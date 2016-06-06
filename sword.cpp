#include "sword.h"
#include <sstream>

using namespace std;

namespace lotr {
	string Sword::to_string() const {
		stringstream stream; 
		stream << Weapon::to_string() << endl;
		stream << "Det är ett svärd också" << endl;
		return stream.str();
	}
}