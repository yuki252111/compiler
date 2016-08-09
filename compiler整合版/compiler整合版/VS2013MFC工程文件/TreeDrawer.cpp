#include "stdafx.h"
/*
* Filename: TreeDrawer.cpp
* FileDes : In this file you can see the definitions or realizations of TreeDrawer's member functions.
*/
#include "TreeDrawer.h"
#include <string>
using std::string;

#define _FORSESASCHILDTREE

// helper functions
vector< vector<ast*> > treeInLevel;
void Levelise(ast* node, int k);
void DrawLevelisedTreeNode();
void DrawLevelisedTreeVector();
const double LEVEL_GAP = 0.08;
string GetNodeContent(ast* node);

TreeDrawer::TreeDrawer()
{
	this->root = NULL;
}

// delete a tree totally
void TreeDrawer::deleteTreeNode(ast* node)
{
	if (node == NULL)
		return;
	if (node->l)
		deleteTreeNode(node->l);
	if (node->r)
		deleteTreeNode(node->r);

	delete node;
	return;
}

// copy a tree totally
ast* TreeDrawer::copyTreeNode(ast* node)
{
	if (node == NULL)
		return NULL;

	// copy the content of the current node
	ast* ret = new ast();
	ret->nodetype = node->nodetype;

	// copy its left child
	if (node->l)
	{
		ast* lret = copyTreeNode(node->l);
		ret->l = lret;
	}
	else
	{
		ret->l = NULL;
	}

	// copy its right child
	if (node->r)
	{
		ast* rret = copyTreeNode(node->r);
		ret->r = rret;
	}
	else
	{
		ret->r = NULL;
	}

	// return the copy
	return ret;
}

void TreeDrawer::printTextTreeNodeHelper(string& sst, ast* node)
{
	if (node == NULL || (((int)node) >> 16 & 0xffff) == 0xABAB)
		return;

	if (((node->nodetype) & (0xff)) <= 7)
		sst += (char)(node->nodetype + '0');
	else
	{
		char str[256];
		sprintf(str, "%c", node->nodetype);
		sst += "\'" + string(str) + "\'";
	}
	sst += "(";

	//cout << endl << hex << "left:0x" << node->l << ";right:0x" << node->r << oct << endl;

	if (node->l)
	{
		printTextTreeNodeHelper(sst, node->l);
	}
	else
	{
		sst += "NULL";
	}

	sst += ",";

	if (node->r)
	{
		printTextTreeNodeHelper(sst, node->r);
	}
	else
	{
		sst += "NULL";
	}

	sst += ") ";
}

// print a tree in a text form
void TreeDrawer::printTextTreeNode(string& sst, ast* node)
{
	printTextTreeNodeHelper(sst, node);
}


TreeDrawer::~TreeDrawer()
{
	if (this->root)
		this->deleteTreeNode(this->root);
}

// copy a tree
ast* TreeDrawer::CopyTree(ast* root)
{
	return copyTreeNode(root);
}

// load a tree root from outside to inside
bool TreeDrawer::LoadTree(ast* root)
{
	if (this->root)
		this->deleteTreeNode(this->root);

	this->root = copyTreeNode(root);

	return true;
}

// draw the tree saved in this->root
bool TreeDrawer::Draw()
{
	if (this->root == NULL)
	{
		cout << "Drawing Error!" << endl;
		return false;
	}

	// first print a text form of tree
	printTextTree();
	// then print a graphic one
	printGraphicTree();
}

string TreeDrawer::printTextTree()
{
	if (this->root == NULL)
		return false;
	string s = "";
	this->printTextTreeNode(s, this->root);
	return s;
}

string TreeDrawer::printTextTree(ast* node)
{
	if (node == NULL)
		return false;

	string s = "";
	this->printTextTreeNode(s, node);
	return s;;
}

bool TreeDrawer::printGraphicTree()
{
	if (this->root == NULL)
		return false;

	this->printGraphicTreeNode(this->root);
	return true;
}

bool TreeDrawer::printGraphicTree(ast* node)
{
	if (node == NULL)
		return false;

	this->printGraphicTreeNode(node);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void drawBackground()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-1.0, -1.0);
	glVertex2f(1.0, -1.0);
	glVertex2f(1.0, 1.0);
	glVertex2f(-1.0, 1.0);
	glEnd();
}

