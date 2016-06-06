#include "char.h"

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

namespace lotr {
	Character::Character(string const & n, Game * g) {
		init_();
		character_name = n;
		npc = true;
		game = g;
	}

	Character::Character(string const & n, string const & p_n, Game * g) {
		init_();
		player_name = p_n;
		character_name = n;
		npc = false;
		game = g;
	}

	void Character::init_() {
		backpack = nullptr;
		health = 10;
		max_health = 10;
		time_to_revive = 0;
		game_over = false;
		quiver = nullptr;

	 	commandMap.insert(make_pair("gå", &Character::commandGo));
	 	commandMap.insert(make_pair("titta", &Character::commandLook));
	 	commandMap.insert(make_pair("ät", &Character::commandEat));
	 	commandMap.insert(make_pair("mina", &Character::commandObjects));
	 	commandMap.insert(make_pair("prata", &Character::commandTalk));
	 	commandMap.insert(make_pair("slåss", &Character::commandFight));
	 	commandMap.insert(make_pair("plocka", &Character::commandPick));
	 	commandMap.insert(make_pair("släng", &Character::commandDrop));
	 	commandMap.insert(make_pair("utforska", &Character::commandExamine));
	 	commandMap.insert(make_pair("baka", &Character::commandBake));
	 	commandMap.insert(make_pair("smid", &Character::commandForge));
	 	commandMap.insert(make_pair("ragea", &Character::commandRage));
	}

	Character::~Character() {

	}

	void Character::turn() { 
		time_to_revive--; 
		if (time_to_revive == 0) {
			health = max_health;
		} else if (time_to_revive < 0) {
			time_to_revive = 0;
		}
	}

	void Character::set_env(Environment * const e) {
		env = e;
		env->add_person(this);
	}
	
	Environment * Character::get_env() const {
		return env;
	}

	bool Character::action() {
		int val = rand() % 2 + 1;
		switch (val) {
			case 1: {
			// Gå i random direction
				list<string> dirs = env->directions();
				int dir = rand() % dirs.size();
				int i = 0;
				for (auto & o : dirs) {
					if (i == dir) {
						if (go(o)) {
							cout << character_name << " färdades " << o << " till " << env->get_name() << "." << endl;
						} else {
							cout << character_name << " försökte gå " << o << " men misslyckades." << endl;
						}
						break;
					}
					++i;
				}
				break;
			}
			case 2: {
			// Plocka upp allt man kan hitta (dock max 2 saker)
				int j = 0;
				for (auto & o : env->get_objects()) {
					++j;
					cout << character_name << " försöker plocka upp " << o->get_name() << "." << endl;
					pick_up(o);
					if (j > 1)
						break;
				}
				if (j == 0)
					cout << "Det fanns inget att plocka upp här. " << endl;
				break;
			}
		}
		return true || false;
	}

