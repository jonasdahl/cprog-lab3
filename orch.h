#ifndef ORCH
#define ORCH

#include "char.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Orch : public Character {
	public:
		Orch(string const & c_name, Game * g) : Character(c_name, g) { health = max_health = 5; }
		Orch(string const & c_name, string const & p_name, Game * g) : Character(c_name, p_name, g) { health = max_health = 5; }
		virtual bool action();
		virtual string type() const override { return "Ork"; }
		virtual string description() const override { return "Ork. Äcklig varelse som Sauron har fostrat som sitt barn."; }
		virtual string save_string() { return "{Orch:{character_name: '" + character_name + "', player_name: '" + player_name + "', commandMap: " + commandMap + 
										", environment: " + env + ", npc: " + (npc?"true":"false") + ", max_health: " + std::to_string(max_health) + ", health: " + std::to_string(health) + ", backpack: " + backpack +
										", quiver: " + quiver + ", items: " + items + ", time_to_revive: " + std::to_string(time_to_revive) + ", game_over: " + ", game: " + game + "}}"; }

	};
}

#endif