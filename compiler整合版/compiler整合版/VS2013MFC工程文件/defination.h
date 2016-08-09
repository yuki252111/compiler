#ifndef __DEFINATION_H__
#define __DEFINATION_H__
//----------------------------------------------------
#include <string>
using namespace std;


struct pcdata{
	void* scaninfo;
	struct symbol** symtab;
	struct ast* ast;
	string tokens;
};
struct symbol{
	char* name;
	int datatype;  //数据类型
	int intval;
	double doubval;
	char charval;
	
	int size;

	struct ast* func;
	struct symlist* syms;
};
struct arg{
	char* name;  //变量的名字
	int datatype; //内置数据类型，char，int，double,-1表示不是内置
	char* tname; //用户定义数据类型，如class的名字，array的名字，NULL表示不是用户定义
	int size;  //数组的大小，如果不是数组，则为-1
};
struct symlist{
	struct arg* cur;
	struct symlist* next;
};
#define MAX 9997


struct symbol* lookup(struct pcdata*, char*);
void insert(struct pcdata*, struct symbol* s);
struct symlist* newsymlist(struct pcdata*, struct arg* sym, struct symlist* next);
struct arg* newarg(struct pcdata*, char*, int, char*,int);
//----------------------------------------------------
enum  bifs
{
	B_sqrt=1,
	B_exp,
	B_log,
	B_print
};
struct un{
	int type;
	char ch;
	int num;
	double doub;
};
//-----------------------------------------------------
struct ast{
	int nodetype;
	struct ast* l;
	struct ast* r;
	int lineno;
};
//控制流节点，包括while和if
struct flow:public ast{
	//如果是if，nodetype  'I'
	//如果是while，nodetype 'W'
	struct ast* cond; //条件
	struct ast* tl;      
	struct ast* el;
};
//for 节点
struct _for:public ast{
	// 'O'
	char* index; //for里面的引用的变量名称，如i
	int start;   //起始值
	int end;   //结束值
	int step;  //步长
	struct ast* tl; 
};
//foreach 节点
struct _foreach:public ast{
	// 'E'
	char* index; //for里面的引用的变量名称，如i
	char* arr;  //数组的名字
	struct ast* tl;
};
//内置函数调用
struct fncall:public ast{
	//0
	struct ast* tl;
	enum bifs functype;
};
//用户定义函数调用
struct ufncall:public ast {
	//1
	struct ast* tl;
	char* name;
	char* fname;//------------------------change------------------------------------如果是类函数，则为类的名字，否则为NULL
};
//char 常量
struct charcons:public ast{
		//2
	char ch;
};
//int 常量
struct intcons:public ast{
		//3
	int num;
};
//double 常量
struct doubcons:public ast{
		//4
	double doub;
};
//变量声明，char，int，double
struct var:public ast{
	  //5
	int datatype;
	char* name;
};
//数组声明
struct arr:public ast{            //6
	
	int datatype;
	char* name;
	int size;
};
//函数定义和声明，如果tl=NULL，代表是声明，tl！=NULL，代表是定义
struct fndec:public ast{
		//7;
	char* name;
	struct symlist* s;
	struct ast* tl;
	int type;   //0 (char) , 1 (int) , 2(double),-1(void)  -----------------------------------change-----------------------------------------
};
//类声明（相当于变量声明，var a as tt，只不过tt是一个class而已）
struct csdec :public ast{
	 //8;
	char* vname;  //变量名字，相当于a
	char* cname;  //类名字，相当于tt
};
//类定义
struct csdef :public ast{
	//9;
	char* cname;      //类名字
	char* fname;      //继承的父类名字
	struct ast* tl;
};
//获取类成员
struct csget :public ast{
	//10
	char* cname;        //类名字
	char* kname;       //成员变量或者成员函数或者成员数组的名字
	int func;             //内置的函数的类型
	struct ast* explist; //函数的参数链表，不是函数则是NULL
	struct ast* index;  //数组的下标，不是数组则为NULL
};
//赋值语句
struct symasgn:public ast{
	// '='
	char* name;   //变量名称
	char* cname; //类名称，不是类则为NULL
	struct ast* v;  //右边的表达式
	struct ast* index;  //数组下标，不是数组则为NULL
};
//变量引用
struct symref :public ast{
	// ‘N'
	char* name;  //变量名字
	struct ast* index; //数组下标，不是数组则为NULL
};
//图形化的工具
struct singlestring :public ast{
	char* str;
};
struct twostrings : public ast
{
	char* str1;
	char* str2;
};

struct ast* newfunc(struct pcdata*, int functype, struct ast* l);
struct ast* newcall(struct pcdata*, char* fname,char* s, struct ast* l);  //------change---------对应定义的修改
struct ast* newint(struct pcdata*, int num);
struct ast* newdoub(struct pcdata*, double d);
struct ast* newchar(struct pcdata*, char ch);
struct ast* newvar(struct pcdata*,char* name, int type);
struct ast* newarr(struct pcdata*, char* name, int type, int size);
struct ast* newclass(struct pcdata*, char* vname, char* cname);
struct ast* newclassdef(struct pcdata*, char* cname, char* fname, struct ast* tl);
struct ast* newcsget(struct pcdata*, char* cname, char* kname,int func,struct ast* explist,struct ast* index);
struct ast* newasgn(struct pcdata*,char* cname, char* name, struct ast* v,struct ast* index);
struct ast* dodef(struct pcdata*, int type,char* name, struct symlist* syms, struct ast* stmts);//-------change---------对应定义的修改
struct ast* newref(struct pcdata*, char* name,struct ast* index);

struct ast* newast(struct pcdata*, int nodetype,struct ast* l, struct ast* r);
struct ast* newflow(struct pcdata*, int nodetype, struct ast* cond, struct ast* tl, struct ast* tr);
struct ast* newfor(struct pcdata*, char* index, int start, int end, int step, struct ast* tl);
struct ast* newforeach(struct pcdata*, char* index, char* arr, struct ast* tl);
struct ast* newcmp(struct pcdata*, int cmptype, struct ast* l, struct ast* r);

struct un eval(struct pcdata*, struct ast*);
void treefree(struct pcdata*, struct ast*);
void yyerror(struct pcdata* pp, char* s, ...);

void show(int);

#endif