	bool Character::go(string const & direction) {
		if (env->neighbour(direction) == nullptr) {
			cout << "Det finns inget i den riktningen." << endl;
			return false;
		}
		if (!env->leave(this)) {
			cout << "Du är fast här." << endl;
			return false;
		}
		if  (character_name != "Frodo" &&
			env->neighbour(direction)->get_name() == "Mordor" && 
			!env->neighbour(direction)->has_character("Frodo") && 
			!env->neighbour(direction)->neighbour("österut")->has_character("Frodo") &&
			!env->neighbour(direction)->neighbour("österut")->ring_destroyed()) {
			cout << "Du kan inte gå in i Mordor om inte Frodo är där först." << endl;
		env->enter(this);
		return false;
	}
	env = env->neighbour(direction);
	env->enter(this);
	return true;
}

bool Character::damage(int const val) { 
	health -= val; 
	health = health < 0 ? 0 : health; 
	return health > 0; 
}

Object * Character::find_object(string const & obj_name) const {
	for (auto & o : items) {
		if (boost::iequals(o->get_name(), obj_name))
			return o;
	}

	if (backpack != nullptr) {
		if (boost::iequals(backpack->get_name(), obj_name))
			return backpack;

		for (auto & o : backpack->get_content()) {
			if (boost::iequals(o->get_name(), obj_name))
				return o;
		}
	}

	if (quiver != nullptr) {
		if (boost::iequals(quiver->get_name(), obj_name))
			return quiver;

		for (auto & o : quiver->get_content()) {
			if (boost::iequals(o->get_name(), obj_name))
				return o;
		}
	}

	return nullptr;
}

bool Character::fight(Character * const character) {
	cout << endl;
	if (character == this) {
		cout << "Man kan inte attackera sig själv." << endl;
		return true;
	}
	if (character->is_dead()) {
		cout << "Man kan inte attackera redan döda personer." << endl;
		return false;
	}
	cout << character_name << " attackerar " << character->get_character_name() << ". Fight, fight, fight!" << endl;

	for (;;) {
		if (fight_part(this, character)) {
			break;
		}
		if (fight_part(character, this)) {
			break;
		}
	}
	if ((is_dead() && get_character_name() == "Frodo") ||
		(character->is_dead() && character->get_character_name() == "Frodo")) {
		game_over = true;
}
cout << endl; 
cout << "Fighten är slut. " << endl;
return true;
}

void Character::sleep(int q) const {
	for (int c = 0; c < 5 * q / 1000; c++)
		for (int i = 0; i < 1000000; i++) {
			int j = 4711 * 4711 / 5711 * 4711 * 42 * i * c;
			j--;
		}
	}

	bool Character::fight_part(Character * const p1, Character * const p2) {
		sleep(2000);
		cout << endl;
		cout << p1->get_character_name() << ":s hälsopoäng: " << p1->get_health() << endl; 
		cout << p2->get_character_name() << ":s hälsopoäng: " << p2->get_health() << endl;
		cout << endl; 

		sleep(2000);

		if (p1->type() == "Trollkarl")
			cout << p1->get_character_name() << ":s tur. Vill du \"anfalla\", \"trolla\", \"fly\" eller illa fäkta?" << endl;
		else	
			cout << p1->get_character_name() << ":s tur. Vill du \"anfalla\" eller \"fly\"?" << endl;

		if (p1->is_npc()) {
			cout << ">> anfall" << endl;
			int amount = p1->get_weapon_damage();
			sleep(2000);
			cout << p1->get_character_name() << " skadade " << amount << " hp." << endl;
			if (!p2->damage(amount)) {
				cout << p2->get_character_name() << " dog." << endl;
				return true;
			}
			return false;
		}
		for (;;) {
			string command = prompt_token();
			if (command == "anfall" || command == "anfalla") {
				int amount = p1->get_weapon_damage();
				sleep(2000);
				cout << p1->get_character_name() << " skadade " << amount << " hp." << endl;
				if (!p2->damage(amount)) {
					cout << p2->get_character_name() << " dog." << endl;
					return true;
				}
				break;
			} else if (command == "trolla") {
				return p1->enchant(p2);
			} else if (command == "fly") {
				cout << "Flyr..." << endl;
				return true;
			} else {
				cout << "Vad menar du? Försök igen..." << endl;
			}
		}
		return false;
	}

