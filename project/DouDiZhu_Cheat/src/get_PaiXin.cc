#include <vector>
#include <PaiXin.h>
#include <string>
using namespace std;

string name[MAX_N + 5] = {
    "", "", "", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "Ace", "2", "joker", "JOKER"
};

//牌型类方法
vector<Card_Type *> Card_Type::get_PaiXin(int *arr) {
    vector<Card_Type *> temp;
    vector<Card_Type *> Pass = Pass::get(arr);
    vector<Card_Type *> One = OneCard::get(arr);
    vector<Card_Type *> Two = TwoCard::get(arr);
    vector<Card_Type *> Three = ThreeToCard::get(arr);
    vector<Card_Type *> sz = ShunZi::get(arr);
    vector<Card_Type *> ZhaDan = Bomb::get(arr);
    vector<Card_Type *> WangZha = Rocket::get(arr);
    vector<Card_Type *> Feiji = AirPlane::get(arr);
    vector<Card_Type *> LianDui = DoubleShunZi::get(arr);
    vector<Card_Type *> FourtoCard = BombToCard::get(arr);
    for (auto x : One) temp.push_back(x);
    for (auto x : Two) temp.push_back(x);
    for (auto x : Three) temp.push_back(x);
    for (auto x : sz) temp.push_back(x);
    for (auto x : ZhaDan) temp.push_back(x);
    for (auto x : WangZha) temp.push_back(x);
    for (auto x : Feiji) temp.push_back(x);
    for (auto x : LianDui) temp.push_back(x);
    for (auto x : FourtoCard) temp.push_back(x);
    for (auto x : Pass) temp.push_back(x);
    return temp;
}

void Card_Type::output_arr(int *arr) {
    for (int i = 3; i < MAX_N; i++) {
        if (!arr[i]) continue;
        cout << name[i] << "*" << arr[i] << " ";
    }
    cout << endl;
    return ;
}

//单张类中的方法

ostream& OneCard::output() {
    cout << "DanZhang "<< name[x] ;
    return cout;
}

vector<Card_Type *> OneCard::get(int *arr) {
    vector<Card_Type *> temp;
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i] == 0) continue;
        temp.push_back(new OneCard(i));
    }
    return temp;
}

//对子中类方法

vector<Card_Type *> TwoCard::get(int *arr) {
    vector<Card_Type *> temp;
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i] < 2) continue;
        temp.push_back(new TwoCard(i));
    }
    return temp;
}

ostream &TwoCard::output() {
    cout << "DuiZi " << name[x];
    return cout;
}

//三带中类方法

vector<Card_Type *> ThreeToCard::get(int *arr) {
    vector<Card_Type *> temp;
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i] < 3) continue;
        //三不带
        temp.push_back(new ThreeToCard(i, new Pass()));
        for (int j = 3; j < MAX_N; j++) {
            if (!arr[j] || j == i) continue;
            //三带一
            temp.push_back(new ThreeToCard(i, new OneCard(j)));
            //三带二
            if (arr[j] >= 2) temp.push_back(new ThreeToCard(i, new TwoCard(j)));
        }
    }
    return temp;
}

ostream &ThreeToCard::output() {
    cout << "Three " << name[x] << " Dai ";
    this->p->output();
    return cout;
}

//飞机中类方法

vector<Card_Type *> AirPlane::To_One(int *arr, int x, int y) {
    vector<Card_Type *> temp;
    for (int i = 3; i < MAX_N; i++) {
        if (!arr[i]) continue; 
        arr[i] -= 1;
        for (int j = i; j < MAX_N; j++) {
            if (!arr[j]) continue;
            temp.push_back(new AirPlane(x, y, new OneCard(i), new OneCard(j)));
        }
        arr[i] += 1;
    }
    return temp;
}


vector<Card_Type *> AirPlane::To_Two(int *arr, int x, int y) {
    vector<Card_Type *> temp; 
    for (int i = 3; i <= 15; i++) {
        if (arr[i] < 2) continue; 
        arr[i] -= 2;
        for (int j = i; j <= 15; j++) {
            if (arr[j] < 2) continue;
            temp.push_back(new AirPlane(x, y, new TwoCard(i), new TwoCard(j)));
       }
        arr[i] += 2;
    }
    return temp;
}

vector<Card_Type *> AirPlane::get(int *arr) {
    vector<Card_Type *> temp;
    int flag = 1;
    for (int i = 3; i <= 14; i++) {
        if (arr[i] < 3) continue;
        if (i + 1 > 14 || arr[i + 1] < 3) continue;
        arr[i] -= 3;
        arr[i + 1] -= 3;
        //飞机不带的情况
        temp.push_back(new AirPlane(i, i + 1, new Pass(), new Pass()));
        //飞机带俩单
        vector<Card_Type *> one = To_One(arr, i, i + 1);
        //飞机带俩对
        vector<Card_Type *> two = To_Two(arr, i, i + 1);
        temp.insert(temp.end(), one.begin(), one.end());
        temp.insert(temp.end(), two.begin(), two.end());
        arr[i] += 3;
        arr[i + 1] += 3;
    }
    return temp;
}

