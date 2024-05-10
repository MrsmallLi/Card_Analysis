
//
#include <PaiXin.h>
#include <tree.h>

Node::Node() : p(new Pass()), win_flag(0) {}
Node::Node(Card_Type *p, int win = 0) : p(p), win_flag(win) {}

static bool checkEmpty(int *arr) {
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i]) return false;
    }
    return true;
}

void get_Game_Tree(Node *root, int *a, int *b) {
    if (checkEmpty(b)) {
        root->win_flag = 0;
        return ;
    }
    vector<Card_Type *> temp = Card_Type::get_PaiXinGuan(a, root->p);
    for (int i = 0; i < temp.size(); i++) {
        Node *node = new Node(temp[i]);
        temp[i]->tack(a);
        get_Game_Tree(node, b, a);
        temp[i]->back(a);
        root->child.push_back(node);
        if (node->win_flag == 0) {
            root->win_flag = 1;
            break;
        }
    }
    return ;
}
