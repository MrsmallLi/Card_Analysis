/*************************************************************************
	> File Name: PaiXin_contructor.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 06 May 2024 05:04:13 PM CST
 ************************************************************************/

//牌型类中的构造函数
#include <iostream>
#include <PaiXin.h>
using namespace std;

//牌型
Card_Type::Card_Type(PaiXin_Type type) : type(type) {}

//单张
OneCard::OneCard(int x) : Card_Type(PaiXin_Type::OneCard_Type), x(x) {}

//对子 
TwoCard::TwoCard(int x) : Card_Type(PaiXin_Type::TwoCard_Type), x(x) {}

//三带
ThreeToCard::ThreeToCard(int x, Card_Type *p) : Card_Type(PaiXin_Type::ThreeToCard_Type), x(x), p(p) {}

//飞机
AirPlane::AirPlane(int x, int y) : Card_Type(PaiXin_Type::AirPlane_Type), x(x), y(y), p1(nullptr), p2(nullptr){}

AirPlane::AirPlane(int x, int y, Card_Type *p1, Card_Type *p2) : Card_Type(PaiXin_Type::AirPlane_Type), x(x), y(y), p1(p1), p2(p2){}

//炸弹
Bomb::Bomb(int x) : Card_Type(PaiXin_Type::Bomb_Type), x(x) {}

//4带2
BombToCard::BombToCard(int x, Card_Type *p1, Card_Type *p2) : Card_Type(PaiXin_Type::BombToCard_Type), x(x), p1(p1), p2(p2) {}

BombToCard::BombToCard(int x) : Card_Type(PaiXin_Type::BombToCard_Type), x(x), p1(nullptr), p2(nullptr){}

//王炸
Rocket::Rocket() : Card_Type(PaiXin_Type::Rocket_Type) {}

//连子
ShunZi::ShunZi(int x, int len) : Card_Type(PaiXin_Type::ShunZi_Type), x(x), len(len) {}

//连对
DoubleShunZi::DoubleShunZi(int x, int len) : Card_Type(PaiXin_Type::DoubleShunZi_Type), x(x), len(len) {}

//不要
Pass::Pass() : Card_Type(PaiXin_Type::Pass_Type) {}
