#ifndef OUTDOORS
#define OUTDOORS

#include "env.h"

#include <vector>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Outdoors : public Environment {
	public:
		Outdoors(string const & n);
		virtual string get_weather() const;
		virtual string save_string() { return "{Outdoors:{name: '" + name + "', objects: " + objects + ", characters: " + characters + ", neighbours: " + neighbours +
		 										", character_map: " + character_map + ", weathers: " + weathers + "}}"; }
	private:
		vector<string> weathers;
	};
}

#endif