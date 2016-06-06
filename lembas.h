#ifndef LEMBAS
#define LEMBAS

#include "obj.h"
#include "food.h"

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace lotr {
	class Lembas : public Food {
	public:
		Lembas(string const & name, int const hp) : Food(name, hp) {}
		virtual string to_string() const;
		virtual string save_string() { return "{Lembas:{name: '" + name + "', owner: " + owner + "}}"; }
	};
}

#endif