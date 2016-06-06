#include "elf.h"

using namespace std;

namespace lotr {	
	int Elf::eat(Object * const object) {
		Object * obj = find_object(object->get_name());
		if (obj == nullptr)
			return 0;

		int healing = obj->healing_effect();
		if (healing < 0) { 
			cout << object->get_name() << " var gift men eftersom du är en alv" 
				<< " så upptäckte du det innan du hann äta." << endl;
			return 0;
		}
		return Character::eat(object);
	}

	bool Elf::commandBake() {
		cout << "Du bakar en svingod lembas och lägger den på marken!" << endl;
		Object * lembas = new Lembas("Nybakad lembas " + std::to_string(rand() % 100), 2);
		get_env()->add_item(lembas);
		game->createObject(lembas);
		
		read_line();
		wait();
		return true;
	}
}