#include "wand.h"
#include "char.h"

using namespace std;

namespace lotr {
	int Wand::damage() const { 
		if (owner->get_mana() == 0) {
			cout << "Du kan inte använda din stav eftersom din mana är slut!" << endl;
			return 0;
		}
		if (owner->get_mana() < 5) {
			cout << "Tänk på att du inte kan använda din stav om du inte har någon mana!" << endl;
		}
		return Weapon::damage(); 
	}

	// Returns true if thing could be used as weapon
	bool Wand::use_weapon() {
		if (owner->get_mana() == 0) {
			cout << "Du kan inte använda din stav eftersom din mana är slut!" << endl;
			return false;
		}
		if (!owner->decrease_mana()) {
			cout << "Kunde inte använda trollstav." << endl;
			return false;
		}
		cout << "Du trollade lite och har " << owner->get_mana() << " mana kvar!" << endl;
		return Weapon::use_weapon(); 
	}
}