#ifndef WAND
#define WAND

#include "obj.h"
#include "weapon.h"

#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

namespace lotr {
	class Wand : public Weapon {
	public:
		Wand(string const & name, float const weight, int const minDamage, int const maxDamage, float const length_, int const mana_cons_) : 
			Weapon(name, weight, minDamage, maxDamage), length(length_), mana_cons(mana_cons_) {}
		virtual int damage() const;
		// Returns true if thing could be used as weapon
		virtual bool use_weapon();
		virtual string save_string() { return "{Wand:{name: '" + name + "', owner: " + owner + ", length: " + std::to_string(length) + 
												", mana_cons: " + std::to_string(mana_cons) + "}}"; }
	protected:
		float length;
		int mana_cons;
	};
}

#endif