ostream &AirPlane::output() {
    cout << "Three " << name[x] << " And Three " << name[y] << " Dai ";
    p1->output();
    cout << " And ";
    p2->output();
    return cout;
}

//炸弹类处理
vector<Card_Type *> Bomb::get(int *arr) {
    vector<Card_Type *> temp;
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i] != 4) continue;
        temp.push_back(new Bomb(i));
    }
    return temp;
}

ostream &Bomb::output() {
    cout << "ZhaDan " << name[x];
    return cout;
}

//4带2类处理

vector<Card_Type *> BombToCard::To_One(int *arr, int x) {
    vector<Card_Type *> temp;
    for (int i = 3; i < MAX_N; i++) {
        if (!arr[i]) continue; 
        arr[i] -= 1;
        for (int j = i; j < MAX_N; j++) {
            if (!arr[j]) continue;
            temp.push_back(new BombToCard(x, new OneCard(i), new OneCard(j)));
        }
        arr[i] += 1;
    }
    return temp;
}

vector<Card_Type *> BombToCard::To_Two(int *arr, int x) {
    vector<Card_Type *> temp;
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i] < 2) continue; 
        arr[i] -= 2;
        for (int j = i; j < MAX_N; j++) {
            if (arr[j] < 2) continue;
            temp.push_back(new BombToCard(x, new TwoCard(i), new TwoCard(j)));
        }
        arr[i] += 2;
    }
    return temp;
}

vector<Card_Type *> BombToCard::get(int *arr) {
    vector<Card_Type *> temp;
    for (int i = 3; i < MAX_N; i++) {
        if (arr[i] != 4) continue;
        //对数组进行处理当前牌是使用状态
        arr[i] -= 4;
        //4带两张单牌
        vector<Card_Type *> one = To_One(arr, i);
        //4带两个对子
        vector<Card_Type *> two = To_Two(arr, i);
        temp.insert(temp.end(), one.begin(), one.end());
        temp.insert(temp.end(), two.begin(), two.end());
        //归还，表示当前牌是未使用状态
        arr[i] += 4;
    }
    return temp;
}

ostream &BombToCard::output() {
    cout << "Four " << name[x] << " Dai ";
    p1->output();
    cout << " And ";
    p2->output();
    return cout;
}
//王炸类中方法
vector<Card_Type *> Rocket::get(int *arr) {
    vector<Card_Type *> temp;
    if (arr[16] && arr[17]) temp.push_back(new Rocket());
    return temp;
}

ostream &Rocket::output() {
    cout << "Rocket!!";
    return cout;
}

//顺子类中方法

vector<Card_Type *> ShunZi::get(int *arr) {
    vector<Card_Type *> temp;
    //顺子最小长度为5
    //最大长度3-A 为12
    for (int l = 5; l <= 12; l++) {
        //从最小位置开始枚举
        //顺子最大的初始位置为A - 目前枚举长度 + 1
        for (int i = 3, I = 14 - l + 1; i <= I; i++) {
            int flag = 1;
            //枚举当前长度每个位置是否有牌
            //如果有位置没牌就无法组成顺子
            for (int j = i; j < i + l; j++) {
                if (arr[j]) continue;
                flag = 0;
                break;
            }
            if (flag == 1) temp.push_back(new ShunZi(i, l));
        }
    }
    return temp;
}

ostream &ShunZi::output() {
    cout << "ShunZi ";
    for (int i = x; i < x + len; i++) {
        i != x && cout << " ";
        cout << name[i];
    }
    return cout;
}
//连对类中的方法

vector<Card_Type *> DoubleShunZi::get(int *arr) {
    vector<Card_Type *> temp;
    for (int l = 3; l <= 12; l++) {
        for (int i = 3, I = 14 - l + 1; i <= I; i++) {
            int flag = 1;
            for (int j = i; j < i + l; j++) {
                if (arr[j] >= 2) continue;
                flag = 0;
                break;
            }
            if (flag) temp.push_back(new DoubleShunZi(i, l));
        }
    }
    return temp;
}

ostream &DoubleShunZi::output() {
    for (int i = x; i < x + len; i++) {
        i != x && cout << " ";
        cout << name[i] << name[i];
    }
    return cout;
}
//不要类中方法

vector<Card_Type *> Pass::get(int *) {
    vector<Card_Type *> temp;
    temp.push_back(new Pass());
    return temp; 
}

ostream &Pass::output() {
    cout << "Pass";
    return  cout;
}

