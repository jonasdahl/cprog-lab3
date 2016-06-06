#include "lembas.h"

using namespace std;

namespace lotr {
	string Lembas::to_string() const {
		stringstream stream; 
		stream << "Lembasbröd." << endl;
		stream << Food::to_string();
		return stream.str();
	}
}