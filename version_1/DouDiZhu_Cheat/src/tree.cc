/*************************************************************************
	> File Name: tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 06 May 2024 07:19:35 PM CST
 ************************************************************************/

#include <iostream>
#include <tree.h>
#include <PaiXin.h>
using namespace std;

Node::Node() : win_flag(0), p(new Pass()){}

Node::Node(Card_Type *p, int x = 0) : win_flag(x), p(p){}

//由于a先出也就是我们人先出
//所以根节点为Pass
//root表示上手牌出牌
//a表示当前出牌人
//b表示下手出派人
static bool confirm(int *arr) {
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i]) return false;
    } 
    return true;
}

void get_Game_Tree(Node *root, int *a, int *b) {
    //确认对手是否还有手牌
    if (confirm(b)) {
        root->win_flag = 0;
        return ;
    }
    vector<Card_Type *> temp = Card_Type::get_PaiXinGuan(a, root->p);
    for (int i = 0; i < temp.size(); i++) {
        //为当前可以管牌牌型创建一个新节点
        Node *node = new Node(temp[i]);
        //当前管牌牌型已经出了
        //那么a数组中就应该少了出的牌
        temp[i]->tack(a);
        //然后该b出牌
        get_Game_Tree(node, b, a);
        //回到出牌之前，把这次出的牌返回到手牌中
        temp[i]->back(a);
        //将node作为当前节点的子孩子
        root->child.push_back(node);
        if (!node->win_flag) {
            root->win_flag = 1;
            //只要有了一个必胜策略就退出枚举牌型
            break;
        }
    }
    return ;
}


