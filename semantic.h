#ifndef SEMANTIC_H
#define SEMANTIC_H

#include<string>
#include<vector>
#include"nodet.h"
#include"token.h"

class Semantics{
	private:
		int global_count;
		bool fail_flag;
		std::vector<token> global;
	public:
	Semantics(node *);
	void globals(node *);
	void insert(node *);
	bool verify(token);
};

#endif