struct Point{
	double x;
	double y;
};
struct Vector{
	double x;
	double y;
};
void drawVector(Point start, Point end)
{
	// draw the line from start to end point
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(start.x, start.y);
	glVertex2f(end.x, end.y);
	glEnd();

	// draw the arrow whose
	/*
	Vector v;
	v.x = end.x - start.x;
	v.y = end.y - start.y;

	double vlen = sqrt(v.x * v.x + v.y * v.y);
	Vector e;
	e.x = v.x / vlen;
	e.y = v.y / vlen;

	double co = 12;

	double arrowLen = vlen / co;
	double arrowWidth = arrowLen / 3;

	Point c;
	c.x = end.x - e.x * arrowLen;
	c.y = end.y - e.y * arrowLen;

	Vector n;
	n.x = e.y;
	n.y = -e.x;

	Point p1;
	p1.x = end.x;
	p1.y = end.y;

	Point p2;
	p2.x = c.x + n.x * arrowWidth / 2;
	p2.y = c.y + n.y * arrowWidth / 2;

	Point p3;
	p3.x = c.x - n.x * arrowWidth / 2;
	p3.y = c.y - n.y * arrowWidth / 2;

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glVertex2f(p3.x, p3.y);
	glEnd();
	*/
}

void drawString(Point pos, const string& content, int maxLen = 40)
{
	int len = content.length();
	char* s = new char[len];
	memset(s, 0, len);
	strncpy(s, content.c_str(), len);
	char* t = s;
	glRasterPos2f(pos.x, pos.y);
	//glColor3f(1.0, 1.0, 0.0);
	for (int i = 0; i < maxLen && *t != '\0'; i++, t++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *t);
	}

	delete[] s;
}

void drawNode(Point pos, double width, double height, const string& content)
{
	// draw the square background
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(pos.x, pos.y - width / 2);
	glVertex2f(pos.x, pos.y + width / 2);
	glVertex2f(pos.x + height, pos.y + width / 2);
	glVertex2f(pos.x + height, pos.y - width / 2);
	glEnd();

	// write the content in the square
	//pos.x -= width / 2;
	//pos.y -= height / 2;
	drawString(pos, content);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//drawBackground();

	DrawLevelisedTreeNode();
	DrawLevelisedTreeVector();

	glFlush();
}



UINT GlutThreadProc(ast* node)
{
	int argc = 1;
	char* argv[] = { "MFC_GLUT" };
	glutInit(&argc, argv);

	//ast* node = (ast*)lpParameter;

	//this->printTextTree(node);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(960, 960);

	Levelise(node, 0);	// must start from 0
#ifdef DEBUG
	cout << "After levelise:" << endl;
	for (int l = 0; l < treeInLevel.size(); l++)
	{
		vector<ast*> v = treeInLevel[l];
		for (int i = 0; i < v.size(); i++)
		{
			cout << v[i]->nodetype << " ";
		}
		cout << endl;
	}
#endif
	glutCreateWindow("Parse Tree");
	glutDisplayFunc(RenderScene);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
	//cout << "succeeded..." << endl;

	treeInLevel.clear();

	return 0;
}

// your code here
#include <thread>
void TreeDrawer::printGraphicTreeNode(ast* node)
{
	std::thread t1(GlutThreadProc, node);
	t1.join();

	//CWinThread* tr = AfxBeginThread(GlutThreadProc,0,0);
	//tr->m_bAutoDelete = FALSE;
}

