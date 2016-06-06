#include "hobbit.h"

using namespace std;

namespace lotr {
	bool Hobbit::action() {
		// All hobbits are going to Mount Doom.
		if (env->get_name() == "Domedagsklyftan") {
			Object * ring = find_object("Härskarringen");
			if (env->destroy_ring(ring)) {
				cout << "Frodo förstörde ringen." << endl;
				cout << "Ni har vunnit spelet. Grattis!" << endl;
				return true;
			} 
			cout << "Kunde inte förstöra ringen. (Isildur style)." << endl;
		}

		for (auto & direction : env->directions()) {
			if (direction == "österut" || direction == "söderut") {
				if (go(direction)) {
					cout << character_name << " färdades " << direction << " till " << env->get_name() << "." << endl;
				}
				return true;
			}
		}

		return Character::action();
	}

	bool Hobbit::exit() const {
		if (env->ring_destroyed())
			return true;
		return false;
	}
}