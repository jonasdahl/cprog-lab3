#ifndef ELF
#define ELF

#include "char.h"
#include "lembas.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Elf : public Character {
	public:
		Elf(string const & c_name, Game * g) : Character(c_name, g) {}
		Elf(string const & c_name, string const & p_name, Game * g) : Character(c_name, p_name, g) {}
		virtual string type() const { return "Alv"; }
		virtual string description() const override { return "Alv"; }
		virtual int eat(Object * const object);
		virtual bool commandBake();

		virtual string save_string() { return "{Elf:{character_name: '" + character_name + "', player_name: '" + player_name + "', commandMap: " + commandMap + 
										", environment: " + env + ", npc: " + (npc?"true":"false") + ", max_health: " + to_string(max_health) + ", health: " + to_string(health) + ", backpack: " + backpack +
										", quiver: " + quiver + ", items: " + items + ", time_to_revive: " + to_string(time_to_revive) + ", game_over: " + ", game: " + game + "}}"; }

	};
}

#endif