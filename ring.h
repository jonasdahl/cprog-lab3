#ifndef RING
#define RING

#include "obj.h"
#include "treasure.h"

#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

namespace lotr {
	class Ring : public Treasure {
	public:
		Ring(string const & name, string const & colour_) : Treasure(name), colour(colour_) {}
		// Of course, THE RING won't need a backpack
		virtual bool needs_backpack() const { return false; }
		// Returns the weight of this object
		virtual double weight() const { return 10000000; };
	protected:
		string colour;
	};
}

#endif