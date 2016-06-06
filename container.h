#ifndef CONTAINER
#define CONTAINER

#include "obj.h"

#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace lotr {
	class Container : public Object {
	public:
		Container(string const & name_, int const volume, float const weight_) : 
			Object(name_), volume_cap(volume), maxWeight(weight_) {}

		// True as this is a container
		virtual bool is_container() const { return true; }
		// Adds item to list of items
		virtual bool add_item(Object * const obj) { content.push_back(obj); return true; }
		// Returns a copy of the contents in this container
		list<Object *> get_content() const { return content; }
		// Removes an item from this container
		virtual bool remove_item(Object * obj) { content.remove(obj); return true; }

		// True if this container contains obj
		bool contains(Object * const obj) const;
		// Number of things in this content
		int used_space() const { return content.size(); }
		// Space left
		int backspace() const { return volume_cap - used_space(); }
		// Gets the total weight for content in this container
		float get_total_weight() const;
		// Weight left in container
		int backweight() const { return maxWeight - get_total_weight(); }
		// Returns the weight of this object
		virtual double weight() const override { return used_space(); }

		// Returns a string representation of this object
		virtual string to_string() const;
	protected:
		int volume_cap;
		float maxWeight;
		list<Object *> content;
	};
}

#endif