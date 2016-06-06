#ifndef ROHIRRIM
#define ROHIRRIM

#include "char.h"
#include "man.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Rohirrim : public Man {
	public:
		Rohirrim(string const & c_name, Game * g) : Man(c_name, g) {}
		Rohirrim(string const & c_name, string const & p_name, Game * g) : Man(c_name, p_name, g) {}
		virtual string type() const override { return "Rohirrim"; }
		virtual string description() const override { return "Rohirrim är en person från riket Rohan."; }
		int eat(Object * const object);
		virtual string save_string() { return "{Rohirrim:{character_name: '" + character_name + "', player_name: '" + player_name + "', commandMap: " + commandMap + 
										", environment: " + env + ", npc: " + (npc?"true":"false") + ", max_health: " + to_string(max_health) + ", health: " + to_string(health) + ", backpack: " + backpack +
										", quiver: " + quiver + ", items: " + items + ", time_to_revive: " + to_string(time_to_revive) + ", game_over: " + ", game: " + game + "}}"; }

	};
} 

#endif