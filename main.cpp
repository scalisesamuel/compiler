#include<iostream>
#include<cstdio>
#include<string>
#include<fstream>
#include"semantic.h"
#include"parser.h"
#include"nodet.h"
#include"testtree.h"

using namespace std;

int main(int argc, char *argv[]){
	bool fileflg = false;
	string file;
	
	if(argc == 1){
		cout << "Enter text please.\n";
		ofstream of;
		
		file = "out";
		of.open("out.fs182");
		string input;
		
		while(getline(cin, input)){
			of <<input;
			of <<" ";
		}

		of.close();
	}
	else if(argc == 2){
		file = argv[1];
		fileflg = true;
	}
	else{
		cout <<"Error: to many arguments were given.\n";
	
		if(!fileflg){
			remove("out.fs182");
		}

		return 0;
	}
	
	ifstream f;
	string fullFile;
	fullFile = file + ".fs182";
	f.open(fullFile.c_str());
	
	if(!f.is_open()){
		cout <<"Error: File Failed to open.\n";
		
		if(!fileflg){
			remove("out.fs182");
		}

		return 0;
	}
	Parser trial (f);
	
	node *p = trial.getroot();
	testtree(p);
	Semantics check(p);

	f.close();

	if(!fileflg){
		remove("out.fs182");
	}
	return 0;
}
