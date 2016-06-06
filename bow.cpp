#include "bow.h"
#include "char.h"
#include "ammunition.h"

using namespace std;

namespace lotr {
	int Bow::damage() const { 
		if (owner->get_quiver() == nullptr) {
			cout << "Tänk på att du inte kan använda pilbåge eftersom det saknas ett koger med pilar." << endl;
			return false;
		}
		Object * arrows = nullptr;
		for (auto & obj : owner->get_quiver()->get_content()) {
			if (obj != this && obj->get_amount() > 0 && (arrows == nullptr || arrows->damage() < obj->damage())) {
				arrows = obj;
			}
		}
		if (arrows == nullptr) {
			cout << "Tänk på att du inte kan använda din pilbåge om du inte har några pilar!" << endl;
			return 0;
		}
		int d = arrows->damage();
		if (d > maxDamage)
			d = maxDamage;
		if (d < minDamage)
			d = minDamage;
		return d; 
	}

	// Returns true if thing could be used as weapon
	bool Bow::use_weapon() {
		if (owner->get_quiver() == nullptr) {
			cout << "Kunde inte använda pilbåge eftersom det saknades ett koger med pilar." << endl;
			return false;
		}
		Object * arrows = nullptr;
		for (auto & obj : owner->get_quiver()->get_content()) {
			if (obj != this && obj->get_amount() > 0 && (arrows == nullptr || arrows->damage() < obj->damage())) {
				arrows = obj;
			}
		}
		if (arrows == nullptr) {
			cout << "Kunde inte använda pilbåge eftersom det saknades pilar!" << endl;
			return false;
		}
		
		if (arrows->use_weapon()) {
			cout << "Använde pilbåge. Nu har du " << arrows->get_amount() << " pil(ar) kvar i den bunten." << endl;
			return true;
		}
		cout << "Kunde inte använda pilbågen eftersom det inte fanns några pilar." << endl;
		return false;
	}

	string Bow::to_string() const {
		stringstream stream; 
		stream << name << " är en pilbåge som ägs av " << get_owner()->get_character_name() << "." << endl;
		stream << "Vikt: " << weight() << " kg." << endl;
		stream << "Skada: " << minDamage << "-" << maxDamage << " livspoäng beroende på pilar." << endl;
		stream << "Kräver ammunition för att kunna användas." << endl;
		return stream.str();
	}
}