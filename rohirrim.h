#ifndef ROHIRRIM
#define ROHIRRIM

#include "char.h"
#include "man.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Rohirrim : public Man {
	public:
		Rohirrim(string const & c_name, Game * g) : Man(c_name, g) {}
		Rohirrim(string const & c_name, string const & p_name, Game * g) : Man(c_name, p_name, g) {}
		virtual string type() const override { return "Rohirrim"; }
		virtual string description() const override { return "Rohirrim är en person från riket Rohan."; }
		int eat(Object * const object);
	};
} 

#endif