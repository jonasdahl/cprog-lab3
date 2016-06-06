#ifndef HOUSE
#define HOUSE

#include "env.h"
#include "indoors.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class House : public Indoors {
	public:
		House(string const & n, string const & desc_) : Indoors(n), desc(desc_) {}
		virtual string description() const override { return desc; }
		virtual string save_string() { return "{House:{name: '" + name + "', objects: " + objects + ", characters: " + characters + ", neighbours: " + neighbours +
		 										", character_map: " + character_map + ", desc: '" + desc + "'}}"; }
	private:
		string desc;
	};
}

#endif