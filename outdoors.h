#ifndef OUTDOORS
#define OUTDOORS

#include "env.h"

#include <vector>
#include <map>
#include <iostream>

using namespace std;

namespace lotr {
	class Outdoors : public Environment {
	public:
		Outdoors(string const & n);
		virtual string get_weather() const;
	private:
		vector<string> weathers;
	};
}

#endif