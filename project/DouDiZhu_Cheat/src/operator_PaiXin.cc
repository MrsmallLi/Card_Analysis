/*************************************************************************
	> File Name: operator_PaiXin.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 06 May 2024 04:57:51 PM CST
 ************************************************************************/

#include <iostream>
#include <PaiXin.h>
using namespace std;

vector<Card_Type *> Card_Type::get_PaiXinGuan(int *arr, Card_Type *pre) {
    vector<Card_Type *> temp = Card_Type::get_PaiXin(arr);
    vector<Card_Type *> suppress_temp;
    for (auto x : temp) {
        if (x->operator>(pre)) suppress_temp.push_back(x);
        //这种出牌策略不行时直接删掉，不占内存
        else delete x;
    }
    return suppress_temp;
}

//传入参数是上家出牌牌型
//bool operator>(Card_Type *pre) {}

//单张管牌方式
//只能管单张和Pass
bool OneCard::operator>(Card_Type *pre) {
    PaiXin_Type op = pre->type;
    switch (op) {
        case PaiXin_Type::Pass_Type : return true;
        case PaiXin_Type::OneCard_Type : {
            OneCard *_pre = dynamic_cast<OneCard *>(pre);
            return this->x > _pre->x;
        } break;
        default : return false; 
    }
    return false;
}

//对子管牌方式
//只能管对子和Pass
bool TwoCard::operator>(Card_Type *pre) {
    PaiXin_Type op = pre->type;
    switch (op) {
        case PaiXin_Type::Pass_Type : return true;
        case PaiXin_Type::TwoCard_Type : {
            TwoCard *_pre = dynamic_cast<TwoCard *>(pre);
            return this->x > _pre->x;
        } break;
        default : return false;
    }
    return false;
}

//三代管牌方式
//只能管对应的三带方式和pass
bool ThreeToCard::operator>(Card_Type *pre) {
    PaiXin_Type op = pre->type;
    switch (op) {
        case PaiXin_Type::Pass_Type : return true;
        case PaiXin_Type::ThreeToCard_Type : {
            ThreeToCard *_pre = dynamic_cast<ThreeToCard *>(pre);
            if (_pre->p->type != this->p->type) return false;
            return this->x > _pre->x;
        } break;
        default : return false;
    }
    return false;
}

//飞机管牌方式
//飞机的飞机和大于上家的和就可以管
//并且只能管对应方式
bool AirPlane::operator>(Card_Type *pre) {
    PaiXin_Type op = pre->type;
    switch (op) {
        case PaiXin_Type::Pass_Type : return true;
        case PaiXin_Type::AirPlane_Type : {
            AirPlane *_pre = dynamic_cast<AirPlane *>(pre);
            if (_pre->p1->type != this->p1->type) return false;
            return ((this->x + this->y) > (_pre->x + _pre->y));
        } break;
        default : return false;
    }
    return false;
}

//炸弹管牌方式
//除了王炸和比他大的炸弹管不了都可以管
bool Bomb::operator>(Card_Type *pre) {
    PaiXin_Type op = pre->type;
    switch (op) {
        case PaiXin_Type::Rocket_Type : return false;
        case PaiXin_Type::Bomb_Type : {
            Bomb *_pre = dynamic_cast<Bomb *>(pre);
            return this->x > _pre->x;
        } break;
        default : return true;
    }
    return true;
}

//4带2管牌方式
//4张牌比他大并且带的牌型一样
bool BombToCard::operator>(Card_Type *pre) {
    PaiXin_Type op = pre->type;
    switch (op) {
        case PaiXin_Type::Pass_Type : return true;
        case PaiXin_Type::BombToCard_Type : {
            BombToCard *_pre = dynamic_cast<BombToCard *>(pre);
            if (_pre->p1->type != this->p1->type) return false;
            return this->x > _pre->x;
        } break;
        default : return false;
    }
    return true;
}

//顺子管牌方式
//先判断长度是否相同
//相同再判断起始位置大小

bool ShunZi::operator>(Card_Type *pre) {
    PaiXin_Type op = pre->type;
    switch (op) {
        case PaiXin_Type::Pass_Type : return true;
        case PaiXin_Type::ShunZi_Type : {
            ShunZi *_pre = dynamic_cast<ShunZi *>(pre);
            if (_pre->len != this->len) return false;
            return this->x > _pre->x;
        } break;
        default : return false;
    }
    return false;
}

//连对管牌方式和顺子一样
bool DoubleShunZi::operator>(Card_Type *pre) {
    PaiXin_Type op = pre->type;
    switch (op) {
        case PaiXin_Type::Pass_Type : return true;
        case PaiXin_Type::DoubleShunZi_Type : {
            DoubleShunZi *_pre = dynamic_cast<DoubleShunZi *>(pre);
            if (_pre->len != this->len) return false;
            return this->x > _pre->x;
        } break;
        default : return false;
    }
    return false;
}

//只要上家不是Pass
//就可以不要
bool Pass::operator>(Card_Type *pre) {
    if (pre->type == PaiXin_Type::Pass_Type) return false;
    return true;
}

//火箭
//什么都可以管
bool Rocket::operator>(Card_Type *pre) {
    PaiXin_Type op = pre->type;
    switch(op) {
        case PaiXin_Type::Rocket_Type : return false;
        default : return true;
    }
    return false;
}
