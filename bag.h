#ifndef BAG
#define BAG

#include "obj.h"
#include "container.h"

#include <vector>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Bag : public Container {
	public:
		Bag(string const & name, int const volume, float const maxWeight) : Container(name, volume, maxWeight) {}
	};
}

#endif