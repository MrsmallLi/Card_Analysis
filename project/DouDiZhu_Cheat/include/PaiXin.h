/*************************************************************************
	> File Name: Paixin.h
	> Author: 
	> Mail: 
	> Created Time: Sat 04 May 2024 08:00:24 PM CST
 ************************************************************************/

#ifndef _PAIXIN_H
#define _PAIXIN_H

#include <iostream>
#include <vector>
using namespace std;
#define MAX_N 18

enum class PaiXin_Type {
    OneCard_Type,
    TwoCard_Type,
    ThreeToCard_Type,
    ShunZi_Type,
    AirPlane_Type,
    Bomb_Type,
    BombToCard_Type,
    Rocket_Type,
    DoubleShunZi_Type,
    Pass_Type
};

//牌型作为派生类
class Card_Type {
public :    
    Card_Type(PaiXin_Type type);
    static vector<Card_Type *> get_PaiXin(int *);
    static vector<Card_Type *> get_PaiXinGuan(int *, Card_Type *);
    static void output_arr(int *);
    virtual void tack(int *) = 0;
    virtual void back(int *) = 0;
    virtual ostream& output() = 0;
    virtual bool operator>(Card_Type *) = 0;
    virtual ~Card_Type() = default;
    PaiXin_Type type;
};

//子类单张
class OneCard : public Card_Type {
public :
    OneCard(int x);
    void tack(int *) override;
    void back(int *) override;
    ostream& output() override;
    static vector<Card_Type *> get(int *);
    bool operator>(Card_Type *) override;
private :
    //x表示什么单牌
    int x;
};

//子类对子
class TwoCard : public Card_Type {
public :
    TwoCard(int x);
    ostream& output() override;
    void tack(int *) override;
    void back(int *) override;
    bool operator>(Card_Type *) override;
    static vector<Card_Type *> get(int *);
private :
    //x表示什么对子
    int x;
};

//子类三带
class ThreeToCard : public Card_Type {
public :
    ThreeToCard(int x, Card_Type *p);
    ostream& output() override;
    void tack(int *) override;
    void back(int *) override;
    bool operator>(Card_Type *) override;
    static vector<Card_Type *> get(int *);
private :
    //x表示3带是什么
    //p指向带的牌型
    int x;
    Card_Type *p;
};

//子类飞机
class AirPlane : public Card_Type {
public :
    AirPlane(int x, int y);
    AirPlane(int x, int y, Card_Type *, Card_Type *);
    ostream& output() override;
    bool operator>(Card_Type *) override;
    void tack(int *) override;
    void back(int *) override;
    static vector<Card_Type *> To_One(int *, int, int);
    static vector<Card_Type *> To_Two(int *, int, int);
    static vector<Card_Type *> get(int *);
private :
    //飞机的两个三带是什么
    //p1和p2指向带的什么
    int x, y;
    Card_Type *p1, *p2;
};

//子类炸弹
class Bomb : public Card_Type {
public :
    Bomb(int x);
    ostream& output() override;
    void tack(int *) override;
    void back(int *) override;
    bool operator>(Card_Type *) override;
    static vector<Card_Type *> get(int *);
private :
    //x表示是什么炸弹
    int x;
};

//子类四带二
class BombToCard : public Card_Type {
public : 
    BombToCard(int x);
    BombToCard(int x, Card_Type *, Card_Type *);
    static vector<Card_Type *> get(int *);
    static vector<Card_Type *> To_One(int *, int);
    static vector<Card_Type *> To_Two(int *, int);
    ostream& output() override;
    bool operator>(Card_Type *) override;
    void tack(int *) override;
    void back(int *) override;
private :
    //x表示当前4带的牌是多少
    int x;
    //p1，p2用来指向带的牌型
    Card_Type *p1, *p2;
};

//子类顺子
class ShunZi : public Card_Type {
public :   
    ShunZi(int , int );
    static vector<Card_Type *> get(int *);
    ostream& output() override;
    bool operator>(Card_Type *) override;
    void tack(int *) override;
    void back(int *) override;
private :
    //x表示起始牌
    //len表示顺子长度
    int x, len;
};

//子类火箭
class Rocket : public Card_Type {
public :
    Rocket();
    static vector<Card_Type *> get(int *);
    ostream& output() override;
    bool operator>(Card_Type *) override;
    void tack(int *) override;
    void back(int *) override;
};

//子类不要
class Pass : public Card_Type {
public :
    Pass();
    static vector<Card_Type *> get(int *);
    ostream& output() override;
    bool operator>(Card_Type *) override;
    void tack(int *) override;
    void back(int *) override;
};

//子类连对
class DoubleShunZi : public Card_Type {
public :
    DoubleShunZi(int , int);
    static vector<Card_Type *> get(int *);
    ostream &output() override;
    bool operator>(Card_Type *) override;
    void tack(int *) override;
    void back(int *) override;
private :
    //x表示连对的起始位置
    //len表示连对的长度
    int x, len;
};

#endif
