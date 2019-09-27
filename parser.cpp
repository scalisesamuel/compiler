#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include"parser.h"
#include"scanner.h"
#include"token.h"

Parser::Parser(std::ifstream &f){
	error_flag = false;
	current_token = scan.tokencheck(f);
	root = program(f);
	if(current_token.tkid == F){}
	else { error();}
	if(error_flag){
		dtree(root);
		root = NULL;
	}
}

node *Parser::setnode(std::string id){
	node *p = new node;
	p->name = id;
	p->child1 = NULL;
	p->child2 = NULL;
	p->child3 = NULL;
	p->child4 = NULL;
}

void Parser::setcontent(node *p){
	//p->content = p->content + current_token.types[current_token.tkid] + ":" + current_token.value + "\t";
	p->content.push_back(current_token);
}

node *Parser::program(std::ifstream &f){
	node *p = setnode("program");
	if(current_token.tkid == KEYTK){
		if(current_token.value == "void"){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = vars(f);
			p->child2 = block(f);
		}
		else{error();}
	}
	else{ error();}
	return p;
}

node *Parser::block(std::ifstream &f){
	node *p = setnode("block");
	if(current_token.tkid == KEYTK){
		if(current_token.value == "start"){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = vars(f);
			p->child2 = stats(f);
			if(current_token.tkid == KEYTK){
				if(current_token.value == "stop"){
					setcontent(p);
					current_token = scan.tokencheck(f);
				}
				else{error();}
			}
			else{error();}
		}
		else{error();}
	}
	else{error();}
	return p;
}

node *Parser::vars(std::ifstream &f){
	if(current_token.tkid == KEYTK){
		if(current_token.value == "var"){
			node *p = setnode("vars");
			setcontent(p);
			current_token = scan.tokencheck(f);
			if(current_token.tkid == IDTK){
				setcontent(p);
				current_token = scan.tokencheck(f);
				if(current_token.value == ":"){
					setcontent(p);
					current_token = scan.tokencheck(f);
					if(current_token.tkid == INTTK){
						setcontent(p);
						current_token = scan.tokencheck(f);
						p->child1 = vars(f);
					}
					else {error();}
				}
				else{error();}
			}
			else{error();}
			return p;
		}
		else{
			return NULL;
		}
	}
	else{
		return NULL;
	}
}

node *Parser::expr(std::ifstream &f){
	node *p = setnode("expr");
	p->child1 = A(f);
	if(current_token.tkid == OPTK){
		if(current_token.value == "/"){
			current_token = scan.tokencheck(f);
			p->child2 = expr(f);
		}
		else if(current_token.value == "*"){
			current_token = scan.tokencheck(f);
			p->child2 = expr(f);
		}
	}
	return p;
}

node *Parser::A(std::ifstream &f){
	node *p = setnode("A");
	p->child1 = M(f);
	if(current_token.tkid == OPTK){
		if(current_token.value == "+"){
			current_token = scan.tokencheck(f);
			p->child2 = A(f);
		}
		else if(current_token.value == "-"){
			current_token = scan.tokencheck(f);
			p->child2 = A(f);
		}
	}
	return p;
}

node *Parser::M(std::ifstream &f){
	node *p = setnode("M");
	if(current_token.tkid == OPTK){
		if(current_token.value == "-"){
			current_token = scan.tokencheck(f);
			p->child1 = M(f);
		}
		else{p->child1 = R(f);}
	}
	else{p->child1 = R(f);}
	return p;
}

node *Parser::R(std::ifstream &f){
	node *p = setnode("R");
	if(current_token.tkid == OPTK){
		if(current_token.value == "("){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = expr(f);
			if(current_token.tkid == OPTK){
				if(current_token.value == ")"){
					setcontent(p);
					current_token = scan.tokencheck(f);
				}
				else{error();}
			}
			else{error();}
		}
		else{error();}
	}
	else if(current_token.tkid == IDTK){
		setcontent(p);
		current_token = scan.tokencheck(f);
	}
	else if(current_token.tkid == INTTK){
		setcontent(p);
		current_token = scan.tokencheck(f);
	}
	else{error();}
	return p;
}

node *Parser::stats(std::ifstream &f){
	node *p = setnode("stats");
	p->child1 = stat(f);
	p->child2 = mStat(f);
	return p;
}

node *Parser::mStat(std::ifstream &f){
	if(current_token.tkid == KEYTK){
		if(current_token.value == "if" || current_token.value == "out" || current_token.value == "start" || current_token.value == "scan" || current_token.value == "loop" || current_token.value == "let"){
			node *p = setnode("mStat");
			p->child1 = stat(f);
			p->child2 = mStat(f);
			return p;
		}
		else{ return NULL;}
	}
	else{ return NULL;}
}

