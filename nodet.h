#ifndef NODET_H
#define NODET_H

#include<string>
#include<vector>
#include"token.h"

struct node {
	std::string name;
	std::vector<token> content;
	node *child1;
	node *child2;
	node *child3;
	node *child4;
	void destroy();
};

#endif
