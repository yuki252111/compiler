#include "defination.h"
#include <iostream>
#include <fstream>
using namespace std;
#include "parser.h"
#include "lexer.h"
#include <string>
#include "IRGeneration.h"

void _read(ast* cur){
	if (cur->nodetype == '2'){
		cout << "!!" << (char)cur->l->nodetype << endl;
		cout << "!!" << (char)cur->r->nodetype << endl;
	}
	if (cur->nodetype == 1){
		struct ufncall* ufn = (struct ufncall*)cur;
		cout << "call: " << ufn->name << endl;
		cout << "call para: " << (char)ufn->tl->l->nodetype << endl;
		cout << "call para: " << (char)ufn->tl->r->nodetype << endl;
		_read(ufn->tl);
	}
	if (cur->nodetype == 2){
		struct charcons* cc = (struct charcons*)cur;
		cout << "const: " << cc->ch << endl;
	}
	if (cur->nodetype == 3){
		struct intcons* ic = (struct intcons*)cur;
		cout << "const: " << ic->num << endl;
	}
	if (cur->nodetype == 4){

	}
	if (cur->nodetype == 5){
		struct var* v = (struct var*)cur;
		cout << v->name << endl;
		return;
	}
	if (cur->nodetype == 6){
		struct arr* array = (struct arr*)cur;
		cout << "array: " << array->name << endl;

		return;
	}
	if (cur->nodetype == '+'){
		cout << "+" << endl;
		_read(cur->l);
		_read(cur->r);
	}
	if (cur->nodetype == 'N'){
		struct symref* sym = (struct symref*)cur;
		cout << "variable: " << sym->name << endl;
	}
	if (cur->nodetype == 'W'){
		struct flow* fl = (struct flow*)cur;
		ast* node1 = fl->cond;
		cout << "!" << (char)node1->nodetype << endl;
		ast* node2 = fl->tl;
		cout << "!" << (char)node2->nodetype << endl;
		return;
	}
	if (cur->nodetype == 'I'){
		struct flow* fl = (struct flow*)cur;
		ast* node1 = fl->cond;
		//cout << "!!" << (char)node1->nodetype << endl;
		_read(node1);
		ast* node2 = fl->tl;
		//cout << "!!" << (char)node2->nodetype << endl;
		_read(node2);
		ast* node3 = fl->el;
		if (node3){
			//cout << "!!" << (char)node3->nodetype << endl;
			_read(node3);
		}
		else
			cout << "!! no else!" << endl;
		return;
	}
	if (cur->nodetype == 'L'){
		_read(cur->l);
		_read(cur->r);
	}

}

void read(ast* node){
	if (node == NULL)
		return;
	switch (node->nodetype)
	{
	case 5:
	{
		struct var* v = (struct var*)node;
		cout << v->name << endl;
		return;
	}
	case 6:
	{
		struct arr* array = (struct arr*)node;
		cout << array->name << endl;
		return;
	}
	case 7:
	{
		struct fndec* fn = (struct fndec*)node;
		cout << "func: " << (string)fn->name << endl;
		//read(fn->tl);
		//cout << (char)fn->tl->nodetype << endl;
		//cout << node->r->nodetype << endl;
		ast* cur = fn->tl;
		struct symlist* list = fn->s;
		cout << "paralist:" << endl;
		while (list){
			cout << "	" << list->cur->name << "  " << list->cur->datatype << endl;
			list = list->next;
		}

		_read(cur);
		return;
	}
	case 'W':
	{
		struct flow* fl = (struct flow*)node;
		ast* node1 = fl->cond;
		cout << "!" << (char)node1->nodetype << endl;
		ast* node2 = fl->el;
		cout << "!" << (char)node2->nodetype << endl;
		return;
	}
	case 'L':
	{
		read(node->l);
		read(node->r);
		return;
	}
	}
}

int main()
{
	for (;;)
	{
		struct pcdata p = {
			NULL,
			NULL,
			NULL,
			""
		};
		static symbol* symtab[MAX];
		if (yylex_init_extra(&p, &p.scaninfo)){
			perror("init failed\n");
			return 0;
		}
		p.symtab = symtab;

		for (int i = 0; i < MAX; i++)
			p.symtab[i] = NULL;
		string filename;

		cout << "input the filename>";
		cin >> filename;
		FILE* f;
		fopen_s(&f, filename.c_str(), "r");
		yyset_in(f, p.scaninfo);
		yyparse(&p);
		ast* root = p.ast;
		cout << p.tokens << endl;
		//eval(&p, root);
		SemanticError se;
		SymbolTableAnalyse* sta = new SymbolTableAnalyse(&se);
		sta->Analyse(root);

		IRGeneration* irg = new IRGeneration(root);
		string ir = irg->Generate();
		char dstName[100];
		memset(dstName, 0, 100);
		int pos = filename.find(".");
		sprintf_s(dstName, "%s.ll", filename.substr(0, pos).c_str());
		ofstream ofs(dstName);
		ofs << ir << endl;
		cout << ir << endl;
	}
}