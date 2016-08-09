#include "TableType.h"
#include "SymbolTableAnalyse.h"
#include "parser.h"
#include "lexer.h"
#include "defination.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "SemanticError.h"
using namespace std;

class IRGeneration{
private:
	ast* root;

	SymbolTableAnalyse* sta;
	SemanticError* se;

	vector<string> linkfiles;
	int index;
	bool infunc;
	int arrayindex;
	int ifindex;
	int elseindex;
	int whileindex;
	int cmpindex;
	int funcindex;
	int paraindex;
	int retcons;

	string getInt(int n);
	string getFile(string filename);

	int getCodeAss(ast* node, int& index, string& ir, char& ch, double& db);
	string getAllocaInt(string name);
	string getAllocaIntPointer(string name);
	string getAllocaIntArray(string name, int size);
	string getLoadInt(string name);
	string getLoadIntPointer(string name);
	string getStoreInt(string name, string value);
	string getStoreIntPointer(string name, string value);
	string getAllocaChar(string name);
	string getAllocaCharPointer(string name);
	string getAllocaCharArray(string name, int size);
	string getLoadChar(string name);
	string getLoadCharPointer(string name);
	string getStoreChar(string name, string value);
	string getStoreCharPointer(string name, string value);
	string getConstant();
	string getLinkFunc();
	string getCmp(ast* node, int curwhileindex);
	string getWhile(ast* node);
	string getIfCmp(ast* node, bool elseexist, int curifindex, int curelseindex);
	string getIf(ast* node);
	string getFunction(ast* node);
	void getCallAss(ast* node, string& ir1, string& ir2, int findex);
	string getCall(ast* node, int& pos);
public:
	IRGeneration(ast* root);
	void AddLinkFile(string filename);
	string Generate();

};