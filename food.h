#ifndef FOOD
#define FOOD

#include "obj.h"

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace lotr {
	class Food : public Object {
	public:
		Food(string const & name, int const hp_) : Object(name), hp(hp_) {}

		// Returns the healing effect for this food
		virtual int healing_effect() const { return hp; }

		// Returns the weight of this object
		virtual double weight() const { return 0.250; }
		virtual string to_string() const;
		virtual string save_string() { return "{Food:{name: '" + name + "', owner: " + owner + ", hp: " + std::to_string(hp) + "}}"; }	
	protected:
		int hp;
	};
}

#endif