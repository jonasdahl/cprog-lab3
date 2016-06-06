#ifndef MAN
#define MAN

#include "char.h"
#include "game.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Man : public Character {
	public:
		Man(string const & c_name, Game * g) : Character(c_name, g) { health = max_health = 20; }
		Man(string const & c_name, string const & p_name, Game * g) : Character(c_name, p_name, g) { health = max_health = 20; }
		virtual string type() const = 0;
		virtual bool commandBake();
		virtual bool commandForge();
	};
}

#endif