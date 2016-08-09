#include "stdafx.h"
#include "IRGeneration.h"
#include <limits.h>

int
IRGeneration::getCodeAss(ast* node, int& index0, string& ir, char& ch, double& db){
	if (node == NULL)
		return INT_MAX;
	switch (node->nodetype){
	case 1:
	{
		string ir1;
		ir1 = getCall(node, index0);
		ir += ir1;
		return INT_MAX;
	}
	case 2:
	{
		struct charcons* cc = (struct charcons*)node;
		ch = cc->ch;
		return INT_MAX;
	}
	case 3:
	{
		struct intcons* ic = (struct intcons*)node;
		int ret = ic->num;
		return ret;
	}
	case 4:
	{

	}
	case 5:
	{
		struct var* v = (struct var*) node;
		string varname = v->name;
		int vartype = v->datatype;
		if (vartype == 0){//char
			index0 = index;
			ir += getAllocaChar(varname);
		}
		else if (vartype == 1){
			index0 = index;
			ir += getAllocaInt(varname);
		}
		else if (vartype == 2){
		}
		return	INT_MAX;
	}
	case 6:{
		struct arr* a = (struct arr*) node;
		string arrname = a->name;
		int arrtype = a->datatype;
		int arrsize = a->size;
		if (arrtype == 0){
			ir += getAllocaCharArray(arrname, arrsize);
		}
		if (arrtype == 1){
			ir += getAllocaIntArray(arrname, arrsize);
		}
		if (arrtype == 2){

		}
		return INT_MAX;
	}
	case 7:
	{
		string ir1;
		ir1 = getFunction(node);
		ir += ir1;
		return INT_MAX;
	}
	case '+':
	{
		int r1 = INT_MAX;
		int r2 = INT_MAX;
		char c1;
		char c2;
		double d1;
		double d2;
		int curindex1;
		int curindex2;
		string ir1;
		r1 = getCodeAss(node->l, index0, ir, c1, d1);
		curindex1 = index0;
		r2 = getCodeAss(node->r, index0, ir, c2, d2);
		curindex2 = index0;
		if (r1 != INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = add nsw i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = add nsw i32 %" + getInt(curindex1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 != INT_MAX  && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = add nsw i32 " + getInt(r1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = add nsw i32 %" + getInt(curindex1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		return INT_MAX;
	}
	case '-':
	{
		int r1 = INT_MAX;
		int r2 = INT_MAX;
		char c1;
		char c2;
		double d1;
		double d2;
		int curindex1;
		int curindex2;
		string ir1;
		r1 = getCodeAss(node->l, index0, ir, c1, d1);
		curindex1 = index0;
		r2 = getCodeAss(node->r, index0, ir, c2, d2);
		curindex2 = index0;
		if (r1 != INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = sub nsw i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = sub nsw i32 %" + getInt(curindex1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 != INT_MAX  && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = sub nsw i32 " + getInt(r1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = sub nsw i32 %" + getInt(curindex1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		return INT_MAX;
	}
	case '*':
	{
		int r1 = INT_MAX;
		int r2 = INT_MAX;
		char c1;
		char c2;
		double d1;
		double d2;
		int curindex1;
		int curindex2;
		string ir1;
		r1 = getCodeAss(node->l, index0, ir, c1, d1);
		curindex1 = index0;
		r2 = getCodeAss(node->r, index0, ir, c2, d2);
		curindex2 = index0;
		if (r1 != INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = mul nsw i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = mul nsw i32 %" + getInt(curindex1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 != INT_MAX  && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = mul nsw i32 " + getInt(r1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = mul nsw i32 %" + getInt(curindex1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		return INT_MAX;
	}
	case '/':
	{
		int r1 = INT_MAX;
		int r2 = INT_MAX;
		char c1;
		char c2;
		double d1;
		double d2;
		int curindex1;
		int curindex2;
		string ir1;
		r1 = getCodeAss(node->l, index0, ir, c1, d1);
		curindex1 = index0;
		r2 = getCodeAss(node->r, index0, ir, c2, d2);
		curindex2 = index0;
		if (r1 != INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = sdiv i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = sdiv i32 %" + getInt(curindex1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 != INT_MAX  && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = sdiv i32 " + getInt(r1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = sdiv i32 %" + getInt(curindex1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		return INT_MAX;
	}
	case '%':
	{
		int r1 = INT_MAX;
		int r2 = INT_MAX;
		char c1;
		char c2;
		double d1;
		double d2;
		int curindex1;
		int curindex2;
		string ir1;
		r1 = getCodeAss(node->l, index0, ir, c1, d1);
		curindex1 = index0;
		r2 = getCodeAss(node->r, index0, ir, c2, d2);
		curindex2 = index0;
		if (r1 != INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = srem i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = srem i32 %" + getInt(curindex1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 != INT_MAX  && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = srem i32 " + getInt(r1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = srem i32 %" + getInt(curindex1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		return INT_MAX;
	}
	case '=':
	{
		struct symasgn* sa = (struct symasgn*)node;
		string varname = sa->name;
		ast* indexnode = sa->index;
		if (indexnode == NULL){
			if (infunc){
				int typecode = 1;
				para* p = sta->checkFuncPara(varname, funcindex);
				if (p->name != ""){
					varname += ".var";
					typecode = 0;
				}
				else {
					p = sta->checkFuncVar(varname, funcindex);
					if (p->name != ""){
						typecode = 0;
					}
				}
				if (typecode == 0){
					if (p->type == "integer"){
						int r = INT_MAX;
						char c;
						double d;
						r = getCodeAss(sa->v, index0, ir, c, d);
						if (r != INT_MAX){
							string ir1 = "  store i32 " + getInt(r) + ", i32* %" + varname + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else{
							string ir1 = "  store i32 %" + getInt(index0) + ", i32* %" + varname + "\n";
							ir += ir1;
							return INT_MAX;
						}
					}
					else if (p->type == "char"){
						int r = INT_MAX;
						char c = 0;
						double d;
						r = getCodeAss(sa->v, index0, ir, c, d);
						if (c == 0){
							string ir1 = "  store i8 %" + getInt(index0) + ", i8* %" + varname + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else{
							string ir1 = "  store i8 " + getInt((int)c) + ", i8* %" + varname + "\n";
							ir += ir1;
							ch = 0;
							return INT_MAX;
						}
					}
				}
				else {
					serr* err = new serr();
					err->errortype = VARUNDECLARE;
					err->errorpos = sa->lineno;
					err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
					se->addErrs(err);
					return INT_MAX;
				}
			}
			else{
				para* p = sta->checkVariable(varname);
				if (p->name != ""){
					if (p->type == "integer"){
						int r = INT_MAX;
						char c;
						double d;
						r = getCodeAss(sa->v, index0, ir, c, d);
						if (r != INT_MAX){
							string ir1 = "  store i32 " + getInt(r) + ", i32* %" + varname + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else{
							string ir1 = "  store i32 %" + getInt(index0) + ", i32* %" + varname + "\n";
							ir += ir1;
							return INT_MAX;
						}
					}
					else if (p->type == "char"){
						int r = INT_MAX;
						char c = 0;
						double d;
						r = getCodeAss(sa->v, index0, ir, c, d);
						if (c == 0){
							string ir1 = "  store i8 %" + getInt(index0) + ", i8* %" + varname + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else{
							string ir1 = "  store i8 " + getInt((int)ch) + ", i8* %" + varname + "\n";
							ir += ir1;
							ch = 0;
							return INT_MAX;
						}
					}
				}
				else{
					serr* err = new serr();
					err->errortype = VARUNDECLARE;
					err->errorpos = sa->lineno;
					err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
					se->addErrs(err);
					return INT_MAX;
				}
			}
		}
		else {
			if (infunc){
				int typecode = 1;
				para* p = sta->checkFuncPara(varname, funcindex);
				if (p->name != ""){
					varname += ".var";
					typecode = 0;
				}
				else {
					p = sta->checkFuncType(varname, funcindex);
					if (p->name != ""){
						typecode = -1;
					}
				}
				if (typecode == 0){
					if (p->type == "integer"){
						string ir1;
						int r = INT_MAX;
						char c1;
						double d1;
						r = getCodeAss(indexnode, index0, ir1, c1, d1);
						int curindex = index0;
						int rr = INT_MAX;
						char c2;
						double d2;
						rr = getCodeAss(sa->v, index0, ir1, c2, d2);
						int curindexx = index0;
						if (r != INT_MAX && rr != INT_MAX){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r != INT_MAX && rr == INT_MAX){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && rr != INT_MAX){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
							index0 = index;
							index++;

							ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && rr == INT_MAX){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
					}
					else if (p->type == "char"){
						string ir1;
						int r = INT_MAX;
						char c1 = 0;
						double d1;
						r = getCodeAss(indexnode, index0, ir1, c1, d1);
						int curindex = index0;
						int rr = INT_MAX;
						char c2 = 0;
						double d2;
						rr = getCodeAss(sa->v, index0, ir1, c2, d2);
						int curindexx = index0;
						if (r != INT_MAX && c2 != 0){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r != INT_MAX && c2 == 0){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && c2 != 0){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 " + getInt((int)ch) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && c2 == 0){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
					}
				}
				else if (typecode == -1){
					if (p->type == "integer"){
						string ir1;
						int r = INT_MAX;
						char c1;
						double d1;
						r = getCodeAss(indexnode, index0, ir1, c1, d1);
						int curindex = index0;
						int rr = INT_MAX;
						char c2;
						double d2;
						rr = getCodeAss(sa->v, index0, ir1, c2, d2);
						int curindexx = index0;
						if (r != INT_MAX && rr != INT_MAX){
							int curindex = index;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r != INT_MAX && rr == INT_MAX){
							int curindex = index;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && rr != INT_MAX){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && rr == INT_MAX){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
					}
					else if (p->type == "char"){
						string ir1;
						int r = INT_MAX;
						char c1 = 0;
						double d1;
						r = getCodeAss(indexnode, index0, ir1, c1, d1);
						int curindex = index0;
						int rr = INT_MAX;
						char c2 = 0;
						double d2;
						rr = getCodeAss(sa->v, index0, ir1, c2, d2);
						int curindexx = index0;
						if (r != INT_MAX && c2 != 0){
							int curindex = index;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r != INT_MAX && c2 == 0){
							int curindex = index;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && c2 != 0){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && c2 == 0){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
					}
				}
				else {
					serr* err = new serr();
					err->errortype = VARUNDECLARE;
					err->errorpos = sa->lineno;
					err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
					se->addErrs(err);
					return INT_MAX;
				}
			}
			else{
				para* p = sta->checkType(varname);
				if (p->name != ""){
					if (p->type == "integer"){
						string ir1;
						int r = INT_MAX;
						char c1;
						double d1;
						r = getCodeAss(indexnode, index0, ir1, c1, d1);
						int curindex = index0;
						int rr = INT_MAX;
						char c2;
						double d2;
						rr = getCodeAss(sa->v, index0, ir1, c2, d2);
						int curindexx = index0;
						if (r != INT_MAX && rr != INT_MAX){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r != INT_MAX && rr == INT_MAX){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + ", i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && rr != INT_MAX){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + ", i64 %" + getInt(curindex0) + "\n";
							index0 = index;
							index++;

							ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && rr == INT_MAX){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + ", i64 %" + getInt(curindex0) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
					}
					else if (p->type == "char"){
						string ir1;
						int r = INT_MAX;
						char c1 = 0;
						double d1;
						r = getCodeAss(indexnode, index0, ir1, c1, d1);
						int curindex = index0;
						int rr = INT_MAX;
						char c2 = 0;
						double d2;
						rr = getCodeAss(sa->v, index0, ir1, c2, d2);
						int curindexx = index0;
						if (r != INT_MAX && c2 != 0){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r != INT_MAX && c2 == 0){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && c2 != 0){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 " + getInt((int)ch) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
						else if (r == INT_MAX && c2 == 0){
							int curindex0 = index0;
							int curindex1 = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
							index0 = index;
							index++;
							ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
							ir += ir1;
							return INT_MAX;
						}
					}
				}
				else{
					serr* err = new serr();
					err->errortype = VARUNDECLARE;
					err->errorpos = sa->lineno;
					err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
					se->addErrs(err);
					return INT_MAX;
				}
			}
		}
	}
	case 'N':
	{
		struct symref* sr = (struct symref*)node;
		string varname = sr->name;
		ast* indexnode = sr->index;
		if (indexnode == NULL){
			if (infunc){
				int typecode = 1;//1 for error
				para* p = sta->checkFuncPara(varname, funcindex);
				if (p->name != ""){
					varname += ".var";
					typecode = 0;
					if (p->size != -1){
						arrayindex++;
						typecode = -1;
					}
				}
				else {
					p = sta->checkFuncVar(varname, funcindex);
					if (p->name != ""){
						typecode = 0;
					}
					else {
						p = sta->checkFuncType(varname, funcindex);
						if (p->name != ""){
							typecode = -2;
							arrayindex++;
						}
					}
				}

				if (typecode != 1){
					string ir1;
					if (p->type == "integer"){
						index0 = index;
						if (typecode == 0)
							ir1 = getLoadInt(varname);
						else if (typecode == -1)
							ir1 = getLoadIntPointer(varname);
						else if (typecode == -2){
							ir1 = "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
							index++;
						}
						ir += ir1;
						return INT_MAX;
					}
					else if (p->type == "char"){
						index0 = index;
						if (typecode == 0)
							ir1 = getLoadChar(varname);
						else if (typecode == -1)
							ir1 = getLoadCharPointer(varname);
						else if (typecode == -2){
							ir1 = "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
							index++;
						}
						ir += ir1;
						return INT_MAX;
					}
				}
				else{
					serr* err = new serr();
					err->errortype = VARUNDECLARE;
					err->errorpos = sr->lineno;
					err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
					se->addErrs(err);
					return INT_MAX;
				}
			}
			else{
				para* p = sta->checkVariable(varname);
				if (p->name != ""){
					string ir1;
					if (p->type == "integer"){
						index0 = index;
						ir1 = getLoadInt(varname);
						ir += ir1;
						return INT_MAX;
					}
					else if (p->type == "char"){
						index0 = index;
						ir1 = getLoadChar(varname);
						ir += ir1;
						return INT_MAX;
					}
				}
				else{
					p = sta->checkType(varname);
					if (p->name != ""){
						string ir1;
						if (p->type == "integer"){
							index0 = index;
							ir1 = getLoadIntPointer(varname);
							ir += ir1;
							return INT_MAX;
						}
						else if (p->type == "char"){
							index0 = index;
							ir1 = getLoadCharPointer(varname);
							ir += ir1;
							return INT_MAX;
						}
					}
					else{
						serr* err = new serr();
						err->errortype = VARUNDECLARE;
						err->errorpos = sr->lineno;
						err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
						se->addErrs(err);
						return INT_MAX;
					}
				}
			}

		}
		else{//array
			if (infunc){
				int typecode = 1;
				para* p = sta->checkFuncPara(varname, funcindex);
				if (p->name != ""){
					varname += ".var";
					typecode = -1;
				}
				else {
					p = sta->checkFuncType(varname, funcindex);
					if (p->name != ""){
						typecode = 0;
					}
				}
				if (typecode != 1){
					string ir1;
					int r = INT_MAX;
					char c;
					double d;
					r = getCodeAss(indexnode, index0, ir1, c, d);
					if (r != INT_MAX){
						if (p->type == "integer"){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
							index++;
							ir1 += getLoadInt(getInt(index - 1));
							index0 = index - 1;
							ir += ir1;
							return INT_MAX;
						}
					}
					else{
						int curindex0 = index0;
						int curindex1 = index;
						if (p->type == "integer"){
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
							index++;
							ir1 += getLoadInt(getInt(index - 1));
							index0 = index - 1;
							ir += ir1;
							return INT_MAX;
						}
						else if (p->type == "char"){
							ir1 += getLoadCharPointer(varname);
							//[TODO]
							return INT_MAX;
						}
					}
				}
				else{
					serr* err = new serr();
					err->errortype = VARUNDECLARE;
					err->errorpos = sr->lineno;
					err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
					se->addErrs(err);
					return INT_MAX;
				}
			}
			else{
				para* p = sta->checkType(varname);
				if (p->name != ""){
					string ir1;
					int r = INT_MAX;
					char c;
					double d;
					r = getCodeAss(indexnode, index0, ir1, c, d);
					if (r != INT_MAX){
						if (p->type == "integer"){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
							index++;
							ir1 += getLoadInt(getInt(index - 1));
							index0 = index - 1;
							ir += ir1;
							return INT_MAX;
						}
					}
					else{
						int curindex0 = index0;
						int curindex1 = index;
						if (p->type == "integer"){
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
							index++;
							ir1 += getLoadInt(getInt(index - 1));
							index0 = index - 1;
							ir += ir1;
							return INT_MAX;
						}
						else if (p->type == "char"){
							ir1 += getLoadCharPointer(varname);
							//[TODO]
							return INT_MAX;
						}
					}
				}
				else{
					serr* err = new serr();
					err->errortype = VARUNDECLARE;
					err->errorpos = sr->lineno;
					err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
					se->addErrs(err);
					return INT_MAX;
				}
			}
		}
	}
	case 'I':
	{
		string ir1;
		ir1 = getIf(node);
		ir += ir1;
		return INT_MAX;
	}
	case 'W':
	{
		string ir1;
		ir1 = getWhile(node);
		ir += ir1;
		return INT_MAX;
	}
	case 'R':
	{
		if (infunc){
			ast* retnode = node->l;
			int r;
			if (retnode != NULL){
				r = getCodeAss(retnode, index0, ir, ch, db);
				if (r != INT_MAX){
					index0 = r;
					retcons = 1;
				}
			}
			else
				r = INT_MAX;
			return r;
		}
		else{
			//error
			return INT_MAX;
		}
	}
	case 'L':
	{
		if (node->l != NULL)
			getCodeAss(node->l, index0, ir, ch, db);
		if (node->r != NULL)
			getCodeAss(node->r, index0, ir, ch, db);
	}
	}
	return INT_MAX;
}

string
IRGeneration::getInt(int n){
	stringstream ss;
	ss << n;
	string ret = ss.str();
	return ret;
}

string
IRGeneration::getFile(string filename){
	ifstream ifs(filename);
	ostringstream buf;
	char ch;
	while (buf && ifs.get(ch))
		buf.put(ch);
	string ret = buf.str();
	return ret;
}

string
IRGeneration::getAllocaInt(string name){
	string ir;
	ir = "  %" + name + " = alloca i32, align 4\n";
	return ir;
}

string
IRGeneration::getAllocaIntPointer(string name){
	string ir;
	ir = "  %" + name + " = alloca i32*, align 8\n";
	return ir;
}

string
IRGeneration::getAllocaIntArray(string name, int size){
	string ir;
	ir = "  %" + name + " = alloca [" + getInt(size) + " x i32], align 4\n";
	return ir;
}

string
IRGeneration::getLoadInt(string name){
	string ir;
	ir = "  %" + getInt(index) + " = load i32* %" + name + "\n";
	index++;
	return ir;
}

string
IRGeneration::getLoadIntPointer(string name){
	string ir;
	ir = "  %" + getInt(index) + " = load i32** %" + name + "\n";
	index++;
	return ir;
}

string
IRGeneration::getStoreInt(string name, string value){
	string ir;
	ir = "  store i32 %" + value + ", i32* %" + name + "\n";
	return ir;
}

string
IRGeneration::getStoreIntPointer(string name, string value){
	string ir;
	ir = "  store i32* %" + value + ", i32** %" + name + "\n";
	return ir;
}

string
IRGeneration::getAllocaChar(string name){
	string ir;
	ir = "  %" + name + " = alloca i8, align 1\n";
	return ir;
}

string
IRGeneration::getAllocaCharPointer(string name){
	string ir;
	ir = "  %" + name + " = alloca i8*, align 2\n";
	return ir;
}

string
IRGeneration::getAllocaCharArray(string name, int size){
	string ir;
	ir = "  %" + name + " = alloca [" + getInt(size) + " x i8], align 1\n";
	return ir;
}

string
IRGeneration::getLoadChar(string name){
	string ir;
	ir = "  %" + getInt(index) + " = load i8* %" + name + "\n";
	index++;
	return ir;
}

string
IRGeneration::getLoadCharPointer(string name){
	string ir;
	ir = "  %" + getInt(index) + " = load i8** %" + name + "\n";
	index++;
	return ir;
}

string
IRGeneration::getStoreChar(string name, string value){
	string ir;
	ir = "  store i8 %" + value + ", i8* %" + name + "\n";
	return ir;
}

string
IRGeneration::getStoreCharPointer(string name, string value){
	string ir;
	ir = "  store i8* %" + value + ", i8** %" + name + "\n";
	return ir;
}

string
IRGeneration::getConstant(){
	string ir;
	ir = "@_printa = internal constant [5 x i8] c\"%d  \\00\", align 1\n";
	ir += "@_printc = internal constant [2 x i8] c\"%c\", align 1\n";
	ir += "@_printn = internal constant [2 x i8] c\"\\0A\\00\", align 1\n";
	ir += "declare i32 @printf(i8*, ...)\n";

	ir += "\n";
	return ir;
}

string
IRGeneration::getLinkFunc(){
	string ir;
	ir = "";
	int size = linkfiles.size();
	if (size != 0){
		for (int i = 0; i < size; i++){
			ir += getFile(linkfiles[i]);
			ir += "\n";
		}
	}
	ir += "\n";
	return ir;
}

string
IRGeneration::getWhile(ast* node){
	string ir;
	string ir1;
	string ir2;
	int curindex = index;
	ir = "  br label %" + getInt(index) + "\n\n";
	ir += "; <label>:" + getInt(index) + "\n";
	index++;
	int curwhileindex = whileindex;
	whileindex++;
	struct flow* fl = (struct flow*)node;
	ast* cmpnode = fl->cond;
	ast* maincode = fl->tl;
	ir1 = getCmp(cmpnode, curwhileindex);
	int pos;
	ir2 = "";
	char c;
	double d;
	int r = getCodeAss(maincode, pos, ir2, c, d);
	ir += ir1;
	ir += ir2;
	ir += "  br label %" + getInt(curindex) + "\n\n";
	ir += "whileend" + getInt(curwhileindex) + ":\n";
	return ir;
}

string
IRGeneration::getCmp(ast* node, int curwhileindex){
	string ir;
	string symbol;
	switch (node->nodetype){
	case '1':
		symbol = "sgt";
		break;
	case '2':
		symbol = "slt";
		break;
	case '3':
		symbol = "ne";
		break;
	case '4':
		symbol = "eq";
		break;
	case '5':
		symbol = "sge";
		break;
	case '6':
		symbol = "sle";
		break;
	default:
		symbol = "";
		break;
	}
	int pos0, pos1;
	char c1;
	char c2;
	double d1;
	double d2;
	string ir1 = "";
	int r1 = getCodeAss(node->l, pos0, ir1, c1, d1);
	string ir2 = "";
	int r2 = getCodeAss(node->r, pos1, ir2, c2, d2);
	ir = "";
	ir += ir1;
	ir += ir2;
	if (r1 == INT_MAX && r2 == INT_MAX)
		ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", %" + getInt(pos1) + "\n";
	else if (r1 != INT_MAX && r2 == INT_MAX)
		ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", %" + getInt(pos1) + "\n";
	else if (r1 == INT_MAX && r2 != INT_MAX)
		ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", " + getInt(r2) + "\n";
	else if (r1 != INT_MAX && r2 != INT_MAX)
		ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
	ir += "  br i1 %" + getInt(index) + ", label %" + getInt(index + 1) + ", label %whileend" + getInt(curwhileindex) + "\n\n";
	ir += "; <label>:" + getInt(index + 1) + "\n";
	index += 2;
	return ir;
}

string
IRGeneration::getIf(ast* node){
	string ir;
	string ir1;
	string ir2;
	string ir3;
	struct flow* fl = (struct flow*)node;
	int curifindex = ifindex;
	int curelseindex = elseindex;
	ast* cmpnode = fl->cond;
	ast* ifnode = fl->tl;
	ast* elsenode = fl->el;
	bool elseexist;
	if (elsenode)
		elseexist = 1;
	else
		elseexist = 0;
	ifindex++;
	if (elseexist) elseindex++;
	ir1 = getIfCmp(cmpnode, elseexist, curifindex, curelseindex);
	int pos0;
	int pos1;
	ir2 = "";
	char c1;
	double d1;
	int r = getCodeAss(ifnode, pos0, ir2, c1, d1);
	if (elseexist){
		ir3 = "";
		ir3 += "else" + getInt(curelseindex) + ":\n";
		string ir4 = "";
		char c2;
		double d2;
		int rr = getCodeAss(elsenode, pos1, ir4, c2, d2);
		ir3 += ir4;
		ir3 += "  br label %ifend" + getInt(curifindex) + "\n\n";
	}
	else
		ir3 = "";
	ir = "";
	ir += ir1;
	ir += ir2;
	ir += "  br label %ifend" + getInt(curifindex) + "\n\n";
	ir += ir3;
	ir += "ifend" + getInt(curifindex) + ":\n";
	return ir;
}

string
IRGeneration::getIfCmp(ast* node, bool elseexist, int curifindex, int curelseindex){
	string ir;
	string symbol;
	switch (node->nodetype){
	case '1':
		symbol = "sgt";
		break;
	case '2':
		symbol = "slt";
		break;
	case '3':
		symbol = "ne";
		break;
	case '4':
		symbol = "eq";
		break;
	case '5':
		symbol = "sge";
		break;
	case '6':
		symbol = "sle";
		break;
	default:
		symbol = "";
		break;
	}
	int pos0, pos1;
	string ir1 = "";
	string ir2 = "";
	int r1, r2;
	char c1;
	char c2;
	double d1;
	double d2;
	r1 = getCodeAss(node->l, pos0, ir1, c1, d1);
	r2 = getCodeAss(node->r, pos1, ir2, c2, d2);
	if (!elseexist){
		ir = "";
		ir += ir1;
		ir += ir2; if (r1 == INT_MAX && r2 == INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", %" + getInt(pos1) + "\n";
		else if (r1 != INT_MAX && r2 == INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", %" + getInt(pos1) + "\n";
		else if (r1 == INT_MAX && r2 != INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", " + getInt(r2) + "\n";
		else if (r1 != INT_MAX && r2 != INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
		ir += "  br i1 %" + getInt(index) + ", label %" + getInt(index + 1) + ", label %ifend" + getInt(curifindex) + "\n\n";
		ir += "; <label>:" + getInt(index + 1) + "\n";
		index += 2;
	}
	else{
		ir = "";
		ir += ir1;
		ir += ir2; if (r1 == INT_MAX && r2 == INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", %" + getInt(pos1) + "\n";
		else if (r1 != INT_MAX && r2 == INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", %" + getInt(pos1) + "\n";
		else if (r1 == INT_MAX && r2 != INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", " + getInt(r2) + "\n";
		else if (r1 != INT_MAX && r2 != INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
		ir += "  br i1 %" + getInt(index) + ", label %" + getInt(index + 1) + ", label %else" + getInt(curelseindex) + "\n\n";
		ir += "; <label>:" + getInt(index + 1) + "\n";
		index += 2;
	}
	return ir;
}

string
IRGeneration::getFunction(ast* node){
	string ir;
	string ir1;
	string ir2;
	infunc = true;
	struct fndec* fn = (struct fndec*)node;
	struct symlist* paralist = fn->s;
	string name = fn->name;
	func* f = sta->checkFunc(name);
	if (f->name != ""){
		if (f->returntype == 0){
			ir1 = "define void @" + name + "(";
		}
		else if (f->returntype == 1){
			ir1 = "define i32 @" + name + "(";
		}
		else if (f->returntype == 2){
			ir1 = "define i8 @" + name + "(";
		}
		else if (f->returntype == 3){
			//[TODO]
		}
		ir2 = "";
		while (paralist->cur != NULL){
			string paraname = paralist->cur->name;
			int paradatatype = paralist->cur->datatype;
			//string paratname = paralist->cur->tname;//for class
			int parasize = paralist->cur->size;
			if (parasize == -1){//not array
				if (paradatatype == 0){//char
					ir1 += "i8 %" + paraname;
					string modifiedname = paraname + ".var";
					ir2 += getAllocaChar(modifiedname);
					ir2 += getStoreChar(modifiedname, paraname);
				}
				if (paradatatype == 1){//int
					ir1 += "i32 %" + paraname;
					string modifiedname = paraname + ".var";
					ir2 += getAllocaInt(modifiedname);
					ir2 += getStoreInt(modifiedname, paraname);
				}
				if (paradatatype == 2){//double

				}
			}
			else if (parasize != -1){//array
				if (paradatatype == 0){//char
					ir1 += "i8* %" + paraname;
					string modifiedname = paraname + ".var";
					ir2 += getAllocaCharPointer(modifiedname);
					ir2 += getStoreCharPointer(modifiedname, paraname);
				}
				if (paradatatype == 1){//int
					ir1 += "i32* %" + paraname;
					string modifiedname = paraname + ".var";
					ir2 += getAllocaIntPointer(modifiedname);
					ir2 += getStoreIntPointer(modifiedname, paraname);
				}
				if (paradatatype == 2){//double

				}
			}
			paralist = paralist->next;
			if (paralist != NULL)
				ir1 += ", ";
			else
				break;
		}
		ir1 += ") {\n";
		string ir3;
		int pos;
		ast* funcnode = fn->tl;
		ir3 = "";
		char c;
		double d;
		int r = getCodeAss(funcnode, pos, ir3, c, d);
		string ir4;
		if (f->returntype == 0){
			ir4 = "  ret void\n";
		}
		else if (f->returntype == 1){
			if (retcons == 0)
				ir4 += "  ret i32 %" + getInt(pos) + "\n";
			else
				ir4 += "  ret i32 " + getInt(pos) + "\n";
			retcons = 1;
		}
		else if (f->returntype == 2){
			ir4 += "  ret i8 %" + getInt(pos) + "\n";
		}
		ir4 += "}\n\n";
		ir = ir1 + ir2 + ir3 + ir4;
		infunc = false;
		index = 1;
		funcindex++;
		return ir;
	}
	else{

		return ir;
	}
}

string
IRGeneration::getCall(ast* node, int& pos){
	string ir;
	string ir1;
	string ir2;
	string ir3;
	struct ufncall* ufn = (struct ufncall*)node;
	int line = node->lineno;
	string funcname = ufn->name;
	func* f = new func();
	f = sta->checkFunc(funcname);
	if (f->name != ""){
		int findex = f->index;
		ast* paranode = ufn->tl;
		ir3 = "";
		ir2 = "";
		getCallAss(paranode, ir3, ir2, findex);

		string rettype;
		if (f->returntype == 0)
			rettype = "void";
		else if (f->returntype == 1)
			rettype = "i32";
		else if (f->returntype == 2)
			rettype = "i8";
		if (f->returntype != 0){
			pos = index;
			ir1 = "  %" + getInt(index) + " = ";
			index++;
		}
		else {
			ir1 = "  ";
		}
		ir1 += "call " + rettype + " @" + funcname + "(";
		ir1 += ir3;

		if (paraindex != f->paranum){
			serr* err = new serr();
			err->errortype = PARANUMERR;
			err->errorpos = line;
			err->errorinfo = "Call parameter number mismatch with Function parameter number\n";
			se->addErrs(err);
		}
		int length = ir1.length();
		if (paranode != NULL)
			ir1 = ir1.substr(0, length - 2);
		ir1 += ")\n\n";

		ir = ir2 + ir1;
	}
	else{
		serr* err = new serr();
		err->errortype = FUNCUNDECLARE;
		err->errorpos = node->lineno;
		err->errorinfo = "Function '" + funcname + "' called without declaration.\n";
		se->addErrs(err);
	}
	paraindex = 0;
	return ir;
}

void
IRGeneration::getCallAss(ast* node, string& ir1, string& ir2, int findex){
	if (node == NULL)
		return;
	if (node->nodetype == 'L'){
		if (node->l != NULL)
			getCallAss(node->l, ir1, ir2, findex);
		if (node->r != NULL)
			getCallAss(node->r, ir1, ir2, findex);
	}
	else{
		int pos;
		int curarrayindex = arrayindex;
		char c = 0;
		double d;
		int line = node->lineno;
		int r = getCodeAss(node, pos, ir2, c, d);
		para* p = new para();
		p = sta->getFuncPara(findex, paraindex);
		if (r == INT_MAX){
			if (curarrayindex == arrayindex){
				if (p->type == "integer")
					ir1 += "i32 %" + getInt(pos) + ", ";
				else if (p->type == "char")
					ir1 += "i8 %" + getInt(pos) + ", ";
				else{
					serr* err = new serr();
					err->errortype = PARAMISMATCH;
					err->errorpos = line;
					err->errorinfo = "Call parameter mismatch with Function parameter\n";
					se->addErrs(err);
				}
			}
			else {
				if (p->type == "integer" && p->size != -1){
					ir1 += "i32* %" + getInt(pos) + ", ";
					arrayindex++;
				}
				else if (p->type == "char" && p->size != -1){
					ir1 += "i8* %" + getInt(pos) + ", ";
					arrayindex++;
				}
				else{
					serr* err = new serr();
					err->errortype = PARAMISMATCH;
					err->errorpos = line;
					err->errorinfo = "Call parameter mismatch with Function parameter\n";
					se->addErrs(err);
				}
			}
		}
		else {
			if (p->type == "integer")
				ir1 += "i32 " + getInt(r) + ", ";
			else if (p->type == "char"){
				ir1 += "i8 " + getInt((int)c) + ", ";
			}
			else{
				serr* err = new serr();
				err->errortype = PARAMISMATCH;
				err->errorpos = line;
				err->errorinfo = "Call parameter mismatch with Function parameter\n";
				se->addErrs(err);
			}
		}
		paraindex++;
	}
}

string
IRGeneration::Generate(){
	string ir;
	string ir1 = "";
	ir += getConstant();

	int pos;
	char c;
	double d;
	int r = getCodeAss(root, pos, ir1, c, d);

	if (se->checkErrs())
		ir = se->showErrs();
	else{
		ir += ir1;
		ir += "\n";
		ir += ";link\n";
		ir += getLinkFunc();
	}
	return ir;
}

IRGeneration::IRGeneration(ast* rt){
	index = 1;
	infunc = 0;
	arrayindex = 0;
	ifindex = 0;
	elseindex = 0;
	whileindex = 0;
	cmpindex = 0;
	funcindex = 0;
	paraindex = 0;
	retcons = 0;
	root = rt;
	linkfiles.push_back("linkfile.txt");
	se = new SemanticError();
	sta = new SymbolTableAnalyse(se);
	sta->Analyse(root);
}

void
IRGeneration::AddLinkFile(string filename){
	if (filename != "")
		linkfiles.push_back(filename);
	return;
}
