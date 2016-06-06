#include "weapon.h"
#include "char.h"

using namespace std;

namespace lotr {
	string Weapon::to_string() const {
		stringstream stream; 
		stream << name << " är ett vapen som ägs av " << get_owner()->get_character_name() << "." << endl;
		stream << "Vikt: " << weight() << " kg." << endl;
		stream << "Skada: " << minDamage << "-" << maxDamage << " livspoäng" << endl;
		return stream.str();
	}
}