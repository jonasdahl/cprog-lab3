#ifndef MAN
#define MAN

#include "char.h"
#include "game.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Man : public Character {
	public:
		Man(string const & c_name, Game * g) : Character(c_name, g) { health = max_health = 20; }
		Man(string const & c_name, string const & p_name, Game * g) : Character(c_name, p_name, g) { health = max_health = 20; }
		virtual string type() const = 0;
		virtual bool commandBake();
		virtual bool commandForge();
		virtual string save_string() { return "{Man:{character_name: '" + character_name + "', player_name: '" + player_name + "', commandMap: " + commandMap + 
										", environment: " + env + ", npc: " + (npc?"true":"false") + ", max_health: " + to_string(max_health) + ", health: " + to_string(health) + ", backpack: " + backpack +
										", quiver: " + quiver + ", items: " + items + ", time_to_revive: " + to_string(time_to_revive) + ", game_over: " + ", game: " + game + "}}"; }

	};
}

#endif