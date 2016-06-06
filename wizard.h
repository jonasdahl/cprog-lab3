#ifndef WIZARD
#define WIZARD

#include "char.h"
#include "man.h"

#include <list>
#include <map>
#include <iostream>
#include <iostream>
#include <string>

using namespace std;

namespace lotr {
	class Wizard : public Man {
	public:
		// Creates a NPC wizard
		Wizard(string const & c_name, Game * g) : Man(c_name, g), mana(10) {}
		// Creates a playable wizard
		Wizard(string const & c_name, string const & p_name, Game * g) : Man(c_name, p_name, g), mana(10) {}
		virtual bool go(string const & direction);
		virtual bool enchant(Character * const opponent);
		virtual string type() const override { return "Trollkarl"; }
		virtual int get_mana() const { return mana; };
		virtual bool decrease_mana() { if (mana <= 0) return false; mana--; return true; }
		virtual string description() const override;
		// Returns max damage for player's weapons
	private:
		int mana;
	};
}

#endif