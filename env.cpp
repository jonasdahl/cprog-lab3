#include "env.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

namespace lotr {
	/**
	 * Destructor
	 */
	Environment::~Environment() {
	}

	/**
	 * Returns true if a character with given name is in environment.
	 * Name is case sensitive
	 */
	bool Environment::has_character(string const & name) const {
		for (auto & p : characters) {
			if (p->get_character_name() == name)
				return true;
		}
		return false;
	}

	/**
	 * Returns true if the given character is in environment.
	 */
	bool Environment::has_character_object(Character * const character) const {
		for (auto & p : characters) {
			if (p == character)
				return true;
		}
		return false;
	}

	/** 
	 * Adds object to list of items in environment
	 */
	void Environment::add_item(Object * const object) { 
		objects.push_back(object); 
	}

	/**
	 * Adds character to list of characters in environment
	 */
	void Environment::add_person(Character * const character) { 
		characters.push_back(character); 
		character_map.insert(make_pair(character->get_character_name(), character));
	}

	/**
	 * Sets environment for given direction
	 */
	void Environment::set_direction(string direction, Environment * env) {
		neighbours[direction] = env;
	}

	/**
	 * Adds character to environment and returns true if it was successful
	 */
	bool Environment::enter(Character * const character) {
		characters.push_back(character);
		return true;
	}

	/**
	 * Removes character from environment. 
	 * Returns false if character is not in environment.
	 */
	bool Environment::leave(Character * const character) {
		if (!has_character_object(character)) {
			return false;
		}
		characters.remove(character);
		return true;
	}

	/**
	 * Removes object from environment.
	 */
	bool Environment::pick_up(Object * const object) {
		if (!has_object(object)) 
			return false;
		objects.remove(object);
		return true;
	}

	/**
	 * Returns true if object is in environment.
	 */
	bool Environment::has_object(Object * const obj) const {
		for (auto & o : objects) {
			if (o == obj)
				return true;
		}
		return false;
	}

	/**
	 * Finds object in environment with given name.
	 * Returns nullptr if no such object was found.
	 */
	Object * Environment::find_object(string const & obj) const {
		for (auto & o : objects) {
			if (boost::iequals(o->get_name(), obj))
				return o;
		}
		return nullptr;
	}

	/**
	 * Finds character in environment with given name.
	 * Returns nullptr if no such character was found.
	 */
	Character * Environment::find_character(string const & character) {
		/*
		for (auto & o : characters) {
			if (boost::iequals(o->get_character_name(), character))
				return o;
		}
		return nullptr;
		*/
		return character_map[character];
	}

	/**
	 * Adds object to room.
	 */
	bool Environment::drop(Object * const object) {
		objects.push_back(object);
		return true;
	}

	/**
	 * Returns all possible directions for this environment.
	 */
	list<string> Environment::directions() const {
		list<string> dirs;
		for (auto & dir : neighbours) {
			dirs.push_back(dir.first);
		}
		return dirs;
	}

	/**
	 * Returns the neighbouring environment in the given direction.
	 * Returns nullptr if no neighbour in that direction was found.
	 */
	Environment * Environment::neighbour(string direction) {
		if (neighbours.find(direction) == neighbours.end())
			return nullptr;
		return neighbours[direction];
	}

	/**
	 * Returns a list of pointers to all the objects in this environment.
	 */
	list<Object *> Environment::get_objects() const {
		return objects;
	}

	/**
	 * Returns a list of pointers to all characters in this environment.
	 */
	list<Character *> Environment::get_characters() const {
		return characters;
	}

	/**
	 * Returns a map of the neighbouring environments and their directions.
	 */
	map<string, Environment *> Environment::get_directions() const {
		return neighbours;
	}
}