void Levelise(ast* node, int k)
{
	if (node == NULL || (((int)node) >> 16 & 0xffff) == 0xABAB)
		return;

	if (treeInLevel.size() < k + 1)	// k start from 0
	{
		vector<ast*> newLevel;
		treeInLevel.push_back(newLevel);
	}

	treeInLevel[k].push_back(node);

	// 该顺序不能颠倒
	// 该顺序在画图的时候很有用

	// 左子树
	if (node && node->l)
		Levelise(node->l, k + 1);

	// 特殊节点
	if (node->nodetype == '=')	//	赋值语句 symasgn
	{
		symasgn* asgn = (symasgn*)node;

		twostrings* ii = new twostrings();
		ii->nodetype = 129;
		ii->l = NULL;
		ii->r = NULL;
		// this is dangerous!!!
		ii->str1 = asgn->cname;
		ii->str2 = asgn->name;

		Levelise(ii, k + 1);
		Levelise(asgn->v, k + 1);
		Levelise(asgn->index, k + 1);
	}

	if (node->nodetype == 'N')	//	引用语句 symref
	{
		symref* asgn = (symref*)node;
		Levelise(asgn->index, k + 1);
	}

	if (node->nodetype == 0)// 0 : builtin function call
	{
		ufncall* fcall = (ufncall*)node;
		Levelise(fcall->tl, k + 1);
	}

	if (node->nodetype == 1)// 1 : user function call
	{
		fncall* fcall = (fncall*)node;
		Levelise(fcall->tl, k + 1);
	}

	if (node->nodetype == 7)// fndec
	{
		fndec* fdec = (fndec*)node;
		Levelise(fdec->tl, k + 1);
	}

	if (node->nodetype == 'W')// W : while flow
	{
		flow* f = (flow*)node;
		Levelise(f->cond, k + 1);		// condition
		Levelise(f->tl, k + 1);			// then
		Levelise(f->el, k + 1);			// else
	}

	if (node->nodetype == 'O')//O : for _for
	{
		_for* f = (_for*)node;

		// 自己新建三个节点
#ifdef FORSESASCHILDTREE
		// 循环变量开始位置
		intcons* ii = new intcons();
		ii->nodetype = 3;
		ii->l = NULL;
		ii->r = NULL;
		ii->num = f->start;

		// 循环变量结束位置
		intcons* ie = new intcons();
		ie->nodetype = 3;
		ie->l = NULL;
		ie->r = NULL;
		ie->num = f->end;

		// 循环变量步长
		// 循环变量开始位置
		intcons* is = new intcons();
		is->nodetype = 3;
		is->l = NULL;
		is->r = NULL;
		is->num = f->step;

		Levelise(ii, k + 1);
		Levelise(ie, k + 1);
		Levelise(is, k + 1);
#endif

		Levelise(f->tl, k + 1);
	}

	if (node->nodetype == 'E')//E : foreach _foreach
	{
		_foreach* f = (_foreach*)node;


#ifdef FORSESASCHILDTREE
		// 自己新建indx和arr节点并显示
#endif

		Levelise(f->tl, k + 1);
	}

	if (node->nodetype == 'I')// I : if flow
	{
		flow* f = (flow*)node;
		Levelise(f->cond, k + 1);		// condition
		Levelise(f->tl, k + 1);			// then
		Levelise(f->el, k + 1);			// else
	}

	if (node->nodetype == 9)// class defination
	{
		csdef* f = (csdef*)node;
		Levelise(f->tl, k + 1);
	}

	if (node->nodetype == 10)// csget
	{
		csget* f = (csget*)node;
		Levelise(f->explist, k + 1);
		Levelise(f->index, k + 1);
	}


	// 右子树
	if (node && node->r)
		Levelise(node->r, k + 1);
}

void DrawLevelisedTreeNode()
{
	double posy = 0.95;
	int maxl = treeInLevel.size();
	for (int l = 0; l < maxl; l++)
	{
		vector<ast*> v = treeInLevel[l];
		int num = v.size();
		double interval = 1.9 / (num + 1);
		double posx = -0.95 + interval;

		for (int n = 0; n < num; n++)
		{
			Point p;
			p.x = posx;
			p.y = posy;

			string content = GetNodeContent(v[n]);
			drawString(p, content);

			posx += interval;
		}
		posy -= LEVEL_GAP;
	}
}

