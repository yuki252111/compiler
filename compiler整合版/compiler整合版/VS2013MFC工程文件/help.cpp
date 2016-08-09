#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "defination.h"
#include "parser.h"
#include "lexer.h"

static bool first = true;

struct symbol* lookup(struct pcdata* pp, char* sym)
{
	
	struct symbol* sp = NULL;
	for (int i = 0; i < MAX; i++)
	{
		sp = pp->symtab[i];
		if (sp != NULL&&!strcmp(sp->name, sym))
			return sp;
	}
	return NULL;
}
void insert(struct pcdata* pp, struct symbol* s)
{
	for (int i = 0; i < MAX; i++)
	{
		if (pp->symtab[i] == NULL)
		{
			pp->symtab[i] = s;
			return;
		}
	}
	yyerror(pp, "symbol table is full\n");
	exit(0);
}
struct symlist* newsymlist(struct pcdata* pp, struct arg* sym, struct symlist*  next)
{
	struct symlist* sl = (struct symlist*)malloc(sizeof(struct symlist));
	if (!sl)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	sl->cur = sym;
	sl->next = next;
	return sl;
}
struct arg* newarg(struct pcdata*pp, char* vname, int datatype, char* tname,int size)
{
	struct arg* a = (struct arg*)malloc(sizeof(struct arg));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->datatype = datatype;
	a->name = vname;
	a->tname = tname;
	a->size = size;
	return a;
}
void symlistfree(struct pcdata* pp, struct symlist* sl)
{
	struct symlist* nsl;
	while (sl)
	{
		nsl = sl->next;
		free(sl);
		sl = nsl;
	}
}
////////-----------------------------------
struct ast* newchar(struct pcdata* pp, char c)
{
	struct charcons* a = (struct charcons*)malloc(sizeof(charcons));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = 2;
	a->ch = c;
	a->l = NULL;
	a->r = NULL;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newint(struct pcdata* pp, int num)
{
	struct intcons* a = (struct intcons*)malloc(sizeof(intcons));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = 3;
	a->num = num;
	a->l = NULL;
	a->r = NULL;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newdoub(struct pcdata* pp, double d)
{
	struct doubcons* a = (struct doubcons*)malloc(sizeof(doubcons));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = 4;
	a->doub = d;
	a->l = NULL;
	a->r = NULL;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newvar(struct pcdata* pp, char* name,int type)
{
	struct var* v = (struct var*)malloc(sizeof(struct var));
	if (!v)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	v->nodetype = 5;
	v->name = name;
	v->datatype = type;
	v->l = NULL;
	v->r = NULL;
	v->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)v;
}
struct ast* newarr(struct pcdata* pp, char* name, int type, int size)
{
	struct arr*	ar = (struct arr*)malloc(sizeof(struct arr));
	if ( !ar)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	
	ar->nodetype = 6;
	ar->name = name;
	ar->datatype = type;
	ar->size = size;
	ar->l = NULL;
	ar->r = NULL;
	ar->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)ar;
}
struct ast* dodef(struct pcdata* pp, int type,char* name, struct symlist* syms, struct ast*func)
{
	struct fndec * a = (struct fndec*)malloc(sizeof(struct fndec));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = 7;
	a->s = syms;
	a->name = name;
	a->tl= func;
	a->type = type;
	a->l = NULL;
	a->r = NULL; 
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newclass(struct pcdata* pp, char* vname, char* cname)
{
	struct csdec* a = (struct csdec*)malloc(sizeof(struct csdec));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = 8;
	a->l = NULL;
	a->r = NULL;
	a->vname = vname;
	a->cname = cname;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newclassdef(struct pcdata* pp, char* cname, char* fname, struct ast* tl)
{
	struct csdef* a = (struct csdef*)malloc(sizeof(struct csdef));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = 9;
	a->l = NULL;
	a->r = NULL;
	a->cname = cname;
	a->fname = fname;
	a->tl = tl;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newcsget(struct pcdata*pp, char* cname, char* kname, int func, struct ast* explist,struct ast* index)
{
	struct csget* a = (struct csget*)malloc(sizeof(struct csget));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = 10;
	a->l = NULL;
	a->r = NULL;
	a->cname = cname;
	a->kname = kname;
	a->func = func;
	a->explist = explist;
	a->index = index;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newasgn(struct pcdata* pp,char* cname, char* name, struct ast* v,struct ast* index)
{
	struct symasgn* a = (struct symasgn*)malloc(sizeof(struct symasgn));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	struct symbol* s = lookup(pp, name);
	a->nodetype = '=';
	a->name = name;
	a->cname = cname;
	a->v = v;
	a->index = index;
	a->l = NULL;
	a->r = NULL;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newfunc(struct pcdata* pp, int functype, struct ast* l)
{
	struct fncall* a = (struct fncall*)malloc(sizeof(struct fncall));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = 0;
	a->tl = l;
	a->functype = bifs(functype);
	a->l = NULL;
	a->r = NULL;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newcall(struct pcdata*pp, char* fname,char* s, struct ast* l)
{
	struct ufncall* a = (struct ufncall*)malloc(sizeof(struct ufncall));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = 1;
	a->tl = l;
	a->name = s;
	a->fname = fname;
	a->l = NULL;
	a->r = NULL;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newref(struct pcdata* pp, char* name,struct ast* index)
{
	struct symref* a = (struct symref*)malloc(sizeof(symref));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->name = name;
	a->nodetype = 'N';
	a->index = index;
	a->l = NULL;
	a->r = NULL;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
//--------------------------------------------
struct ast* newast(struct pcdata* pp, int nodetype, struct ast*l, struct ast* r)
{
	struct ast* a = (struct ast*)malloc(sizeof(struct ast));
	if (a == NULL)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = nodetype;
	a->l = l;
	a->r = r;
	a->lineno = yyget_lineno(pp->scaninfo);
	return a;
}
struct ast* newflow(struct pcdata* pp, int nodetype, struct ast* cond, struct ast* tl, struct ast* el)
{
	struct flow* a = (struct flow*)malloc(sizeof(struct flow));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = nodetype;
	a->cond = cond;
	a->tl = tl;
	a->el = el;
	a->l = NULL;
	a->r = NULL;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newfor(struct pcdata* pp, char* index, int start, int end, int step, struct ast* tl)
{
	struct _for* a = (struct _for*)malloc(sizeof(struct _for));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = 'O';
	a->index = index;
	a->start = start;
	a->end = end;
	a->step = step;
	a->tl = tl;
	a->l = NULL;
	a->r = NULL;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newforeach(struct pcdata* pp, char* index, char* arr, struct ast* tl)
{
	struct _foreach* a = (struct _foreach*)malloc(sizeof(struct _foreach));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = 'E';
	a->arr = arr;
	a->index = index;
	a->tl = tl;
	a->l = NULL;
	a->r = NULL;
	a->lineno = yyget_lineno(pp->scaninfo);
	return (struct ast*)a;
}
struct ast* newcmp(struct pcdata* pp, int cmptype, struct ast* l, struct ast* r)
{
	struct ast* a = (struct ast*)malloc(sizeof(struct ast));
	if (!a)
	{
		yyerror(pp, "out of space\n");
		exit(0);
	}
	a->nodetype = '0' + cmptype;
	a->l = l;
	a->r = r;
	a->lineno = yyget_lineno(pp->scaninfo);
	return a;
}

//-------------------

static un callbuiltin(struct pcdata* pp, struct fncall*);
static un calluser(struct pcdata* pp, struct ufncall*);

struct un eval(struct pcdata*pp, struct ast* a)
{
		struct un r1, r2;
		r1.type = -1;
		r2.type = -1;
		if (!a)
		{
			yyerror(pp, "invalid tree");
			exit(0);
		}
		switch (a->nodetype){
		case 0:	r1 = callbuiltin(pp, (struct fncall*)a); return r1;
		case 1:	r1 = calluser(pp, (struct ufncall*)a); return r1;
		case 'N':
		{
			struct symbol* s = lookup(pp, ((struct symref*)a)->name);
			if (s == NULL)
			{
				yyerror(pp, "%s variable undefined", ((struct symref*)a)->name);
				exit(0);
			}
			if (s->size != 0 && ((struct symref*)a)->index == NULL)
			{
				yyerror(pp, "%s cannot be dereference", ((struct symref*)a)->name);
				exit(0);
			}
			int index = 0;
			if (s->size != 0)
			{
				struct un tmp = eval(pp, ((struct symref*)a)->index);
				if (tmp.type != 1 || tmp.num >= s->size || tmp.num < 0)
				{
					yyerror(pp, "%s is out of range", ((struct symref*)a)->name);
					exit(0);
				}
				index = tmp.num;
			}
			else
				index = 0;
			r1.type = (s + index)->datatype;
			r1.ch = (s + index)->charval;
			r1.num = (s + index)->intval;
			r1.doub = (s + index)->doubval;
			return r1;
		}
		case 'R':
		{
			r1= eval(pp, a->l);
			return r1;
		}
		case 2:
			r1.type = 0; r1.ch = ((struct charcons*)a)->ch; return r1;
		case 3:
			r1.type = 1; r1.num = ((struct intcons*)a)->num; return r1;
		case 4:
			r1.type = 2; r1.doub = ((struct doubcons*)a)->doub; return r1;
		case 5:
		{
			struct var * v = (struct var*)a;
			struct symbol* s = (struct symbol*)malloc(sizeof(symbol));
			s->name = v->name;
			s->datatype = v->datatype;
			s->charval = 0;
			s->intval = 0;
			s->doubval = 0;
			s->size = 0;
			s->func = NULL;
			s->syms = NULL;
			insert(pp, s);
			return r1;
		}
		case 6:
		{
			struct arr * ar = (struct arr*)a;
			struct symbol* s = (struct symbol*)malloc((ar->size)*sizeof(symbol));
			for (int i = 0; i < ar->size; i++)
			{
				(s + i)->name = ar->name;
				(s + i)->datatype = ar->datatype;
				(s + i)->charval = 0;
				(s + i)->intval = 0;
				(s + i)->doubval = 0;
				(s + i)->size = ar->size;
				(s + i)->func = NULL;
				(s + i)->syms = NULL;
			}
			insert(pp, s);
			return r1;
		}
		case 7:
		{
			struct fndec *fn = (struct fndec*)a;
			struct symbol* s = lookup(pp, fn->name);
			/*if (s != NULL&&s->func != NULL)
			{
				yyerror(pp, "%s  defined repeatly", s->name);
				exit(0);
			}
			else  if (s==NULL)
			{
				s = (struct symbol*)malloc(sizeof(symbol));
				insert(pp, s);
			}
			s->name = fn->name;
			s->datatype = fn->nodetype;
			s->func = fn->tl;
			s->syms = fn->s;
			struct symlist* sl = fn->s;
			while (sl != NULL)
			{
				struct symbol* k = (struct symbol*)malloc(sizeof(symbol));
				k->name = sl->cur->name;
				k->datatype = sl->cur->datatype;
				k->charval = 0;
				k->intval = 0;
				k->doubval = 0;
				k->size = sl->cur->size;
				k->func = NULL;
				k->syms = NULL;
				insert(pp, k);
				sl = sl->next;
			}

			s->size = 0;
			s->charval = 0;
			s->intval = 0;
			s->doubval = 0;*/
			eval(pp,fn->tl);
			return r1;
		}
		case 8:
		{
			struct csdec* cs = (struct csdec*)a;
			if (lookup(pp, cs->vname) != NULL)
			{
				yyerror(pp,"%s defined repeatly\n", cs->vname);
				exit(0);
			}
			struct symbol* c = lookup(pp, cs->cname);
			if (c==NULL)
			{
				yyerror(pp, "%s undefinedly\n", cs->cname);
			}
			return r1;
		}
		case 9:
		{
			struct csdef* c = (struct csdef*)a;
			return r1;
		}
		case 10:
		{
			return r1;
		}
		case '=':
		{
			struct symasgn* asgn = (struct symasgn*)a;
			//struct symbol* s = lookup(pp, asgn->name);
			/*if (s == NULL)
			{
				yyerror(pp, "%s variable undefined", asgn->name);
				exit(0);
			}
			r1.type = s->datatype;*/
			struct un tmp = eval(pp, asgn->v);
			/*if (tmp.type != r1.type)
			{
				yyerror(pp, "%s type is wrong", asgn->v);
				exit(0);
			}
			if (s->size != 0 && asgn->index == NULL)
			{
				yyerror(pp, "%s cannot be dereference", asgn->name);
				exit(0);
			}
			int index = 0;
			if (s->size != 0)
			{
				struct un tmp = eval(pp, asgn->index);
				if (tmp.type != 1 || tmp.num < 0 || tmp.num >= s->size)
				{
					yyerror(pp, "%s is out of range", ((struct symref*)a)->name);
					exit(0);
				}
				index = tmp.num;
			}
			else
				index = 0;
			switch (r1.type){
			case 0:
				(s+index)->charval = tmp.ch; r1.ch = tmp.ch; break;
			case 1:
				(s + index)->intval = tmp.num; r1.num = tmp.num; break;
			case 2:
				(s + index)->doubval = tmp.doub; r1.doub = tmp.doub; break;
			default:
				yyerror(pp, "%s cannot be left", asgn->name);
				exit(0);
				break;
			}*/
			return r1;
		}
		case '1':
		{
			r1.type = 1;
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			switch (tmp1.type){
			case 0:
				r1.num = tmp1.ch > tmp2.ch ? 1 : 0; break;
			case 1:
				r1.num = tmp1.num > tmp2.num ? 1 : 0; break;
			case 2:
				r1.num = tmp1.doub > tmp2.doub ? 1 : 0; break;
			}
			return r1;
		}
		case '2':
		{
			r1.type = 1;
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			switch (tmp1.type){
			case 0:
				r1.num = tmp1.ch < tmp2.ch ? 1 : 0; break;
			case 1:
				r1.num = tmp1.num < tmp2.num ? 1 : 0; break;
			case 2:
				r1.num = tmp1.doub < tmp2.doub ? 1 : 0; break;
			}
			return r1;
		}
		case '3':
		{
			r1.type = 1;
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			switch (tmp1.type){
			case 0:
				r1.num = tmp1.ch != tmp2.ch ? 1 : 0; break;
			case 1:
				r1.num = tmp1.num != tmp2.num ? 1 : 0; break;
			case 2:
				r1.num = tmp1.doub != tmp2.doub ? 1 : 0; break;
			}
			return r1;
		}
		case '4':
		{
			r1.type = 1;
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			switch (tmp1.type){
			case 0:
				r1.num = tmp1.ch == tmp2.ch ? 1 : 0; break;
			case 1:
				r1.num = tmp1.num == tmp2.num ? 1 : 0; break;
			case 2:
				r1.num = tmp1.doub == tmp2.doub ? 1 : 0; break;
			}
			return r1;
		}
		case '5':
		{
			r1.type = 1;
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			switch (tmp1.type){
			case 0:
				r1.num = tmp1.ch >= tmp2.ch ? 1 : 0; break;
			case 1:
				r1.num = tmp1.num >= tmp2.num ? 1 : 0; break;
			case 2:
				r1.num = tmp1.doub >= tmp2.doub ? 1 : 0; break;
			}
			return r1;
		}
		case '6':
		{
			r1.type = 1;
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			switch (tmp1.type){
			case 0:
				r1.num = tmp1.ch <= tmp2.ch ? 1 : 0; break;
			case 1:
				r1.num = tmp1.num <= tmp2.num ? 1 : 0; break;
			case 2:
				r1.num = tmp1.doub <= tmp2.doub ? 1 : 0; break;
			}
			return r1;
		}
		case '+':
		{
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			r1.type = tmp1.type;
			switch (tmp1.type){
			case 0:
				r1.ch = tmp1.ch + tmp2.ch; break;
			case 1:
				r1.num = tmp1.num + tmp2.num; break;
			case 2:
				r1.doub = tmp1.doub + tmp2.doub; break;
			}
			return r1;
		}
		case '-':
		{
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			r1.type = tmp1.type;
			switch (tmp1.type){
			case 0:
				r1.ch = tmp1.ch - tmp2.ch; break;
			case 1:
				r1.num = tmp1.num - tmp2.num; break;
			case 2:
				r1.doub = tmp1.doub - tmp2.doub; break;
			}
			return r1;
		}
		case '*':
		{
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type || tmp1.type==0)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			r1.type = tmp1.type;
			switch (tmp1.type){
			case 1:
				r1.num = tmp1.num * tmp2.num; break;
			case 2:
				r1.doub = tmp1.doub * tmp2.doub; break;
			}
			return r1;
		}
		case '/':
		{
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type ||  tmp1.type ==0)
			{
				yyerror(pp, "type is not compatitle");
				exit(0);
			}
			r1.type = tmp1.type;
			switch (tmp1.type){
			case 1:
				r1.num = tmp1.num / tmp2.num; break;
			case 2:
				r1.doub = tmp1.doub / tmp2.doub; break;
			}
			return r1;
		}
		case '%':
		{
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type || tmp1.type!=1)
			{
				yyerror(pp, "compare is not compatible");
				exit(0);
			}
			r1.type = tmp1.type;
			r1.num = tmp1.num%tmp2.num;
			return r1;
		}
		case '&':
		{
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type || tmp1.type != 1)
			{
				yyerror(pp, "compare is not compatible");
				exit(0);
			}
			r1.type = tmp1.type;
			if (tmp1.num != 0 && tmp2.num != 0)
				r1.num = 1;
			else
				r1.num = 0;
			return r1;
		}
		case '|':
		{
			struct un tmp1 = eval(pp, a->l);
			struct un tmp2 = eval(pp, a->r);
			if (tmp1.type != tmp2.type || tmp1.type != 1)
			{
				yyerror(pp, "compare is not compatible");
				exit(0);
			}
			r1.type = tmp1.type;
			if (tmp1.num == 0 && tmp2.num == 0)
				r1.num = 0;
			else
				r1.num = 1;
			return r1;
		}
		case '~':
		{
			struct un tmp = eval(pp, a->l);
			if (tmp.type != 1)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			r1.type = tmp.type;
			if (tmp.num != 0)
				r1.num = 0;
			else
				r1.num = 1;
			return r1;
		}
		case 'M':
		{
			struct un tmp = eval(pp, a->l);
			if (tmp.type == 0)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			r1.type = tmp.type;
			if (r1.type == 1)
				r1.num = -(tmp.num);
			else
				r1.doub = -(tmp.doub);
			return r1;
		}
		case 'I':
		{
			struct un tmp = eval(pp, ((struct flow*)a)->cond);
			if (tmp.type != 1)
			{
				yyerror(pp, "compare is not compatitle");
				exit(0);
			}
			if (tmp.num != 0)
			{
				if (((struct flow*)a)->tl)
					r1 = eval(pp, ((struct flow*)a)->tl);
			}
			else
			{
				if (((struct flow*)a)->el)
					r1 = eval(pp, ((struct flow*)a)->el);
			}
			return r1;
		}
		case 'W':
		{
				struct un tmp = eval(pp, ((struct flow*)a)->cond);
				if (tmp.type != 1)
				{
					yyerror(pp, "compare is not compatitle");
					exit(0);
				}
				while (tmp.num != 0)
				{
					r1 = eval(pp, ((struct flow*)a)->tl);
					tmp = eval(pp, ((struct flow*)a)->cond);
				}
				return r1;
		}
		case 'O':
		{
			struct _for* f = (struct _for*)a;
			struct symbol* s = lookup(pp, f->index);
			if (s == NULL)
			{
				yyerror(pp, "%s variable undefined", s->name);
				exit(0);
			}
			if (s->datatype != 1)
			{
				yyerror(pp, "%s type is not compatitle", s->name);
			}
			s->intval = f->start;
			while (s->intval < f->end)
			{
				eval(pp, f->tl);
				s->intval += f->step;
			}
			return r1;
		}
		case 'E':
		{
			struct _foreach *fe = (struct _foreach*)a;
			struct symbol*	s1 = lookup(pp, fe->arr);
			struct symbol* s2 = lookup(pp, fe->index);
			if (s1->datatype != s2->datatype || s1->size<=0)
			{
				yyerror(pp, "%s is not compatible", fe->arr);
				exit(0);
			}
			int i = 0;
			switch (s1->datatype){
			case 0:
				while (i < s1->size)
				{
					s2->charval = (s1 + i)->charval;
					eval(pp, fe->tl);
					i++;
				}
				break;
			case 1:
				while (i < s1->size)
				{
					s2->intval = (s1 + i)->intval;
					eval(pp, fe->tl);
					i++;
				}
				break;
			case 2:
				while (i < s1->size)
				{
					s2->doubval = (s1 + i)->doubval;
					eval(pp, fe->tl);
					i++;
				}
				break;
			}
			return r1;
		}
		case 'L':eval(pp, a->l); r1 = eval(pp, a->r); return r1;
		default:
			printf("bad expression"); return r1;
		}
}
//----------------------------------
 un callbuiltin(struct pcdata* pp, struct fncall* f)
{
	enum bifs functype = f->functype;
	struct un r1 = eval(pp, f->tl);
	switch (functype){
	case B_sqrt:
	{
		switch (r1.type){
		case 0:
			yyerror(pp, "function cannot be used"); exit(0);
		case 1:
			r1.num = sqrt((double)r1.num); break;
		case 2:
			r1.doub = sqrt(r1.doub); break;
		}
		return r1;
	}
	case B_exp:
	{
		switch (r1.type){
		case 0:
			yyerror(pp, "function cannot be used"); exit(0);
		case 1:
			r1.num = exp((double)r1.num); break;
		case 2:
			r1.doub = exp(r1.doub); break;
		}
		return r1;
	}
	case B_log:
	{
		switch (r1.type){
		case 0:
			yyerror(pp, "function cannot be used"); exit(0);
		case 1:
			r1.num = log((double)r1.num); break;
		case 2:
			r1.doub = log(r1.doub); break;
		}
		return r1;
	}
	case B_print:
	{
		switch (r1.type){
		case 0:
			printf("%c\n", r1.ch); break;
		case 1:
			printf("%d\n", r1.num); break;
		case 2:
			printf("%f\n", r1.doub); break;
		}
		return r1;
	}
	default:
		yyerror(pp, "unknown built-in function %d", functype);
		return r1;
	}
}
static un calluser(struct pcdata* pp, struct ufncall* f)
{
	struct symbol* fn = lookup(pp, f->name);
	struct symlist* sl;
	struct ast* args = f->tl;
	struct un* oldval, *newval;
	struct un r1;
	int nargs;

	if (!fn->func)
	{
		yyerror(pp, "undefined function %s",fn->name);
		exit(0);
	}
	sl = fn->syms;
	for (nargs = 0; sl; sl = sl->next)
		nargs++;
	oldval = (struct un*)malloc(nargs*sizeof(struct un));
	newval = (struct un*)malloc(nargs*sizeof(struct un));
	if (!oldval || !newval)
	{
		yyerror(pp, "out of space %s", fn->name);
		exit(0);
	}
	for (int i = 0; i < nargs; i++)
	{
		if (!args)
		{
			yyerror(pp, "too few args in %s", fn->name);
			free(oldval); free(newval);
			exit(0);
		}
		if (args->nodetype == 'L')
		{
			newval[i] = eval(pp, args->l);
			args = args->r;
		}
		else
		{
			newval[i] = eval(pp, args);
			args = NULL;
		}
	}
	sl = fn->syms;
	for (int i = 0; i < nargs; i++)
	{
		/*struct symbol* s = lookup(pp, sl->name);
		oldval[i].type = s->datatype;
		oldval[i].ch = s->charval;
		oldval[i].num = s->intval;
		oldval[i].doub = s->doubval;

		s->datatype = newval[i].type;
		s->charval = newval[i].ch;
		s->intval = newval[i].num;
		s->doubval = newval[i].doub;
		sl = sl->next;*/
	}
	free(newval);
	r1 = eval(pp, fn->func);
	sl = fn->syms;
	for (int i = 0; i < nargs; i++)
	{
/*		struct symbol* s = lookup(pp, sl->name);
		s->datatype = oldval[i].type;
		s->charval = oldval[i].ch;
		s->intval = oldval[i].num;
		s->doubval = oldval[i].doub;
		sl = sl->next;*/
	}
	free(oldval);
	return r1;
}
void treefree(struct pcdata* pp, struct ast* a)
{
	
}
void yyerror(struct pcdata* pp, char* s, ...)
{
	va_list ap;
	va_start(ap, s);
	fprintf(stderr, "line %d:  error: ", yyget_lineno(pp->scaninfo));
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}
void show(int d)
{

}