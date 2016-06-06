#include "container.h"

using namespace std;

namespace lotr {
	bool Container::contains(Object * const obj) const { 
		for (auto & o : content) {
			if (obj == o)
				return true;
		}
		return false;
	}

	float Container::get_total_weight() const {
		float sum = 0;
		for (auto & o : content) {
			sum += o->weight();
		}
		return sum;
	}

	string Container::to_string() const { 
		stringstream stream; 
		stream << "Kapacitet: " << volume_cap << "." << endl;
		stream << "Maxvikt: " << maxWeight << "kg." << endl;
		return stream.str();
	}
}