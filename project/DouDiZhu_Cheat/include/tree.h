/*************************************************************************
	> File Name: tree.h
	> Author: 
	> Mail: 
	> Created Time: Mon 06 May 2024 07:16:18 PM CST
 ************************************************************************/

#ifndef _TREE_H
#define _TREE_H
#include <vector>
#include <PaiXin.h>
class Node {
public :
    Node();
    Node(Card_Type *, int);
    int win_flag;
    Card_Type *p;
    vector<Node *> child;
};

void get_Game_Tree(Node *, int *, int *);
#endif
