#ifndef TREASURE
#define TREASURE

#include "obj.h"

#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

namespace lotr {
	class Treasure : public Object {
	public:
		Treasure(string const & name) : Object(name) {}
		virtual string save_string() { return "{Treasure:{name: '" + name + "', owner: " + owner + "}}"; }
	};
}

#endif