	bool Character::pick_up(Object * const object) {
		string name_ = is_npc() ? character_name : "Du";

		if (!env->pick_up(object)) {
			cout << name_ << " kan inte plocka upp det där." << endl;
			return false;
		}

		if (object->is_quiver()) {
			if (quiver != nullptr) {
				cout << name_ << " har ju redan ett koger." << endl;
				env->drop(object);
				return false;
			}
			quiver = (Quiver *) object;
			cout << name_ << " plockade upp koger." << endl;
			object->set_owner(this);
			return true;
		}

		if (object->is_container()) {
			if (backpack == nullptr) {
				backpack = (Container *) object;
				cout << name_ << " tog på ryggsäcken." << endl;
				object->set_owner(this);
				return true;
			}
			cout << name_ << " har ju redan en ryggsäck." << endl;
			env->drop(object);
			return false;
		}

		if (object->needs_quiver()) {
			if (quiver == nullptr) {
				cout << name_ << " har ju inget koger att lägga dem i." << endl;
				env->drop(object);
				return false;
			}
			if (quiver->backspace() < 1) {
				cout << name_ << " har för många saker i kogret." << endl;
				env->drop(object);
				return false;
			}
			if (quiver->add_item(object)) {
				cout << name_ << " la " << object->get_name() << " i kogret." << endl;
				object->set_owner(this);
				return true;
			}
			cout << name_ << " har inte någon plats i kogret." << endl;
			env->drop(object);
			return false;
		}

		if (object->needs_backpack()) {
			if (backpack == nullptr) {
				cout << name_ << " har ju ingen ryggsäck att lägga den i." << endl;
				env->drop(object);
				return false;
			}
			if (backpack->backspace() < 1) {
				cout << name_ << " har för många saker i ryggsäcken." << endl;
				env->drop(object);
				return false;
			}
			if (backpack->backweight() < ((Container *) object)->weight()) {
				cout << "Hoppsan! Ryggsäcken gick sönder för att " << name_ << " la i för mycket vikt." << endl;
				cout << "Alla saker hamnade på marken, och ryggsäcken förstördes." << endl;
				for (auto & o : backpack->get_content()) {
					env->drop(o);
				}
				delete backpack;
				backpack = nullptr;
				env->drop(object);
				return false;
			}
			if (backpack->add_item(object)) {
				cout << name_ << " la " << object->get_name() << " i ryggsäcken." << endl;
				object->set_owner(this);
				return true;
			}
			cout << name_ << " har inte någon plats i ryggsäcken." << endl;
			env->drop(object);
			return false;
		}

		items.push_back(object);
		object->set_owner(this);
		return true;
	}

	Container * Character::get_backpack() const {
		return backpack;
	}

	Container * Character::get_quiver() const {
		return quiver;
	}

	int Character::get_weapon_damage() const {
		int max = 0;
		Object * maxWeapon = nullptr;
		for (auto & weapon : items) {
			int damage = weapon->damage();
			if (damage > max) {
				max = damage;
				maxWeapon = weapon;
			}
		}
		if (max == 0)
			max = 1;
		if (maxWeapon != nullptr) 
			maxWeapon->use_weapon();
		return max;
	}

	bool Character::add_item(Object * const object) {
		if (object->is_container()) {
			if (backpack == nullptr) {
				backpack = (Container *) object;
				object->set_owner(this);
				return true;
			}
			return false;
		}

		if (object->needs_backpack()) {
			if (backpack == nullptr) {
				return false;
			}
			if (backpack->add_item(object)) {
				object->set_owner(this);
				return true;
			}
			return false;
		}

		items.push_back(object);
		object->set_owner(this);
		return true;
	}

	bool Character::remove_item(Object * object) {
		object->set_owner(nullptr);
		items.remove(object);
		backpack->remove_item(object);
		game->destructObject(object);
		return true;
	}

	bool Character::drop(Object * const object) {
		if (!env->drop(object)) {
			cout << "Du kan inte lägga det där här." << endl;
			return false;
		}

		if (backpack == object) {
			backpack = nullptr;
			cout << "Du slängde ryggsäcken (med allt innehåll) din dummer!" << endl;
			object->set_owner(nullptr);
			return true;
		}

		if (quiver == object) {
			quiver = nullptr;
			cout << "Du slängde kogret (med allt innehåll) din dummer!" << endl;
			object->set_owner(nullptr);
			return true;
		}

		if (object->needs_quiver()) {
			if (quiver != nullptr && quiver->remove_item(object)) {
				object->set_owner(nullptr);
				return true;
			}
			return false;
		}

		if (object->needs_backpack()) {
			if (backpack != nullptr && backpack->remove_item(object)) {
				object->set_owner(nullptr);
				return true;
			}
			return false;
		}

		items.remove(object);
		object->set_owner(nullptr);
		return true;
	}

