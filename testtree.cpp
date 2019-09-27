#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include"nodet.h"


static void display(node *, int);

void testtree(node *p){
	int level = 0;
	if(p != NULL){
		display(p, level);
	}
	else{
		std::cout <<"The Tree is empty\n";
	}
}

static void display(node *p, int level){
	if(p != NULL){
		//std::cout <<std::setw(level * 2) <<"" <<p->name <<":\t" <<p->content <<"\n";
		
		std::cout <<std::setw(level * 2) <<"" <<p->name <<"::\t";
		for ( std::vector<token>::iterator i = p->content.begin(); i != p->content.end(); ++i){
			token temp = *i;			
			std::cout <<temp.types[temp.tkid] <<":" <<temp.value <<"\t";
		}
		std::cout <<"\n";
		level = level + 5;
		display(p->child1, level);
		display(p->child2, level);
		display(p->child3, level);
		display(p->child4, level);
	}
}
