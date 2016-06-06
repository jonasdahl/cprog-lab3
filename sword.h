#ifndef SWORD
#define SWORD

#include "obj.h"
#include "weapon.h"

#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace lotr {
	class Sword : public Weapon {
	public:
		Sword(string const & name, float const weight, int const minDamage, int const maxDamage, float const length_) : 
			Weapon(name, weight, minDamage, maxDamage), length(length_) {}

		virtual string to_string() const;
	protected:
		float length;
	};
}

#endif