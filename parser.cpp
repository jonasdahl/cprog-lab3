#include "parser.h"

using namespace std;

namespace lotr {
	Parser::Parser() {

	}

	Object * Parser::parse(string & in) {
		input = in;
		char * buffer = new char[in.size()];
		unsigned int index = 0;
		string token;
		string res;
		while (index < in.size()) {
			cout << "Token: " << parse_token(&index, buffer) << endl;
		}
		cout << "Klar" << endl;
		return nullptr;
	}

	string Parser::parse_token(unsigned int * index, char * buffer) {
		cout << "Börjar på index " << *index;
		int i = 0;
		char c;
		while (*index < input.size()) {
			c = input[(*index)++];
			buffer[i++] = c;
			if (c == '{' || c == ':') {
				buffer[i] = '\0';
				break;
			}
		}
		std::string str(buffer);
		return str;
	}

	bool Parser::result() {
		return false;
	}
}