	int Character::eat(Object * object) {
		Object * obj = find_object(object->get_name());
		if (obj == nullptr)
			return 0;

		int healing = obj->healing_effect();
		if (obj->healing_effect() == 0) 
			return 0;
		if (obj->healing_effect() > 0) {
			health += healing;
			if (health > max_health) 
				health = max_health;
			remove_item(object);	
			return healing;
		}
		health += healing;
		if (health <= 0 && character_name == "Frodo")
			game_over = true;	
		remove_item(object);	
		return healing;
	}

	void Character::talk_to(Character * character) {
		string n = character->get_character_name();
		cout << ">> Du: " << "Hejsan " << n << "!" << endl;
		cout << ">> " << n << ": " << "Hallå hallå i stugan blå!" << endl;
		if (character == this) {
			cout << ">> Molgan: Jag har tappat min fönsterskrapa - den är puts väck." << endl;
			cout << ">> Du: Hahaha Molgan, det där var väldigt roligt!" << endl;
			cout << ">> Molgan: Jag vet, har övat på den länge!" << endl;
			cout << ">> Du: Den var fan sämst." << endl;
			cout << "" << endl;
			cout << "" << endl;
			cout << "" << endl;
			cout << "Molgan börjar gråta och går iväg." << endl;
			cout << endl;
		}
	} 

	bool Character::operator==(Character const & c) const {
		return character_name == c.get_character_name();
	}

	/**
	 * Prompts and returns a line.
	 */
	 string Character::prompt_line() {
	 	cout << ">> ";
	 	return read_line();
	 }

	/**
	 * Prompts and returns a word.
	 */
	 string Character::read_token() {;
	 	string resp;
	 	cin >> resp;
	 	return trim(resp);
	 }

	/**
	 * Prompts and returns a word.
	 */
	 string Character::prompt_token() {
	 	cout << ">> ";
	 	return read_token();
	 }

	/**
	 * Reads a line from user.
	 */
	 string Character::read_line() {
	 	char in[256];
	 	string input;		
	 	cin.getline(in, 256);
	 	input = string(in);
	 	return trim(input);
	 }

	 bool Character::execute(string word) {
		// Checka i mapen
	 	auto fp = commandMap[word];
	 	if (fp == nullptr) {
	 		return false;
	 	}
		return (this->*fp)();
	}


	bool Character::commandRage() {
		string word = read_token();
		if (word != "på") {
			cout << "Nu förstår jag inte..." << endl;
			return false;
		}

		word = read_line();
		Object * object = find_object(word);
		if (object == nullptr) {
			cout << "Hittade inte " << word << "." << endl;
			return false;
		}
		cout << "Du slår " << object->get_name() << " hårt mot bergväggen så det går i bitar. Hoppsan. Det gick sönder." << endl;
		remove_item(object);

		return false;
	}

	bool Character::commandBake() {
		cout << "Du kan inte baka!" << endl;
		read_line();
		wait();
		return false;
	}

	bool Character::commandForge() {
		cout << "Du kan inte smida!" << endl;
		read_line();
		wait();
		return false;
	}

	bool Character::commandGo() {
		string direction = read_token();
		if (go(direction)) {
			cout << "Du färdades till " << get_env()->get_name() << "." << endl;
			read_line();
			wait(); // Walking should take one turn
			return true;
		}
		read_line(); // Consume last \n
		return false;
	}

	bool Character::commandEat() {
		string thing = read_line();
		Object * object = find_object(thing);
		if (object == nullptr) {
			cout << "Maten \"" << thing << "\" kunde inte hittas bland dina saker." << endl;
			return false;
		}
		int res = eat(object);
		if (res != 0) {
			if (res > 0) {
				cout << "Smaskens. Det var gott. Dina hälsopäng ökade till " << get_health() << "." << endl;
			} else {
				if (get_health() <= 0) {
					cout << "Ouäck. Det var gift. Dina hälsopäng minskade med " 
					<< (-res) << " så du dog. Tråkigt, men sånt är livet (eller döden, höhö)." << endl;
				} else {
					cout << "Ouäck. Det var gift. Dina hälsopäng minskade med " 
					<< (-res) << " till " << get_health() << endl;
				}
			}
			return false;
		} 
		cout << "Det gick ju inte att äta " << thing << "." << endl;
		return true;
	}

