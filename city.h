#ifndef CITY
#define CITY

#include "env.h"
#include "outdoors.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class City : public Outdoors {
	public:
		City(string const & n, string const & desc_) : Outdoors(n), desc(desc_) {}
		virtual string description() const override { return desc; }
	private:
		string desc;
	};
}

#endif