#include "orch.h"

using namespace std;

namespace lotr {
	bool Orch::action() {
		for (auto & person : env->get_characters()) {
			if (person != this && person->get_character_name() != "Frodo") {
				cout << character_name << " försöker attackera " << person->get_character_name() << "!" << endl;
				if (fight(person))
					return true;
			}
		}

		for (auto & person : env->get_characters()) {
			if (person->get_character_name() == "Frodo") {
				cout << character_name << " attackerar Frodo!" << endl;
				cout << "- Hjääälp! Sam, var är du???" << endl;
				cout << "- Aaaaaaahh hjälp!!!! Saaaam!!" << endl;
				if (fight(person))
					return true;
			}
		}

		return Character::action();
	}
}