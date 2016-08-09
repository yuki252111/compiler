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
	int datatype;  //��������
	int intval;
	double doubval;
	char charval;
	
	int size;

	struct ast* func;
	struct symlist* syms;
};
struct arg{
	char* name;  //����������
	int datatype; //�����������ͣ�char��int��double,-1��ʾ��������
	char* tname; //�û������������ͣ���class�����֣�array�����֣�NULL��ʾ�����û�����
	int size;  //����Ĵ�С������������飬��Ϊ-1
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
//�������ڵ㣬����while��if
struct flow:public ast{
	//�����if��nodetype  'I'
	//�����while��nodetype 'W'
	struct ast* cond; //����
	struct ast* tl;      
	struct ast* el;
};
//for �ڵ�
struct _for:public ast{
	// 'O'
	char* index; //for��������õı������ƣ���i
	int start;   //��ʼֵ
	int end;   //����ֵ
	int step;  //����
	struct ast* tl; 
};
//foreach �ڵ�
struct _foreach:public ast{
	// 'E'
	char* index; //for��������õı������ƣ���i
	char* arr;  //���������
	struct ast* tl;
};
//���ú�������
struct fncall:public ast{
	//0
	struct ast* tl;
	enum bifs functype;
};
//�û����庯������
struct ufncall:public ast {
	//1
	struct ast* tl;
	char* name;
	char* fname;//------------------------change------------------------------------������ຯ������Ϊ������֣�����ΪNULL
};
//char ����
struct charcons:public ast{
		//2
	char ch;
};
//int ����
struct intcons:public ast{
		//3
	int num;
};
//double ����
struct doubcons:public ast{
		//4
	double doub;
};
//����������char��int��double
struct var:public ast{
	  //5
	int datatype;
	char* name;
};
//��������
struct arr:public ast{            //6
	
	int datatype;
	char* name;
	int size;
};
//������������������tl=NULL��������������tl��=NULL�������Ƕ���
struct fndec:public ast{
		//7;
	char* name;
	struct symlist* s;
	struct ast* tl;
	int type;   //0 (char) , 1 (int) , 2(double),-1(void)  -----------------------------------change-----------------------------------------
};
//���������൱�ڱ���������var a as tt��ֻ����tt��һ��class���ѣ�
struct csdec :public ast{
	 //8;
	char* vname;  //�������֣��൱��a
	char* cname;  //�����֣��൱��tt
};
//�ඨ��
struct csdef :public ast{
	//9;
	char* cname;      //������
	char* fname;      //�̳еĸ�������
	struct ast* tl;
};
//��ȡ���Ա
struct csget :public ast{
	//10
	char* cname;        //������
	char* kname;       //��Ա�������߳�Ա�������߳�Ա���������
	int func;             //���õĺ���������
	struct ast* explist; //�����Ĳ����������Ǻ�������NULL
	struct ast* index;  //������±꣬����������ΪNULL
};
//��ֵ���
struct symasgn:public ast{
	// '='
	char* name;   //��������
	char* cname; //�����ƣ���������ΪNULL
	struct ast* v;  //�ұߵı��ʽ
	struct ast* index;  //�����±꣬����������ΪNULL
};
//��������
struct symref :public ast{
	// ��N'
	char* name;  //��������
	struct ast* index; //�����±꣬����������ΪNULL
};
//ͼ�λ��Ĺ���
struct singlestring :public ast{
	char* str;
};
struct twostrings : public ast
{
	char* str1;
	char* str2;
};

struct ast* newfunc(struct pcdata*, int functype, struct ast* l);
struct ast* newcall(struct pcdata*, char* fname,char* s, struct ast* l);  //------change---------��Ӧ������޸�
struct ast* newint(struct pcdata*, int num);
struct ast* newdoub(struct pcdata*, double d);
struct ast* newchar(struct pcdata*, char ch);
struct ast* newvar(struct pcdata*,char* name, int type);
struct ast* newarr(struct pcdata*, char* name, int type, int size);
struct ast* newclass(struct pcdata*, char* vname, char* cname);
struct ast* newclassdef(struct pcdata*, char* cname, char* fname, struct ast* tl);
struct ast* newcsget(struct pcdata*, char* cname, char* kname,int func,struct ast* explist,struct ast* index);
struct ast* newasgn(struct pcdata*,char* cname, char* name, struct ast* v,struct ast* index);
struct ast* dodef(struct pcdata*, int type,char* name, struct symlist* syms, struct ast* stmts);//-------change---------��Ӧ������޸�
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