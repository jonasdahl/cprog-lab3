#ifndef WEAPON
#define WEAPON

#include "obj.h"

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace lotr {
	class Weapon : public Object {
	public:
		Weapon(string name, float weight_, int minDamage_, int maxDamage_) : Object(name), weights(weight_), minDamage(minDamage_), maxDamage(maxDamage_) {}
		virtual string to_string() const;
		// Never needs backpack for weapons
		virtual bool needs_backpack() const { return false; }
		// Randomizes a damage between mindamage and maxdamage
		virtual int damage() const { 
			return (rand() % (maxDamage - minDamage + 1) + minDamage); 
		}
		// Returns the weight of this object
		virtual double weight() const { return weights; }
		// Returns true if thing could be used as weapon
		virtual bool use_weapon() { return true; }
	protected:
		float weights;
		int minDamage;
		int maxDamage;
	};
}

#endif