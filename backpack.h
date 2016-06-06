#ifndef BACKPACK
#define BACKPACK

#include "obj.h"
#include "container.h"
#include "bag.h"

#include <vector>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Backpack : public Bag {
	public:
		Backpack(string const & name, int const volume_, float const maxWeight_) : Bag(name, volume_, maxWeight_) {}
	};
	virtual string save_string() { return "{Backpack:{name: '" + name + "', owner: " + owner + "}}"; }
}

#endif