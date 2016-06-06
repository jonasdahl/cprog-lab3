#ifndef POISON
#define POISON

#include "obj.h"
#include "food.h"

#include <vector>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Poison : public Food {
	public:
		Poison(string const & name, int const hp) : Food(name, -hp) {}
		virtual string save_string() { return "{Poison:{name: '" + name + "', owner: " + owner + "}}"; }
	};
}

#endif