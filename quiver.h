#ifndef QUIVER
#define QUIVER

#include "obj.h"
#include "container.h"

#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

namespace lotr {
	class Quiver : public Container {
	public:
		Quiver(string const & name, int const capacity_) : Container(name, capacity_, 0) {}
		// True if this object can contain ammunition
		virtual bool is_quiver() const { return true; }
		virtual string save_string() { return "{Quiver:{name: '" + name + "', owner: " + owner + "}}"; }
	};
}

#endif