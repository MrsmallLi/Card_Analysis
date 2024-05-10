/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 06 May 2024 07:46:58 PM CST
 ************************************************************************/

#include <iostream>
#include <PaiXin.h>
#include <tree.h>
#include <stack>
using namespace std;

int a[MAX_N + 5] = {0};
int b[MAX_N + 5] = {0};

void read(FILE *f, int *arr) {
    int x;
    while (fscanf(f, "%d", &x) != EOF) {
        if (x == 0) break;
        arr[x] += 1;
    }
    return ;
}

void get_input_data() {
    FILE *f = fopen("input", "r");
    read(f, a);
    read(f, b);
    fclose(f);
    return ;
}

void run(Node *root) {
    printf("root is %s\n", root->win_flag ? "win" : "lose");
    //通过博弈树来获取必胜出牌顺序
    stack<Node *> s;
    //将根节点压入栈中
    s.push(root);
    while (!s.empty()) {
        printf("%s: ", s.size() % 2 ? "-->" : "   "); 
        Card_Type::output_arr(a);
        printf("%s: ", s.size() % 2 ? "   " : "-->"); 
        Card_Type::output_arr(b);
        Node *node = s.top();
        int op;
        do {
            printf("[%3d] : back\n", -1);
            for (int i = 0; i < node->child.size(); i++) {
                Node *n = node->child[i];
                printf("[%3d] : %s --> ", i, n->win_flag ? "" : "win");
                n->p->output();
                printf("\n");
            }
            cout << "input : " << endl;
            cin >> op;
            if (op == -1 || op < node->child.size()) break;
            else {
                printf("%d is input error\n", op);
                continue;
            }
        } while(1);
        //后悔出牌收回出牌
        if (op == -1) {
            s.pop();
            node->p->back(s.size() % 2 ? a : b);
        }else {
            node->child[op]->p->tack(s.size() % 2 ? a : b);
            s.push(node->child[op]);
        }
    }
}

int main() {
    /*
    get_input_data();
    Card_Type::output_arr(a);
    Card_Type::output_arr(b);
    Node *root = new Node();
    get_Game_Tree(root, a, b);
    */
    //根节点作为不要
    //那么就是我们先出牌
    Node *root = new Node();
    cout << "new node" << endl;
    get_input_data();
    cout << "get data" << endl;
    //获取博弈树
    Card_Type::output_arr(a);
    Card_Type::output_arr(b);
    get_Game_Tree(root, a, b);
    cout << "get game tree" << endl;
    run(root);
    return 0;
}

