#ifndef OBJECT
#define OBJECT

#include <string>

using namespace std;

namespace lotr {
	class Character;

	class Object {
	public:
		// Creates new object with given name
		Object(string const & name_) : name(name_) {}
		// Destroys object
		virtual ~Object();

		// Pure virtual, needs to be implemented
		// Returns the weight of this object
		virtual double weight() const = 0;

		// True if this object can contain other objects
		virtual bool is_container() const { return false; }
		// True if this object needs a backpack
		virtual bool needs_backpack() const { return true; }
		// True if this object can contain ammunition
		virtual bool is_quiver() const { return false; }
		// Returns true if object is arrow and needs to be placed quiver
		virtual int needs_quiver() const { return false; }

		// Returns the damage of this object
		virtual int damage() const { return 0; }
		// Returns the healing effect of this object
		virtual int healing_effect() const { return 0; }

		// Gets name of object
		string get_name() const { return name; }
		// Compares this object to another object
		bool operator==(Object const * o) const;
		// Sets owner for this object
		void set_owner(Character * const own) { owner = own; }
		// Gets owner for this object
		Character * get_owner() const { return owner; }

		// Returns a string representation of this object
		virtual string to_string() const { return name; }
		// Returns true if ammunition
		virtual int get_amount() const { return 0; }
		// Returns true if thing could be used as weapon
		virtual bool use_weapon() { return false; }

		virtual string save_string() { return "{Object:{name: '" + name + "', owner: " + owner + "}}"; }

		friend std::ostream & operator<<(std::ostream & o, const Object *);
	protected:
		string name;
		Character * owner;
	};

	std::ostream & operator<<(std::ostream & o, const Object *);
}

#endif