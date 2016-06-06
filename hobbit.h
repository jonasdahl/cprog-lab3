#ifndef HOBBIT
#define HOBBIT

#include "char.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Hobbit : public Character {
	public:
		Hobbit(string const & c_name, Game * g) : Character(c_name, g) {}
		Hobbit(string const & c_name, string const & p_name, Game * g) : Character(c_name, p_name, g) {}
		virtual bool action();
		virtual bool exit() const;
		virtual string type() const override { return "Hob"; }
		virtual string description() const override { return "Hober är speciella varelser. De är smarta och kan gå långa sträckor men de är inte så bra på att slåss."; }
		virtual string save_string() { return "{Hobbit:{character_name: '" + character_name + "', player_name: '" + player_name + "', commandMap: " + commandMap + 
										", environment: " + env + ", npc: " + (npc?"true":"false") + ", max_health: " + to_string(max_health) + ", health: " + to_string(health) + ", backpack: " + backpack +
										", quiver: " + quiver + ", items: " + items + ", time_to_revive: " + to_string(time_to_revive) + ", game_over: " + ", game: " + game + "}}"; }

	};
}

#endif