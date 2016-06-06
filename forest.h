#ifndef FOREST
#define FOREST

#include "env.h"
#include "outdoors.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Forest : public Outdoors {
	public:
		Forest(string const & n, string const & desc_) : Outdoors(n), desc(desc_) {}
		virtual string description() const override { return desc; }
		virtual string save_string() { return "{Forest:{name: '" + name + "', objects: " + objects + ", characters: " + characters + ", neighbours: " + neighbours +
		 										", character_map: " + character_map + ", desc: '" + desc + "'}}"; }
	private:
		string desc;
	};
}

#endif