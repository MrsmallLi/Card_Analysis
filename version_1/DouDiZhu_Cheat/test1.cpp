/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 04 May 2024 08:12:28 PM CST
 ************************************************************************/

#include <iostream>
#include <PaiXin.h>
#include <vector>
using namespace std;


int arr[MAX_N + 5] = {0};

void usge(int op = 10) {
    if (op >= 1) printf("1.DanZhang\n");
    if (op >= 2) printf("2.DuiZi\n");
    if (op >= 3) printf("3.SanDai\n");
    if (op >= 5) printf("4.ShunZi\n");
    if (op >= 4) printf("5.FeiJi\n");
    if (op >= 6) printf("6.LianDui\n");
    if (op >= 7) printf("7.ZhaDan\n");
    if (op >= 8) printf("8.WangZha\n");
    if (op >= 9) printf("9.4Dai2\n");
    if (op >= 10) printf("10.Pass\n");
    printf("intput(-1): quit\n");
    printf("input : ");
    return ;
}


Card_Type *func(int max_op = 10) {
    Card_Type *p;
    int x = 0;
    while (1) {
        usge(max_op);
        cin >> x;
        if (x < 1 || x > 10) {
            printf("input error!!\n");
            printf("plese input(1-10 or -1)\n");
            continue;
        }
        int num;
        switch (x) {
            case 1: {
                cin >> num;
                p = new OneCard(num);
            } break;
            case 2: {
                cin >> num;
                p = new TwoCard(num);
            } break;
            case 3: {
                cin >> num;
                p = new ThreeToCard(num, func(2));
            } break;
            case 4: {
                printf("起始其位置x :");
                cin >> num;
                int len;
                printf("长度len :");
                cin >> len;
                p = new ShunZi(num, len);
            } break;
            case 5: {
                while (1) {
                int num2;
                cin >> num2 >> num;
                    if (abs(num2 - num) != 1) {
                        printf("input error");
                        continue;
                    }
                    p = new AirPlane(num2, num, func(2), func(2));
                    break;
                }
            } break;
            case 6: {
                printf("起始其位置x :");
                cin >> num;
                int len;
                printf("长度len :");
                cin >> len;
                p = new DoubleShunZi(num, len);
            } break;
            case 7: {
                cin >> num;
                p = new Bomb(num);
            } break;
            case 8: {
                p = new Rocket();
            } break;
            case 9: {
                cin >> num;
                p = new BombToCard(num, func(2), func(2));
            } break;
            case 10: {
                p = new Pass();
            } break;
        }
        break;
    }
    return p;
}

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


int main() {
    get_input_data();
    //vector<Card_Type *> temp1 = Card_Type::get_PaiXinGuan(a, new Pass());
    //vector<Card_Type *> temp2 = Card_Type::get_PaiXinGuan(b, new Pass());
    //vector<Card_Type *> temp1 = Card_Type::get_PaiXin(a) ;
    //vector<Card_Type *> temp2 = Card_Type::get_PaiXin(b);
    Card_Type::output_arr(a);
    //Card_Type::output_arr(b);
    vector<Card_Type *> temp1 = Card_Type::get_PaiXinGuan(a, func());
    for (auto x : temp1) x->output() << endl;
    //cout << "======================" << endl;
    //for (auto x : temp2) x->output() << endl;
    return 0;
}
