#include "includes.h"

#include "game.h"
#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <unistd.h>
#include <term.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <boost/algorithm/string.hpp>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <ctime>

using namespace std;

namespace lotr {
	Game::Game() {
		turn = 0;
		gameMap = vector<Environment *>();
		srand(time(0));
	}

	void Game::play() {
		// Ask for player names and init gameplay
		clear_terminal();
		init();
		clear_terminal();
		// Print intro text
		cout << get_file_contents("intro.txt") << std::endl;
		wait();
		clear_terminal();
		// Print description text
		cout << get_file_contents("description.txt") << std::endl;
		wait();

		int oldTurn = -1;
		// One iteration for every prompt
		for (turn = 0;;) {
			clear_terminal();

			// Now will store the active player
			Character * now = characters[turn];

			if (turn != oldTurn) {
				// If it is time for user to type for the first time this lap, call turn()
				now->turn();
				oldTurn = turn;
			}

			if (now->is_dead()) {
				// Jump to next player
				turn = turn >= ((int) characters.size() - 1) ? 0 : turn + 1;
				continue;
			}
			
			print_turn_info(now);

			if (now->is_npc()) {
				sleep(2000);
				now->action(); // Act
				wait();

				// If NPC made game end (Frodo), do it
				if (now->exit()) {
					clear_terminal();
					cout << "Spelet är över." << endl;
					wait();
					break;
				}

				// If NPC made game end (Frodo), do it
				if (now->game_is_over()) {
					clear_terminal();
					cout << "Frodo är död, så GAME OVER." << endl;
					wait();
					break;
				}

				turn = turn >= ((int) characters.size() - 1) ? 0 : turn + 1;
				continue;
			}

			// INV: Not NPC
			// Ask for command
			string word = prompt_token();

			// We'll see what we can do out of this
			if (word == "avsluta") {
				break;
			} else if (word == "pass" || word == "p") {
				print_pass(now);
				turn = turn >= ((int) characters.size() - 1) ? 0 : turn + 1;
				cout << "Turen gick vidare." << endl;
				read_line(); // Consume last \n
			} else if (word == "spara") {
				ofstream savefile;
				savefile.open("saved.txt");
				for (auto & o : objects) {
					savefile << o->save_string() << endl;
				}
				for (auto & o : characters) {
					savefile << o->save_string() << endl;
				}
				for (auto & o : gameMap) {
					savefile << o->save_string() << endl;
				}
				savefile.close();
			} else if (word == "ladda") {
				ofstream savefile;
				savefile.open("saved.txt");
				for (auto & o : objects) {
					savefile << o->save_string() << endl;
				}
				for (auto & o : characters) {
					savefile << o->save_string() << endl;
				}
				for (auto & o : gameMap) {
					savefile << o->save_string() << endl;
				}
				savefile.close();
			} else if (word == "hjälp") {
				print_help(now);
				read_line(); // Consume last \n
			} else {
				if (now->execute(word)) {
					turn = turn >= ((int) characters.size() - 1) ? 0 : turn + 1;
					cout << "Turen gick vidare." << endl;
				} else {
					cout << "Det är fortfarande din tur." << endl;
				}
			}
			wait(); 
			
			if (now->game_is_over()) {
				clear_terminal();
				cout << "Frodo är död, så GAME OVER." << endl;
				wait();
				break;
			}
		}

		//cout << "Tar bort alla karaktärer." << endl;
		for (auto & character : characters) {
			//cout << "-> Tar bort " << character->get_character_name() << endl; 
			delete character;
		}

		//cout << "Tar bort alla rum." << endl;
		for (auto & env : gameMap) {
			//cout << "-> Tar bort " << env->get_name() << endl; 
			delete env;
		}

		//cout << "Tar bort alla objekt." << endl;
		for (auto & obj : objects) {
			//cout << "-> Tar bort " << obj->get_name() << endl; 
			delete obj;
		}
	}

	bool Game::print_fight(Character * player) {
		string p = read_token();
		//cout << "Läst token: " << p <<endl;
		Character * person = player->get_env()->find_character(p);
		if (person == nullptr) {
			cout << "Det finns ingen som heter " << p << " här." << endl;
			return false; 
		}
		cout << "Du börjar slåss mot " << person->get_character_name() << "." << endl;
		return player->fight(person);
	}

	void Game::print_pass(Character *) {
		cout << "Du stod över din tur." << endl;
	}

