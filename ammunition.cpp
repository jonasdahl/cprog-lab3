#include "ammunition.h"

using namespace std;

namespace lotr {
	string Ammunition::to_string() const {
		stringstream stream; 
		stream << amount << " pilar." << endl;
		stream << "Kan användas tillsammans med en pilbåge i fight." << endl;
		stream << "Skadar " << damage_ << " hp inom pilbågens intervall." << endl;
		return stream.str();
	}
}