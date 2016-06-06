#include "wizard.h"
#include <string>
#include <sstream>

using namespace std;

namespace lotr {

	bool Wizard::enchant(Character * const opponent) {
		cout << get_character_name() << " trollar lite på " << opponent->get_character_name() << "." << endl;
		opponent->damage(7);
		cout << "Du skadade 7!" << endl;
		mana--;
		cout << "Du trollade lite och har " << get_mana() << " mana kvar!" << endl;
		if (opponent->is_dead()) {
			return true;
		}
		return false;
	}
	
	bool Wizard::go(string const & direction) {
		if (env->neighbour(direction) == nullptr)
			return false;
		if (!env->leave(this))
			return false;
		if (env->get_name() == "Moria" && env->neighbour(direction)->get_name() == "Lothlórien") {
			// Dö på Khazad-dûm-bron (Dwarrowdelf)
			cout << "Ajaj, det kom en Balrog och käkade upp dig." << endl;
			cout << "Du kommer inte få vara med på två omgångar." << endl;
			env = env->neighbour("österut")->neighbour("söderut")->neighbour("västerut");
			health = 0;
			time_to_revive = 3;
		} else {
			env = env->neighbour(direction);
		}
		env->enter(this);
		return health > 0;
	}

	string Wizard::description() const {
		stringstream stream; 
		stream << "Trollkarl. Mana kvar: " << mana << endl;
		return stream.str();
	}
}