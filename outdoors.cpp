#include "outdoors.h"

using namespace std;

namespace lotr {
	Outdoors::Outdoors(string const & n) : Environment(n) {
		weathers = {"är soligt", "är växlande molnighet", "regnar", "snöar", "blåser extremt mycket", "blåser extremt lite", "är orkan", "haglar"};
	}

	string Outdoors::get_weather() const {
		return weathers[rand() % weathers.size()];
	}
}