void DrawLevelisedTreeVector()
{
	double posy1 = 0.95;
	int maxl = treeInLevel.size() - 1;
	for (int l = 0; l < maxl; l++)
	{
		vector<ast*> v1 = treeInLevel[l];
		vector<ast*> v2 = treeInLevel[l + 1];

		int num1 = v1.size();
		int num2 = v2.size();
#ifdef DEBUG
		cout << l << "->" << l + 1 << ":" << endl;
		cout << "num1 = " << num1 << "; num2 = " << num2 << endl;
#endif
		double interval1 = 1.9 / (num1 + 1);
		double interval2 = 1.9 / (num2 + 1);
#ifdef DEBUG
		cout << "int1 = " << interval1 << "; int2 = " << interval2 << endl;
#endif
		double posx1 = -0.95 + interval1;
		double posx2 = -0.95 + interval2;
		double posy2 = posy1 - LEVEL_GAP;

		Point p1;
		p1.x = posx1;
		p1.y = posy1;

		Point p2;
		p2.x = posx2;
		p2.y = posy2;

		int j = 0;
		for (int i = 0; i < num1; i++)
		{
			if (v1[i]->l)
			{
#ifdef DEBUG
				cout << "draw left child (" << p2.x << "," << p2.y << ")" << endl;
#endif
				drawVector(p1, p2);
				posx2 += interval2;
				p2.x += interval2;
				j++;
			}

			// 特殊节点
			if (v1[i]->nodetype == '=')	// 赋值语句 symasgn 
			{
				symasgn* asgn = (symasgn*)v1[i];

				drawVector(p1, p2);
				posx2 += interval2;
				p2.x += interval2;
				j++;

				if (asgn->v)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}

				if (asgn->index)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}
			}

			if (v1[i]->nodetype == 'N')	//	引用语句 symref
			{
				symref* ref = (symref*)v1[i];
				if (ref->index)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}
			}

			if (v1[i]->nodetype == 0)// 0 : builtin function call
			{
				fncall* fcall = (fncall*)v1[i];
				if (fcall->tl)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}
			}

			if (v1[i]->nodetype == 1)// 1 : user function call
			{
				ufncall* fcall = (ufncall*)v1[i];
				if (fcall->tl)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}
			}

			if (v1[i]->nodetype == 7)// fndec
			{
				fndec* fdec = (fndec*)v1[i];
				if (fdec->tl)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}
			}

			if (v1[i]->nodetype == 'W')// W : while flow
			{
				flow* f = (flow*)v1[i];
				if (f->cond)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}

				if (f->tl)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}

				if (f->el)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}
			}

			if (v1[i]->nodetype == 'O')// O: for _for
			{
				_for* f = (_for*)v1[i];
#ifdef FORSESASCHILDTREE
				drawVector(p1, p2);
				posx2 += interval2;
				p2.x += interval2;
				j++;

				drawVector(p1, p2);
				posx2 += interval2;
				p2.x += interval2;
				j++;

				drawVector(p1, p2);
				posx2 += interval2;
				p2.x += interval2;
				j++;
#endif
				if (f->tl)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}
			}

			if (v1[i]->nodetype == 'E')// foreach
			{
				_foreach* f = (_foreach*)v1[i];
				if (f->tl)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}
			}

			if (v1[i]->nodetype == 'I')// I : if flow
			{
				flow* f = (flow*)v1[i];
				if (f->cond)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}

				if (f->tl)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}

				if (f->el)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}
			}

			if (v1[i]->nodetype == 9)// class defination
			{
				csdef* f = (csdef*)v1[i];
				if (f->tl)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}
			}

			if (v1[i]->nodetype == 10)// class defination
			{
				csget* f = (csget*)v1[i];
				if (f->explist)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}

				if (f->index)
				{
					drawVector(p1, p2);
					posx2 += interval2;
					p2.x += interval2;
					j++;
				}
			}

			// 特殊节点完毕

			if (v1[i]->r)
			{
#ifdef DEBUG
				cout << "draw right child(" << p2.x << "," << p2.y << ")" << endl;
#endif
				drawVector(p1, p2);
				posx2 += interval2;
				p2.x += interval2;
				j++;
			}

			p1.x += interval1;
		}

		posy1 -= LEVEL_GAP;
	}
}

string GetTypeName(int type)
{
	switch (type)
	{
	case 0:
		return "char";
	case 1:
		return "int";
	case 2:
		return "double";
	default:
		return "UNKNOWN";
		break;
	}
}

