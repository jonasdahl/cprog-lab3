#ifndef HOBBIT
#define HOBBIT

#include "char.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Hobbit : public Character {
	public:
		Hobbit(string const & c_name, Game * g) : Character(c_name, g) {}
		Hobbit(string const & c_name, string const & p_name, Game * g) : Character(c_name, p_name, g) {}
		virtual bool action();
		virtual bool exit() const;
		virtual string type() const override { return "Hob"; }
		virtual string description() const override { return "Hober är speciella varelser. De är smarta och kan gå långa sträckor men de är inte så bra på att slåss."; }
	};
}

#endif