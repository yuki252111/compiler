#ifndef TABLETYPE
#define TABLETYPE

#include <iostream>
#include <vector>
using namespace std;

enum stype{//symbol type
	FUNCTION,
	ATYPE,
	VARIABLE,
	CLASSDEF
};
struct para{
	string name;
	string type;
	int size;// -1 not array
};

struct func{
	string name;
	int returntype;
	int paranum;
	int index;
};
//overall
class SymbolTable{
public:
	vector<string> symbolName;
	vector<stype> symbolType;
};
//for array
class TypeTable{
public:
	vector<string> typeName;
	vector<int> typeNum;//size
	vector<string> typeInfo;//
};
class VariableTable{
public:
	vector<string> variableName;
	vector<string> variableType;
};
class FunctionTable{
public:
	vector<string> functionName;
	vector<int> functionReturn;
	//0 for void; 1 for int; 2 for char; 3 for double 
	vector<int> functionParaNum;
	vector<vector<string>> functionParaType;
	vector<vector<int>> functionParaSize;
	vector<vector<string>> functionParaName;
	vector<VariableTable*> functionVariable;
	vector<TypeTable*> functionType;
	vector<bool> functionState;
};

//for class 类的定义
class ClassTable{
public:
	vector<string>className;
	vector<string>fatherName;
	vector<SymbolTable*>classSymbol;
	vector<VariableTable*>classVariable;
	vector<TypeTable*>classType;
	vector<FunctionTable*>classFunction;
};
#endif