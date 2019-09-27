#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include"testscanner.h"
#include"scanner.h"
#include"token.h"

Testscanner::Testscanner(std::ifstream &f){
	bool eofflag = false;
	token complete_token;
	Scanner scan;

	while(!eofflag){
		complete_token = scan.tokencheck(f);
		
		std::cout <<"\n" <<std::setw(20) <<complete_token.types[complete_token.tkid] <<"\t" <<std::setw(8) <<complete_token.value <<"\t" <<std::setw(8) <<complete_token.line_num <<"\n";

		switch(complete_token.tkid){
			case F:
			case OPTKF:
			case IDTKF:
			case INTTKF:
				eofflag = true;
				break;
			default:
				eofflag = false;
		}
	}
}
