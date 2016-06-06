#include "mountain.h"

using namespace std;

namespace lotr {
	bool Mountain::destroy_ring(Object * const object) { 
		ring_destr = object->get_name() == "Härskarringen";
		return ring_destr; 
	}
}