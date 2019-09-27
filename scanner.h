#ifndef SCANNER_H
#define SCANNER_H

#include<fstream>
#include"token.h"

class Scanner {
	private:
		token current_token;
		int line;
		char lookahead;
	public:
		Scanner();
		token tokencheck(std::ifstream&);
		void nextchar(std::ifstream&);
};
#endif
