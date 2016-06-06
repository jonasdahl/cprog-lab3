#ifndef AMMUNITION
#define AMMUNITION

#include "obj.h"

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace lotr {
	class Ammunition : public Object {
	public:
		Ammunition(string const & name, int const amount_, int const damage__) : Object(name), amount(amount_), damage_(damage__) {}
		// Returns the weight of this object
		virtual double weight() const { return 0.05; }
		virtual int damage() const { return damage_; }
		virtual int get_amount() const { return amount; }
		virtual bool use_weapon() { if (amount <= 0) return false; --amount; return true; }
		virtual string to_string() const;
		// Returns true if object is arrow and needs to be placed quiver
		virtual int needs_quiver() const { return true; }
	protected:
		int amount;
		int damage_;
	};
}

#endif