#include "obj.h"

#include<iostream>

using namespace std;

namespace lotr {
	Object::~Object() {
		cout << "Nu förstördes " << name << endl;
	}
	
	bool Object::operator==(Object const * o) const {
		return name == o->get_name();
	}

	std::ostream& operator<<(std::ostream & stream, const Object * object) { 
		stream << object->to_string();
	  	return stream;
	}
}