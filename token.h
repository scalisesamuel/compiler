#ifndef TOKEN_H
#define TOKEN_H

#include<string>

enum id {UNKE, COME, OPE, INTE, IDE, KEYTK, IDTK, INTTK, OPTK, IDTKF, INTTKF, OPTKF, F}; 

struct token {
	enum id tkid; 
	std::string types[13];
	std::string value;
	int line_num;
};

#endif
