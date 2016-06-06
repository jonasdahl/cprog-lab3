#ifndef ORCH
#define ORCH

#include "char.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Orch : public Character {
	public:
		Orch(string const & c_name, Game * g) : Character(c_name, g) { health = max_health = 5; }
		Orch(string const & c_name, string const & p_name, Game * g) : Character(c_name, p_name, g) { health = max_health = 5; }
		virtual bool action();
		virtual string type() const override { return "Ork"; }
		virtual string description() const override { return "Ork. Äcklig varelse som Sauron har fostrat som sitt barn."; }
	};
}

#endif