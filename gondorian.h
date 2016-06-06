#ifndef GONDORIAN
#define GONDORIAN

#include "char.h"
#include "man.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Gondorian : public Man {
	public:
		Gondorian(string const & c_name, Game * g) : Man(c_name, g) {}
		Gondorian(string const & c_name, string const & p_name, Game * g) : Man(c_name, p_name, g) { } 
		virtual string type() const override { return "Gondorian"; }
		virtual string description() const override { return "En gondorian är en person från riket Gondor. Eftersom de är människor \nhar de dubbelt så mycket liv som andra."; }
		virtual string save_string() { return "{Gondorian:{character_name: '" + character_name + "', player_name: '" + player_name + "', commandMap: " + commandMap + 
										", environment: " + env + ", npc: " + (npc?"true":"false") + ", max_health: " + to_string(max_health) + ", health: " + to_string(health) + ", backpack: " + backpack +
										", quiver: " + quiver + ", items: " + items + ", time_to_revive: " + to_string(time_to_revive) + ", game_over: " + ", game: " + game + "}}"; }

	};
}

#endif