	/**
	 * Prints info before each turn.
	 */
	 void Game::print_turn_info(Character * player) {
	 	cout << "*******************************" << endl;
	 	cout << "* " << player->get_character_name();
	 	if (!player->is_npc())
	 		cout << " (" << player->get_player_name() << ")";
	 	cout << endl;
	 	cout << "*******************************" << endl;
	 	cout << player->get_character_name() << " befinner sig innan sin tur i " << player->get_env()->get_name() 
	 	<< " och det " << player->get_env()->get_weather() << "." << endl;
	 	cout << player->get_env()->description() << endl;
	 	cout << "Hen har " << player->get_health() << " hp." << endl;
	 	cout << player->description() << endl;
	 	if (player->inventory().size() > 0) {
	 		cout << player->get_character_name() << " har följande saker:" << endl;
	 		for (auto & object : player->inventory()) {
	 			cout << "- " << object->get_name() << endl;
	 		}
	 		cout << endl;
	 	}
	 	if (player->get_backpack() != nullptr && player->get_backpack()->get_content().size() > 0) {
	 		cout << "I ryggsäcken har " << player->get_character_name() << ":" << endl;
	 		for (auto & object : player->get_backpack()->get_content()) {
	 			cout << "- " << object->get_name() << endl;
	 		}
	 		cout << endl;
	 	} else if (player->get_backpack() != nullptr) {
	 		cout << "Din ryggsäck är tom." << endl;
	 	}

	 	if (player->get_quiver() != nullptr && player->get_quiver()->get_content().size() > 0) {
	 		cout << "I kogret har " << player->get_character_name() << ":" << endl;
	 		for (auto & object : player->get_quiver()->get_content()) {
	 			cout << "- " << object->get_name() << " (" << object->get_amount() << ")" << endl;
	 		}
	 		cout << endl;
	 	} else if (player->get_quiver() != nullptr) {
	 		cout << "Ditt koger är tomt." << endl;
	 	}
	 	cout << endl;
	 }

	/**
	 * Prompts and returns a line.
	 */
	 void Game::print_help(Character * player) {
	 	auto minfunktion = [] (int x) { return x + 1; };

	 	cout << 1 << endl;
	 	cout << minfunktion(1) << endl;

	 	cout << "Du kan använda följande kommandon:" << endl;
	 	cout << " hjälp              :: Visar det här hjälpmeddelandet." << endl;
	 	cout << " titta              :: Se dig omkring efter saker och personer på samma plats." << endl;
	 	cout << " gå [riktning]      :: Gå i angiven riktning och avsluta denna omgång så att nästa spelare får spela." << endl;
	 	cout << "                       Du kan i detta rum gå i följande riktningar: " << endl;
	 	for (auto & dir : player->get_env()->get_directions()) {
	 		cout << "                       - " << dir.first << ": " << dir.second->get_name() << endl;
	 	}
	 	cout << " plocka upp [sak]   :: Plocka upp en sak från marken." << endl;
	 	cout << " släng [sak]        :: Släng en sak som du har." << endl;
	 	cout << " prata med [person] :: Prata med en person på samma plats." << endl;
	 	cout << " mina saker         :: Presenterar en lista över saker som du har plockat upp." << endl;
	 	cout << " utforska [sak]     :: Visa egenskaper för ett objekt som du har." << endl;
	 	cout << " ät [sak]           :: Äter sak." << endl;
	 	cout << " slåss mot [person] :: Startar en fight mot angiven person på samma plats." << endl;
	 	cout << " pass               :: Stå över din tur." << endl;
	 	cout << " avsluta            :: Avslutar spelet." << endl;
	 }

	/**
	 * Prompts and returns a line.
	 */
	 string Game::prompt_line() {
	 	cout << "> ";
	 	return read_line();
	 }

	/**
	 * Prompts and returns a word.
	 */
	 string Game::read_token() {;
	 	string resp;
	 	cin >> resp;
	 	return trim(resp);
	 }

	/**
	 * Prompts and returns a word.
	 */
	 string Game::prompt_token() {
	 	cout << "> ";
	 	return read_token();
	 }

	/**
	 * Reads a line from user.
	 */
	 string Game::read_line() {
	 	char in[256];
	 	string input;		
	 	cin.getline(in, 256);
	 	input = string(in);
	 	return trim(input);
	 }

	/**
	 * Rensar skärmen.
	 */
	 void Game::clear_terminal() {
	 	printf("\033[2J\033[1;1H");
	 }

	/** 
	 * Visar en prompt med "Tryck enter för att fortsätta"
	 */
	 void Game::wait() {
	 	cout << endl;
	 	cout << "Tryck enter för att fortsätta...";
	 	read_line();
	 }

