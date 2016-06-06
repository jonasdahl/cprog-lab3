#ifndef INDOORS
#define INDOORS

#include "env.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Indoors : public Environment {
	public:
		Indoors(string const & n) : Environment(n) {}
		virtual string get_weather() const { return "är säkert att sova och du påverkas inte längre av vädret utanför"; }
	};
}

#endif