node *Parser::stat(std::ifstream &f){
	node *p = setnode("stat");
	if(current_token.tkid == KEYTK){
		if(current_token.value == "if"){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = If(f);
		}
		else if(current_token.value == "out"){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = out(f);
		}
		else if(current_token.value == "start"){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = block(f);
		}
		else if(current_token.value == "scan"){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = in(f);
		}
		else if(current_token.value == "loop"){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = loop(f);
		}
		else if(current_token.value == "let"){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = assign(f);
		}
		else{error();}
	}
	else{error();}
	return p;
}

node *Parser::assign(std::ifstream &f){
	node *p = setnode("assign");
	if(current_token.tkid == IDTK){
		setcontent(p);
		current_token = scan.tokencheck(f);
		if(current_token.tkid == OPTK){
			if(current_token.value == "="){
				setcontent(p);
				current_token = scan.tokencheck(f);
				p->child1 = expr(f);
				if(current_token.tkid == OPTK){
					if(current_token.value == "."){
						setcontent(p);
						current_token = scan.tokencheck(f);
					}
				}
				else{error();}
			}
			else{error();}
		}
		else{error();}
	}
	else{error();}
	return p;
}

node *Parser::in(std::ifstream &f){
	node *p = setnode("in");
	if(current_token.tkid == IDTK){
		setcontent(p);
		current_token = scan.tokencheck(f);
		if(current_token.tkid == OPTK){
			if(current_token.value == "."){
				setcontent(p);
				current_token = scan.tokencheck(f);
			}
			else{error();}
		}
		else{error();}
	}
	else{error();}
	return p;
}

node *Parser::out(std::ifstream &f){
	node *p = setnode("out");
	if(current_token.tkid == OPTK){
		if(current_token.value == "["){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = expr(f);
			if(current_token.tkid == OPTK){
				if(current_token.value == "]"){
					setcontent(p);
					current_token = scan.tokencheck(f);
					if(current_token.tkid == OPTK){
						if(current_token.value == "."){
							setcontent(p);
							current_token = scan.tokencheck(f);
						}
						else{error();}
					}
					else{error();}
				}
				else{error();}
			}
			else{error();}
		}
		else{error();}
	}
	else{error();}
	return p;
}

node *Parser::If(std::ifstream &f){
	node *p = setnode("if");
	if(current_token.tkid == OPTK){
		if(current_token.value == "("){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = expr(f);
			p->child2 = RO(f);
			p->child3 = expr(f);
			if(current_token.tkid == OPTK){
				if(current_token.value == ")"){
					setcontent(p);
					current_token = scan.tokencheck(f);
					p->child4 = stat(f);
				}
				else{error();}
			}
			else{error();}
		}
		else{error();}
	}
	else{error();}
	return p;
}

node *Parser::loop(std::ifstream &f){
	node *p = setnode("loop");
	if(current_token.tkid == OPTK){
		if(current_token.value == "("){
			setcontent(p);
			current_token = scan.tokencheck(f);
			p->child1 = expr(f);
			p->child2 = RO(f);
			p->child3 = expr(f);
			if(current_token.tkid == OPTK){
				if(current_token.value == ")"){
					setcontent(p);
					current_token = scan.tokencheck(f);
					p->child4 = stat(f);
				}
				else{error();}
			}
			else{error();}
		}
		else{error();}	
	}
	else{error();}
	return p;
}

node *Parser::RO(std::ifstream &f){
	node *p = setnode("RO");
	if(current_token.tkid == OPTK){
		if(current_token.value == "<"){
			setcontent(p);
			current_token = scan.tokencheck(f);
			if(current_token.tkid == OPTK){
				if(current_token.value == "="){
					setcontent(p);
					current_token = scan.tokencheck(f);
				}
			}
		}
		else if(current_token.value == ">"){
			setcontent(p);
			current_token = scan.tokencheck(f);
			if(current_token.tkid == OPTK){
				if(current_token.value == "="){
					setcontent(p);
					current_token = scan.tokencheck(f);
				}
			}
		}
		else if(current_token.value == "="){
			setcontent(p);
			current_token = scan.tokencheck(f);
			if(current_token.tkid == OPTK){
				if(current_token.value == "="){
					setcontent(p);
					current_token = scan.tokencheck(f);
				}
			}
		}
		else{error();}
	}
	else{error();}
	return p;
}

void Parser::error(){
	error_flag = true;
	std::cout <<"Parser Error:\t" <<current_token.types[current_token.tkid] <<"\t" <<current_token.value <<"\t" <<current_token.line_num <<"\n";
}

Parser::~Parser(){
	dtree(root);
}

void Parser::dtree(node *p){
	if(p != NULL){
		dtree(p->child1);
		dtree(p->child2);
		dtree(p->child3);
		dtree(p->child4);
		p->destroy();	
	}
}

node *Parser::getroot(){ return root;}
