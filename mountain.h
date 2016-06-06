#ifndef MOUNTAIN
#define MOUNTAIN

#include "env.h"
#include "outdoors.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Mountain : public Outdoors {
	public:
		Mountain(string const & n, string const & desc_) : Outdoors(n), desc(desc_) {}

		// Rings can be destroyed in all mountains
		virtual bool destroy_ring(Object * const object);
		virtual string description() const override { return desc; }
		virtual string save_string() { return "{Mountain:{name: '" + name + "', objects: " + objects + ", characters: " + characters + ", neighbours: " + neighbours +
		 										", character_map: " + character_map + ", desc: '" + desc + "'}}"; }
	private:
		string desc;
	};
}

#endif