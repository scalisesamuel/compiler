#ifndef PARSER_H
#define PARSER_H

#include<fstream>
#include<string>
#include"token.h"
#include"scanner.h"
#include"nodet.h"

class Parser {
	private:
		token current_token;
		Scanner scan;
		node *root;
		bool error_flag;
	public:
		Parser(std::ifstream&);
		~Parser();
		node *program(std::ifstream&);
		node *block(std::ifstream&);
		node *vars(std::ifstream&);
		node *expr(std::ifstream&);
		node *A(std::ifstream&);
		node *M(std::ifstream&);
		node *R(std::ifstream&);
		node *stats(std::ifstream&);
		node *mStat(std::ifstream&);
		node *stat(std::ifstream&);
		node *assign(std::ifstream&);
		node *in(std::ifstream&);
		node *out(std::ifstream&);
		node *If(std::ifstream&);
		node *loop(std::ifstream&);
		node *RO(std::ifstream&);
		void error();
		node *setnode(std::string);
		void setcontent(node *);
		void dtree(node *);
		node *getroot();
};
#endif
