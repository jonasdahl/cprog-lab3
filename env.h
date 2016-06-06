#ifndef ENVIRONMENT
#define ENVIRONMENT

#include "obj.h"
#include "char.h"
#include <list>
#include <map>
#include <string>

using namespace std;

namespace lotr {
	class Character;

	class Object;

	class Environment {
	public:
		Environment(string const & n) : name(n) { ring_destr = false; }
		virtual ~Environment();

		bool enter(Character * const character);
		bool leave(Character * const character);
		void set_direction(string, Environment *);
		virtual bool pick_up(Object * const object);
		virtual bool drop(Object * const object);

		void add_item(Object * const object);
		void add_person(Character * const character);
		bool has_object(Object * const obj) const;
		Object * find_object(string const & obj) const;
		Character * find_character(string const & character);
		virtual string get_weather() const = 0;

		virtual bool ring_destroyed() const { return ring_destr; }
		virtual bool destroy_ring(Object * const object) { return false; }

		virtual list<string> directions() const;
		virtual Environment * neighbour(string direction);
		virtual string description() const = 0;

		list<Object *> get_objects() const;
		list<Character *> get_characters() const;
		bool has_character(string const & name) const;
		bool has_character_object(Character * const character) const;
		map<string, Environment *> get_directions() const;
		string get_name() const { return name; }
		virtual string save_string() { return "{Environment:{name: '" + name + "', objects: " + objects + ", characters: " + characters + ", neighbours: " + neighbours +
		 										", character_map: " + character_map + "}}"; }

	protected:
		bool ring_destr;
		string name;
		list<Object *> objects;
		list<Character *> characters;
		map<string, Environment *> neighbours;
		map<string, Character *> character_map;
	};
}

#endif