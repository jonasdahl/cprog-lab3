#include "man.h"
#include "poison.h"
#include "sword.h"

using namespace std;

namespace lotr {
	bool Man::commandBake() {
		cout << "Du bakar ett äckligt bröd som till och med är giftigt! Du lägger det på marken." << endl;
		Object * bread = new Poison("Äckligt, giftigt bröd " + std::to_string(rand() % 100), 2);
		get_env()->add_item(bread);
		game->createObject(bread);

		read_line();
		wait();
		return true;
	}

	bool Man::commandForge() {
		cout << "Du smider ett trubbigt svärd!" << endl;
		Object * sword = new Sword("Trubbigt svärd " + std::to_string(rand() % 100), 3, 1, 2, 2.0);
		get_env()->add_item(sword);
		game->createObject(sword);
		
		read_line();
		wait();
		return true;
	}
}