	 void Game::sleep(int q) const {
	 	for (int c = 0; c < 10 * q / 1000; c++)
	 		for (int i = 0; i < 1000000; i++) {
	 			int j = 4711 * 4711 / 5711 * 4711 * 42 * i * c;
	 			j--;
	 		}
	 	}

	/** 
	 * Hämtar innehåll i fil med givet namn.
	 */
	 string Game::get_file_contents(string file) {
	 	string text = "";
	 	ifstream reader(file);
	 	if (reader) {
	 		while (reader.good()) {
	 			string temp_line;
	 			getline(reader, temp_line);
	 			temp_line += "\n";
	 			text += temp_line;
	 		}
	 		reader.close();
	 		return text;
	 	} else {
	 		reader.close();
	 		return "Ett fel uppstod.";
	 	}
	 }

	 void Game::destructObject(Object * & o) {
	 	objects.erase(std::remove(objects.begin(), objects.end(), o), objects.end());
	 	delete o;
	 }

	 void Game::createObject(Object * & o) {
	 	objects.push_back(o);
	 }

	/**
	 * Initierar hela spelet.
	 */
	 void Game::init() {
	 	string input;

		/**
		 * Add players.
		 */
		 cout << "Vem ska vara Boromir?" << endl;
		 input = prompt_line(); 
		 Character * boromir = new Gondorian("Boromir", input, this);

		 Object * lambda = new Sword("Boromirs svärd", 8, 1, 2, 0.9);
		 objects.push_back(lambda);
		 boromir->add_item(lambda);

		 cout << endl;
		 clear_terminal();

		 cout << "Vem ska vara Gandalf?" << endl;
		 input = prompt_line(); 
		 Character * gandalf = new Wizard("Gandalf", input, this);

		 Object * gswfs = new Sword("Gandalfs svärd", 8, 2, 5, 0.9);
		 objects.push_back(gswfs);
		 gandalf->add_item(gswfs);

		 cout << endl;
		 clear_terminal();

		 cout << "Vem ska vara Éowyn?" << endl;	
		 input = prompt_line();
		 Character * eowyn = new Rohirrim("Éowyn", input, this);

		 Object * esw = new Sword("Èowyns svärd", 8, 1, 3, 0.9);
		 objects.push_back(esw);
		 eowyn->add_item(esw);

		 Container * ers = new Backpack("Èowyns ryggsäck", 10, 100);
		 objects.push_back(ers);
		 eowyn->add_item(ers);

		 Object * lembas_e = new Lembas("Èowyns lembas", 1);
		 objects.push_back(lembas_e);
		 ers->add_item(lembas_e);

		 Object * ebpa = new Backpack("Ryggsäck", 2, 5);
		 objects.push_back(ebpa);
		 eowyn->add_item(ebpa);

		 cout << endl;
		 clear_terminal();

		 cout << "Vem ska vara Legolas?" << endl;
		 input = prompt_line();
		 Character * legolas = new Elf("Legolas", input, this);

		 Object * lsw = new Sword("Legolas svärd", 8, 3, 4, 0.9);
		 objects.push_back(lsw);
		 legolas->add_item(lsw);

		 cout << endl;	
		 clear_terminal();	

		 Character * frodo = new Hobbit("Frodo", this);
		 Object * fbp = new Backpack("Ryggsäck", 2, 5);
		 objects.push_back(fbp);
		 frodo->add_item(fbp);

		 Character * gollum = new Hobbit("Gollum", this);
		 Object * gbp = new Backpack("Ryggsäck", 2, 5);
		 objects.push_back(gbp);
		 gollum->add_item(gbp);

		 Character * galadriel = new Elf("Galadriel", this);
		 Object * gabp = new Backpack("Ryggsäck", 2, 5);
		 objects.push_back(gabp);
		 galadriel->add_item(gabp);

		 Character * denethor = new Gondorian("Denethor", this);
		 Object * dbp = new Backpack("Ryggsäck", 2, 5);
		 objects.push_back(dbp);
		 denethor->add_item(dbp);
		 Object * dsw = new Sword("Denethors svärd", 8, 2, 3, 0.9);
		 objects.push_back(dsw);
		 denethor->add_item(dsw);

		 Character * faramir = new Gondorian("Faramir", this);
		 Object * fabp = new Backpack("Ryggsäck", 2, 5);
		 objects.push_back(fabp);
		 faramir->add_item(fabp);
		 Object * fsw = new Sword("Faramirs svärd", 8, 2, 4, 0.9);
		 objects.push_back(fsw);
		 faramir->add_item(fsw);

		 Character * orch1 = new Orch("Vätte", this);
		 Object * o1bp = new Backpack("Ryggsäck", 2, 5);
		 objects.push_back(o1bp);
		 orch1->add_item(o1bp);
		 Object * o1sv = new Sword("Orksvärd", 8, 0, 3, 0.9);
		 objects.push_back(o1sv);
		 orch1->add_item(o1sv);

		 Character * orch2 = new Orch("Ork", this);
		 Object * o2bp = new Backpack("Ryggsäck", 2, 5);
		 objects.push_back(o2bp);
		 orch2->add_item(o2bp);
		 Object * o2sv = new Sword("Orksvärd", 8, 0, 3, 0.9);
		 objects.push_back(o2sv);
		 orch2->add_item(o2sv);

		 characters.push_back(frodo);
		 characters.push_back(gollum);
		 characters.push_back(boromir);
		 characters.push_back(gandalf);
		 characters.push_back(eowyn);
		 characters.push_back(legolas);
		 characters.push_back(faramir);
		 characters.push_back(denethor);
		 characters.push_back(galadriel);
		 characters.push_back(orch1);
		 characters.push_back(orch2);

		/**
		 * Add objects.
		 */
		 Object * ring 			= new Ring("Härskarringen", "Guld");
		 Object * quiver 		= new Quiver("Pilkoger", 10);
		 Object * bow 			= new Bow("Pilbåge", 5, 4, 5, 10.0);
		 Object * arrows1 		= new Ammunition("Pilar", 5, 1);
		 Object * arrows2 		= new Ammunition("Pilar", 2, 1);
		 Object * arrows3 		= new Ammunition("Pilar", 5, 1);
		 Object * sword1 		= new Sword("Anduril", 10, 2, 4, 1.2);
		 Object * sword2 		= new Sword("Glamdring", 10, 2, 3, 1);
		 Object * sword3 		= new Sword("Sting", 5, 1, 2, 0.6);
		 Object * sword4 		= new Sword("Svärd", 8, 0, 3, 0.9);
		 Object * small_dagger 	= new Sword("Liten dolk", 4, 0, 2, 0.4);
		 Object * wand 			= new Wand("Gandalfs stav", 5, 4, 8, 1.8, 2);
		 Object * lembas1 		= new Lembas("Halvstor Lembas", 10);
		 Object * lembas2 		= new Lembas("Liten Lembas", 5);
		 Object * lembas3 		= new Lembas("Stor Lembas", 15);
		 Object * lembas4 		= new Lembas("Väldigt stor Lembas", 20);
		 Object * lembas5 		= new Lembas("Halvstor Lembas", 10);
		 Object * lembas6 		= new Lembas("Liten Lembas", 5);
		 Object * lembas7 		= new Lembas("Stor Lembas", 15);
		 Object * lembas8 		= new Lembas("Väldigt stor Lembas", 20);
		 Object * poison 		= new Poison("Saftig lembas", 5);

		 objects.push_back(bow);
		 objects.push_back(ring);
		 objects.push_back(quiver);
		 objects.push_back(arrows1);
		 objects.push_back(arrows2);
		 objects.push_back(arrows3);
		 objects.push_back(sword1);
		 objects.push_back(sword2);
		 objects.push_back(sword3);
		 objects.push_back(sword4);
		 objects.push_back(small_dagger);
		 objects.push_back(wand);
		 objects.push_back(lembas1);
		 objects.push_back(lembas2);
		 objects.push_back(lembas3);
		 objects.push_back(lembas4);
		 objects.push_back(lembas5);
		 objects.push_back(lembas6);
		 objects.push_back(lembas7);
		 objects.push_back(lembas8);
		 objects.push_back(poison);


		/**
		 * Add environments.
		 */
		 Environment * rivendell = new City("Vattnadahl", "Du är i alven Elronds rike Vattnadahl. Du känner ett stilla lugn fylla din kropp, \nsamtidigt som du vet att du snart måste ge dig av...");
		 Environment * moria = new Mine("Moria", "Du öppnar porten till Moria med lösenordet \"Mellon\". Strax efter att du kommer in slås \nporten igen bakom dig. Porten till Vattnadahl har rasat igen. \nDu måste bege dig till Lothlorien!");
		 Environment * lothlorien = new Forest("Lothlórien", "Du kommer in i drottning Galadriels skog. Runt dig är det tyst och du känner dig iakttagen.");
		 Environment * edoras = new City("Edoras", "Du färdas till Rohans rike och finner dig själv i huvudstaden Edoras.");
		 Environment * deserted_house = new House("Övergivet hus", "Ridandes västerut ser du ett hus. Du går in och finner det \nhelt öde med spindelväv över väggarna.");
		 Environment * minas_tirith = new City("Minas Tirith", "Du beger dig till Gondors huvudstad, Minas Tirith. \nStaden är full av människor som flyr från Mordors styrkor.");
		 Environment * mordor = new City("Mordor", "Frodo är framför dig för att förstöra ringen. Mordors styrkor kommer snart vara besegrade.");
		 Environment * mount_doom = new Mountain("Domedagsklyftan", "Du befinner dig i Domedagsklyftan. Det enda stället i Midgård där Härskarringen kan förstöras...");

		 rivendell		->set_direction("söderut", moria);
		// moria 			->set_direction("västerut", rivendell);
		 moria 			->set_direction("österut", lothlorien);
		 lothlorien		->set_direction("västerut", moria);
		 lothlorien		->set_direction("söderut", edoras);
		 edoras 			->set_direction("norrut", lothlorien);
		 edoras 			->set_direction("österut", minas_tirith);
		 edoras 			->set_direction("västerut", deserted_house);
		 deserted_house 	->set_direction("österut", edoras);
		 minas_tirith 	->set_direction("norrut", edoras);
		 minas_tirith 	->set_direction("österut", mordor);
		 mordor 			->set_direction("västerut", minas_tirith);
		 mordor 			->set_direction("österut", mount_doom);
		 mount_doom 		->set_direction("västerut", mordor);
		//mount_doom 		->set_direction("upp", rivendell);

		 Backpack * backpack2 = new Backpack("Ryggsäck", 3, 2);
		 objects.push_back(backpack2);

		 boromir 		->add_item(backpack2);
		 frodo			->add_item(sword3);
		 frodo			->add_item(ring);
		 boromir 		->add_item(bow);
		 rivendell		->add_item(quiver);
		 rivendell		->add_item(sword1);
		 rivendell		->add_item(sword1);
		 rivendell		->add_item(sword2);
		 rivendell		->add_item(sword4);
		 rivendell		->add_item(small_dagger);
		 rivendell		->add_item(poison);
		 gandalf			->add_item(wand);
		 rivendell 		->add_item(arrows1);
		 moria			->add_item(arrows2);
		 minas_tirith	->add_item(arrows3);
		 lothlorien		->add_item(lembas1);
		 lothlorien		->add_item(lembas3);
		 lothlorien		->add_item(lembas4);
		 lothlorien		->add_item(lembas5);
		 lothlorien		->add_item(lembas7);
		 rivendell		->add_item(lembas8);
		 deserted_house	->add_item(lembas2);
		 deserted_house	->add_item(lembas6);
		 for (int i = 0; i < 5; ++i) {
		 	Object * backpack = new Backpack("Ryggsäck", 2, 5);
		 	objects.push_back(backpack);
		 	rivendell->add_item(backpack);
		 } 

		 Object * l1 = new Lembas("l1", 15);
		 Object * l2 = new Lembas("l2", 15);
		 Object * l3 = new Lembas("l3", 15);
		 objects.push_back(l1);
		 objects.push_back(l2);
		 objects.push_back(l3);

		 rivendell->add_item(l1);
		 rivendell->add_item(l2);
		 rivendell->add_item(l3);

		 gollum 		->set_env(moria);
		 orch1 		->set_env(moria);
		 legolas 	->set_env(rivendell);
		 boromir 	->set_env(rivendell);
		 gandalf 	->set_env(rivendell);
		 eowyn 		->set_env(edoras);
		 frodo 		->set_env(rivendell);
		 orch2 		->set_env(mordor);
		 galadriel 	->set_env(lothlorien);
		 denethor 	->set_env(minas_tirith);
		 faramir 	->set_env(minas_tirith);

		 gameMap.push_back(moria);
		 gameMap.push_back(rivendell);
		 gameMap.push_back(lothlorien);
		 gameMap.push_back(edoras);
		 gameMap.push_back(deserted_house);
		 gameMap.push_back(minas_tirith);
		 gameMap.push_back(mordor);
		 gameMap.push_back(mount_doom);
		}

		string & Game::ltrim(string & s) {
			s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
			return s;
		}

		string & Game::rtrim(string & s) {
			s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
			return s;
		}

		string & Game::trim(string & s) {
			return ltrim(rtrim(s));
		}
	}