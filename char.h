#ifndef CHARACTER
#define CHARACTER

#include "env.h"
#include "obj.h"
#include "weapon.h"
#include "container.h"
#include "quiver.h"
#include "game.h"
#include <string>
#include <list>

using namespace std;

namespace lotr {
	class Environment;
	class Object;
	class Character {
	public:
		// Create an NPC
		Character(string const & character_name, Game * g);
		// Create a normal player
		Character(string const & character_name, string const & player_name, Game * g);
		// Destroys a character
		virtual ~Character();

		// Pure virtual functions that have to be implemented
		// Returns the type for this character ("Alf", "Ork" etc)
		virtual string type() const = 0;
		virtual string description() const = 0;

		// Returns the name for this character (same as get_character_name())
		virtual string name() const { return character_name; };
		// Returns the name for this character (same as get_character_name())
		// Returns player name
		virtual string get_player_name() const { return player_name; }
		// Returns character name
		virtual string get_character_name() const { return character_name; }
		// Returns health for character
		virtual int get_health() const { return health; }
		// Returns number of turns until character wakes up from death
		virtual int get_time_to_revive() const { return time_to_revive; }

		// Initializes a character
		void init_();
		// True if character is NPC
		bool is_npc() const { return npc; }
		// Sets environment for this character
		void set_env(Environment * const e);
		// Returns the inventory (mainly weapons) for this character
		list<Object *> const & inventory() { return items; }
		// Returns the environment in which this character is
		Environment * get_env() const;
		// Should be called every time it is the user's turn
		void turn();

		void sleep(int) const;
		// Action, called by NPC:s to make them do something
		virtual bool action();
		// Go in given direction
		virtual bool go(string const & direction);
		// Damages character
		virtual bool damage(int const val);
		// Starts a fight with given character
		virtual bool fight(Character * const character);

		// Picks up object
		virtual bool pick_up(Object * const object);
		// Adds item to list of items
		virtual bool add_item(Object * const object);
		// Removes item from list of items
		virtual bool remove_item(Object * object);
		// Drops item from character
		virtual bool drop(Object * const object);
		// Tries to eat object
		virtual int eat(Object * const object);

		// Returns true if game is over
		virtual bool exit() const { return false; }
		// Returns true if user is dead
		virtual bool is_dead() const { return health <= 0; }
		// Starts conversation with character
		virtual void talk_to(Character * character);
		// Returns max damage for player's weapons
		virtual int get_weapon_damage() const;
		// Returns max damage for player's weapons
		virtual bool decrease_mana() { return false; }
		// Enchant like wizard against player
		virtual bool enchant(Character * const player);
		// Enchant like wizard against player
		virtual int get_mana() const { return 0; };

		virtual bool execute(string);
		virtual bool commandGo();
		virtual bool commandLook();
		virtual bool commandEat();
		virtual bool commandObjects();
		virtual bool commandTalk();
		virtual bool commandFight();
		virtual bool commandPick();
		virtual bool commandDrop();
		virtual bool commandExamine();
		virtual bool commandBake();
		virtual bool commandForge();
		virtual bool commandRage();

		// Returns true if game is over
		bool game_is_over() const { return game_over; }
		// Returns the backpack for this user
		Container * get_backpack() const; 
		// Returns the quiver for this user
		Container * get_quiver() const; 

		// Finds object in user inventory/backpack
		Object * find_object(string const & obj) const;

		// Compares two characters and returns true if character names are same
		bool operator==(Character const & c) const;
		virtual string save_string() { return "{character:{name:" + get_character_name() + "}}"; }

		// I/O stuff
		string read_line();
		string read_token();
		string prompt_token();
		string prompt_line();
		string & ltrim(string & s);
		string & rtrim(string & s);
		string & trim(string & s);
		typedef bool (Character::*command)(void);
	protected:
    	std::map <string, command> commandMap;
		Environment * env;
		bool npc;
		int max_health;
		int health;
		string player_name;
		string character_name;
		Container * backpack;
		Quiver * quiver;
		list<Object *> items;
		int time_to_revive;
		bool game_over;
		Game * game;

	private:
		// Part of fight
		bool fight_part(Character * const p1, Character * const p2);
	};
}

#endif