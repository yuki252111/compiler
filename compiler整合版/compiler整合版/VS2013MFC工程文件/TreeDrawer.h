/*
* Filename: TreeDrawer.h
* FileDes : In this file you can see the declaration of class TreeDrawer and its member functions.
*/

// TreeDrawer用法：
// TreeDrawer treeDrawer;
// ast* root = ...
// treeDrawer.LoadTree(root);
// treeDrawer.Draw();
// 或者
// TreeDrawer treeDrawer;
// ast* root = ...;
// treeDrawer.printTextTree(root);
// treeDrawer.printGraphicTree(root);

#ifndef __DRAW_TREE_H__
#define __DRAW_TREE_H__

#include "defination.h"			// In this file are the tree types
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

class TreeDrawer
{
public:
	TreeDrawer();
	//TreeDrawer(ast* root);
	//TreeDrawer(TreeDrawer& t);
	~TreeDrawer();

private:
	ast* root;

private:
	void deleteTreeNode(ast* node);
	ast* copyTreeNode(ast* node);

private:
	void printTextTreeNodeHelper(string& sst, ast* node);
	void printGraphicTreeNodeHelper(ast* node);

private:

public:


private:
	void printTextTreeNode(string& sst, ast* node);
	void printGraphicTreeNode(ast* node);

public:
	string printTextTree(ast* node);		// 打印文字型的树
	bool printGraphicTree(ast* node);		// 打印图形树
	string printTextTree();
	bool printGraphicTree();

public:
	bool LoadTree(ast* root);	// Load an ast Tree from an existing tree
	ast* CopyTree(ast* root);	// Copy an ast Tree from root
	bool Draw();				// Draw the tree saved in the file
	bool Draw(ast* root);		// Draw the tree saved in root
};

#endif // __DRAW_TREE_H__