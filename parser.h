#ifndef PARSER
#define PARSER

#include "env.h"
#include "char.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "obj.h"

using namespace std;

namespace lotr {
	class Parser {
	public:
		Parser();
		
		Object * parse(string & in);

		string parse_token(unsigned int * index, char * buffer);

		bool result();
		
	private:
		string input;
	};
}

#endif