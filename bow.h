#ifndef BOW
#define BOW

#include "obj.h"
#include "weapon.h"

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace lotr {
	class Bow : public Weapon {
	public:
		Bow(string const & name, float const weight, int const minDamage, int const maxDamage, float const accuracy_) : 
			Weapon(name, weight, minDamage, maxDamage), accuracy(accuracy_) {}
		virtual string to_string() const;
		virtual int damage() const;
		// Returns true if thing could be used as weapon
		virtual bool use_weapon();
		virtual string save_string() { return "{Bow:{name: '" + name + "', owner: " + owner + ", accuracy: " + std::to_string(accuracy) + "}}"; }
	protected:
		float accuracy;
	};
}

#endif