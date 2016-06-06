#ifndef ELF
#define ELF

#include "char.h"
#include "lembas.h"

#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Elf : public Character {
	public:
		Elf(string const & c_name, Game * g) : Character(c_name, g) {}
		Elf(string const & c_name, string const & p_name, Game * g) : Character(c_name, p_name, g) {}
		virtual string type() const { return "Alv"; }
		virtual string description() const override { return "Alv"; }
		virtual int eat(Object * const object);
		virtual bool commandBake();
	};
}

#endif