string GetNodeContent(ast* node)
{
	/*
	char str[32];
	memset(str, 0, 32);
	sprintf(str, "%d", node->nodetype);
	string content(str);
	content = "AST:" + content;
	*/
	string content = "";
	char str[32];
	memset(str, 0, 16);

	switch (node->nodetype)
	{
	case 0:
	{// Build-In function call
			  fncall* fcall = (fncall*)node;
			  content = "BuiltIn Funccall";
			  char str[16];
			  sprintf(str, ":%d", fcall->functype);
			  content += str;
			  break;
	}

	case 1:
	{// user function call
			  content = "User Funccall";
			  break;
	}

	case 2:
	{// char 
			  // content = "Charcons : ";
			  charcons* p = (charcons*)node;
			  content += p->ch;
			  break;
	}

	case 3:
	{// double
			  //content = "Intcons : ";
			  intcons* i = (intcons*)node;
			  sprintf(str, "%d", i->num);
			  content += string(str);
			  break;
	}

	case 4:
	{// double
			  //content = "Doubcons : ";
			  doubcons* d = (doubcons*)node;
			  sprintf(str, "%8lf", d->doub);
			  content += string(str);
			  break;
	}

	case 5:
	{// var
			  content += "Var ";
			  var* v = (var*)node;
			  content += string(v->name);
			  content += " as ";
			  content += GetTypeName(v->datatype);
			  break;
	}

	case 6:
	{		// array
			  arr* ar = (arr*)node;
			  content += "Arr ";
			  content += string(ar->name);
			  content += " size: ";

			  char str[16];
			  sprintf(str, "%d", ar->size);
			  content += str;

			  content += " as ";
			  content += GetTypeName(ar->datatype);
			  break;
	}
	case 7:
	{
			  fndec* fnd = (fndec*)node;
			  content += "Funcdec ";
			  content += string(fnd->name);
			  content += "(";
			  symlist* s = fnd->s;
			  while (s != NULL)
			  {
				  if (s->cur && s->cur->name)
				  {
					  content += s->cur->name;
				  }
				  else
				  {
					  // 没有参数
					  content += "void";
				  }

				  if (s->next)
					  content += ",";
				  s = s->next;
			  }
			  content += ")";

			  break;
	}

	case '=':
	{
				symasgn* asgn = (symasgn*)node;
				content += "=";
				//content += string(asgn->name);
				break;
	}

	case 'N':
	{
				symref* ref = (symref*)node;
				content += "SymRef ";
				content += string(ref->name);
				break;
	}

	case '+':
		content = "+";
		break;

	case '-':
		content = "-";
		break;

	case '*':
		content = "*";
		break;

	case '/':
		content = "/";
		break;

	case '%':
		content = "%";
		break;

	case '&':
		content = "&";
		break;

	case '|':
		content = "|";
		break;

	case '~':
		content = "~";
		break;

	case '1':
		content = ">";
		break;

	case '2':
		content = "<";
		break;

	case '3':
		content = "<>";
		break;

	case '4':
		content = "=(compare)";
		break;

	case '5':
		content = ">=";
		break;

	case '6':
		content = "<=";
		break;

	case 'M':
		content = "-";
		break;

	case 'I':
		content = "If";
		break;

	case 'W':
		content = "While";
		break;

	case 'O':
	{
				content = "For";
#ifndef FORSESASCHILDTREE
				char str[32];
				_for* f = (_for*)node;
				sprintf(str, "(%d,%d,%d)", f->start, f->end, f->step);
				content += str;
#endif
				break;
	}
	case 'E':
	{
				_foreach* f = (_foreach*)node;
				content = "Foreach(";
				content += f->index;
				content += " in ";
				content += f->arr;
				content += ")";
				break;
	}

	case 8:
	{
			  csdec* f = (csdec*)node;
			  content += "var ";
			  content += f->vname;
			  content += " as ";
			  content += f->cname;
			  break;
			  // csdec
	}


	case 9:
	{
			  csdef* f = (csdef*)node;

			  content += "class ";
			  content += f->cname;

			  if (f->fname)
			  {
				  content += " extends ";
				  content += f->fname;
			  }
			  break;
	}

	case 10:
	{
			   csget* f = (csget*)node;
			   content += "get ";
			   content += f->kname;
			   content += " in class";
			   content += f->cname;
			   break;
	}

	case 128:
	{
				singlestring* f = (singlestring*)node;
				content += f->str;
				break;
	}

	case 129:
	{
				twostrings* n = (twostrings*)node;
				if (n->str1)
				{
					content += n->str1;
					content += "->";
				}
				content += n->str2;
				break;
	}

	case 'R':
		content = "Return";
		break;

	default:
		//content += "Unknown ";
		content += node->nodetype;
		break;
	}

	return content;
}