	bool Character::commandTalk() {
		string word = read_token();
		if (word == "med") {
			string p = read_token();
			Character * person = get_env()->find_character(p);
			if (person == nullptr) {
				cout << "Det finns ingen som heter " << p << " här." << endl;
				return false; 
			}
			if (person == this) {
				cout << "Du är ju rätt så vimsig." << endl;
				cout << "Pratar med dig själv och så." << endl;
			}
			talk_to(person);
		}
		read_line(); // Consume last \n
		return false;
	}

	bool Character::commandFight() {
		string word = read_token();
		if (word == "mot") {
			string p = read_token();
			//cout << "Läst token: " << p <<endl;
			Character * person = get_env()->find_character(p);
			if (person == nullptr) {
				cout << "Det finns ingen som heter " << p << " här." << endl;
				return false; 
			}
			cout << "Du börjar slåss mot " << person->get_character_name() << "." << endl;
			return fight(person);
		}
		read_line();
		return false;
	}

	bool Character::commandPick() {
		string word = read_token();
		if (word == "upp") {
			string thing = read_line();
			Object * object = get_env()->find_object(thing);
			if (object == nullptr) {
				cout << "Objektet \"" << thing << "\" kunde inte hittas på platsen." << endl;
				return false;
			}
			if (pick_up(object)) {
				cout << "Du plockade upp \"" << object->get_name() << "\"." << endl;
			} else {
				cout << "Du misslyckades med att plocka upp \"" << object->get_name() << "." << endl;
			}
		}
		return false;
	}

	bool Character::commandDrop() {	 	
		string thing = read_line();
		Object * object = find_object(thing);
		if (object == nullptr) {
			cout << "Objektet \"" << thing << "\" kunde inte hittas bland dina saker." << endl;
			return false;
		}
		if (drop(object)) {
			cout << "Du slängde \"" << object->get_name() << "\"." << endl;
		} else {
			cout << "Du misslyckades med att slänga \"" << object->get_name() << "." << endl;
		}
		return false;
	}

	bool Character::commandObjects() {
		string word = read_token();
		if (word == "saker") {
			cout << "Du har följande saker:" << endl;
			for (auto & object : inventory()) {
				cout << "- " << object->get_name() << endl;
			}
			if (get_backpack() != nullptr) {	
				cout << "I ryggsäcken har du:" << endl;
				for (auto & object : get_backpack()->get_content()) {
					cout << "- " << object->get_name() << endl;
				}
			}
			if (get_quiver() != nullptr) {	
				cout << "I kogret har du:" << endl;
				for (auto & object : get_quiver()->get_content()) {
					cout << "- " << object->get_name() << endl;
				}
			}
		}
		read_line(); // Consume last \n
		return false;
	}

	bool Character::commandExamine() {
		string thing = read_line();
		Object * object = find_object(thing);
		if (object == nullptr) {
			cout << "Objektet \"" << thing << "\" kunde inte hittas bland dina saker." << endl;
			return false;
		}
		cout << object << endl;
		return false;
	}

	bool Character::commandLook() {	 	
		cout << "Det finns " << get_env()->get_objects().size() << " saker här: " << endl;
		for (auto & dir : get_env()->get_objects()) {
			cout << "- " << dir->get_name() << endl;
		}

		cout << "Det finns " << get_env()->get_characters().size() << " personer här: " << endl;
		for (auto & dir : get_env()->get_characters()) {
			cout << "- " << dir->get_character_name();
			if (dir->is_dead())
				cout << " (död)";
			cout << endl;
		}
		read_line(); // Consume last \n
		return false;
	}

	bool Character::enchant(Character * const p) { 
		cout << "Du försöker trolla men du kan inte! Turen går över till motståndaren" << endl; 
		return false; 
	}


	string & Character::ltrim(string & s) {
		s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
		return s;
	}

	string & Character::rtrim(string & s) {
		s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
		return s;
	}

	string & Character::trim(string & s) {
		return ltrim(rtrim(s));
	}
}