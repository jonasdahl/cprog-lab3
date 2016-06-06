#include "rohirrim.h"

using namespace std;

namespace lotr {
	int Rohirrim::eat(Object * const object) {
		Object * obj = find_object(object->get_name());
		if (obj == nullptr)
			return 0;
		int healing = obj->healing_effect();
		if (healing > 0) { 
			health += 2 * obj->healing_effect();
			if (health > max_health) 
				health = max_health;
			remove_item(object);
			cout << "Du är rohirrim så du fick dubbelt så mycket liv!" << endl;	
			return healing;
		}
		return Character::eat(object);
	}
}