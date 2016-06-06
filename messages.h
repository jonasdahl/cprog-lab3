#ifndef MESSAGES
#define MESSAGES

using namespace std;

namespace lotr {
	class Messages {
	public:
		Game();
		string read_line();
		void play();
		void wait();
		void ctr();
		void print_intro();
		void print_gandalf();
		std::string getFileContents (std::ifstream& File);
	private:
		int turn;
		vector<Character *> characters;
		vector<Environment *> gameMap;
	};
}

#endif