#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include"semantic.h"
#include"token.h"
#include"nodet.h"

Semantics::Semantics(node *root){
	fail_flag = false;
	global_count = 0;
	if(root != NULL){
		globals(root);
	}
	else{
		std::cout <<"The tree was empty\n";
	}
}

void Semantics::globals(node *p){
	if(p != NULL){
		if(p->name == "vars"){
			insert(p);
		}
		else{
			for(std::vector<token>::iterator i = p->content.begin(); i != p->content.end(); ++i){
				token temp = *i;
				bool exist = false;
				if(temp.tkid == IDTK){
					for(std::vector<token>::iterator it = global.begin(); it != global.end(); ++it){
						token globtemp = *it;
						if(globtemp.value == temp.value){
							exist = true;
						}	
					}
					if(!exist){
						std::cout <<"ERROR:: Semantics: at (" <<temp.line_num <<") " <<temp.value <<" is not declared.\n";
					}
				}
			}
		}
		globals(p->child1);
		globals(p->child2);
		globals(p->child3);
		globals(p->child4);
	}
}

void Semantics::insert(node *p){
	if(p != NULL){
			
		for(std::vector<token>::iterator i = p->content.begin(); i != p->content.end(); ++i){
			token temp = *i;
			if(temp.tkid == IDTK){
				if(global_count == 0){
					global.push_back(temp);
					global_count++;
				}	
				else{
					bool ver = verify(temp);
					if(ver){
						global.push_back(temp);
					}
				}
			}
		}
	}
	
}


bool Semantics::verify(token current_token){
	bool verify = true;
	for(std::vector<token>::iterator it = global.begin(); it != global.end(); ++it){
		token globtemp = *it;
		if(current_token.value == globtemp.value){
			fail_flag = true;
			verify = false;
			std::cout <<"ERROR:Semantics: at " <<globtemp.line_num <<": " <<globtemp.value <<" has already been declared\n"; 
		}
	} 
	return verify;
}

