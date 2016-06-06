#include "food.h"

using namespace std;

namespace lotr {
	string Food::to_string() const {
		stringstream stream; 
		stream << "Mat. " << endl;
		if (hp > 0)
			stream << "Helar " << hp << " hp." << endl;
		return stream.str();
	}
}