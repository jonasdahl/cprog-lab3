#ifndef GAME
#define GAME

#include "env.h"
#include "char.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace lotr {
	class Environment;
	
	class Game {
	public:
		Game();
		string read_line();
		string read_token();
		string prompt_token();
		string prompt_line();
		void init();
		void play();
		void wait();
		void clear_terminal();
		void print_intro();
		void print_turn_info(Character *);
		void print_help(Character *);
		void print_look(Character *);
		void print_drop(Character *);
		void print_eat(Character *);
		bool print_fight(Character *);
		void print_pass(Character *);
		void print_examine(Character *);
		void print_pick_up(Character * player);
		void print_my_things(Character * player);
		void print_talk_to(Character * player);
		void print_gandalf();
		void sleep(int) const;
		string get_file_contents(string file);
		string & ltrim(string & s);
		string & rtrim(string & s);
		string & trim(string & s);
		void destructObject(Object * & o);
		void createObject(Object * & o);

		typedef int (Character::*command)(int);
	private:
		int turn;
		vector<Character *> characters;
		vector<Environment *> gameMap;
		vector<Object *> objects;
	};
}

#endif