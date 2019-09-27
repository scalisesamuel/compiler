#include<string>
#include<iostream>
#include<fstream>
#include"scanner.h"
#include"token.h"

Scanner::Scanner(){
	line = 1;
	current_token.types[0] = "ERROR: Unkown Character";
	current_token.types[1] = "ERROR: Comment";
	current_token.types[2] = "ERROR: Operator";
	current_token.types[3] = "ERROR: Integer";
	current_token.types[4] = "ERROR: Identifier";
	current_token.types[5] = "Keyword";
	current_token.types[6] = "Identifier";
	current_token.types[7] = "Integer";
	current_token.types[8] = "Operator";
	current_token.types[9] = "Identifier EOF";
	current_token.types[10] = "Integer EOF";
	current_token.types[11] = "Operator EOF";
	current_token.types[12] =  "EOF";
}

token Scanner::tokencheck(std::ifstream &f){
	
	int fsa_table [8][9] = {
		{1, -1, 2, 0, 3, -3, 7000, 4, -5},
		{1, 1, -1, 1000, -1, 1, 4000, 5, -5},
		{-2, -2, 2, 2000, -2, -2, 5000, 6, -5},
		{-3, -3, -3, 3000, -3,-3, 6000, 7, -5},
		{4, 4, 4, 4, 4, 4, -4, 0, -5},
		{5, 5, 5, 5, 5, 5, -4, 1, -5},
		{6, 6, 6, 6, 6, 6, -4, 2, -5},
		{7, 7, 7, 7, 7, 7, -4, 3, -5},
	};


	std::string key[12] = {"start", "stop", "loop", "void", "var", "return", "scan", "out", "program", "if", "then", "let"};

	bool tokenflg = false;
	int col;
	int row = 0;
	current_token.value = "";

	while(!tokenflg){
		nextchar(f);
		current_token.line_num = line;
		if(lookahead == '\n') { 
			line++;
		}

		if(islower(lookahead)) {
			col = 0;
		} else if(isupper(lookahead)){
			col = 1;
		} else if(isdigit(lookahead)){
			col = 2;
		} else if(lookahead == ' ' || lookahead == '\t' || lookahead == '\n'){
			col = 3;
		} else if(lookahead == '_') {
			col = 5;
		} else if(lookahead == '$'){
			col = 7;
		} else if(lookahead == EOF){
			col = 6;
		} else {
			char op [18] = {'=', '<', '>', ':', '+', '-', '*', '/', '%', '.', '(', ')', ',', '{', '}', ';', '[', ']'};
			col = 8;
			for(int i =0; i < 18; i++){
				if(op[i] == lookahead){ col = 4;}
			}
		
		}

			row = fsa_table[row][col];
			
			if(lookahead != '$'){

				switch(row){
					case -5: 
						tokenflg = true;
						current_token.tkid = UNKE;
						break;
					case -4: 
						tokenflg = true;
						current_token.tkid = COME;
						break;
					case -3: 
						tokenflg = true;
						current_token.tkid = OPE;
						break;
					case -2: 
						tokenflg = true;
						current_token.tkid = INTE;
						break;
					case -1:
						tokenflg = true;
						current_token.tkid = OPE;
						break;
					case 1000:
						tokenflg = true;
						current_token.tkid = IDTK;
				
						for(int i = 0; i < 12; i++){
							if(key[i] == current_token.value) { current_token.tkid = KEYTK;}
						}	
						break;
					case 2000:
						tokenflg = true;
						current_token.tkid = INTTK;
						break;
					case 3000:
						tokenflg = true;
						current_token.tkid = OPTK;
						break;
					case 4000:
						tokenflg = true;
						current_token.tkid = IDTKF;
						break;
					case 5000:
						tokenflg = true;
						current_token.tkid = INTTKF;
						break;
					case 6000:
						tokenflg = true;
						current_token.tkid = OPTKF;
						break;
					case 7000:
						tokenflg = true;
						current_token.tkid = F;
						break;	
					case 4:
					case 5:
					case 6:
					case 7:
						break;
					default:
						if(!(lookahead == ' ' || lookahead == '\t' || lookahead == '\n')){
							current_token.value += lookahead;
						}
				}
			}
	}
	return current_token;
}

void Scanner::nextchar(std::ifstream &f){
		lookahead = f.get();
}
