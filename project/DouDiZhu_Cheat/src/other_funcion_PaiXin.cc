/*************************************************************************
	> File Name: other_funcion_PaiXin.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 06 May 2024 07:35:02 PM CST
 ************************************************************************/

#include <iostream>
#include <PaiXin.h>
using namespace std;

//单张
void OneCard::tack(int *arr){
    arr[x] -= 1;
    return ;
}

void OneCard::back(int *arr){
    arr[x] += 1;
    return ;
}

//对子
void TwoCard::tack(int *arr){
    arr[x] -= 2;
    return ;
}

void TwoCard::back(int *arr){
    arr[x] += 2;
    return ;
}

//三带
void ThreeToCard::tack(int *arr){
    arr[x] -= 3;
    p->tack(arr);
    return ;
}

void ThreeToCard::back(int *arr){
    arr[x] += 3;
    this->p->back(arr);
    return ;
}

//飞机
void AirPlane::tack(int *arr){
    arr[x] -= 3;
    arr[y] -= 3;
    this->p1->tack(arr);
    this->p2->tack(arr);
    return ;
}

void AirPlane::back(int *arr){
    arr[x] += 3;
    arr[y] += 3;
    this->p1->back(arr);
    this->p2->back(arr);
    return ;
}
//炸弹
void Bomb::tack(int *arr){
    arr[x] -= 4;
    return ;
}

void Bomb::back(int *arr){
    arr[x] += 4;
    return ;
}

//4带2
void BombToCard::tack(int *arr){
    arr[x] -= 4;
    p1->tack(arr);
    p2->tack(arr);
    return ;
}

void BombToCard::back(int *arr){
    arr[x] += 4;
    p1->back(arr);
    p2->back(arr);
    return ;
}
//顺子
void ShunZi::tack(int *arr){
    for (int i = x; i < x + len; i++) {
        arr[i] -= 1;
    }
    return ;
}

void ShunZi::back(int *arr){
    for (int i = x; i < x + len; i++) {
        arr[i] += 1;
    }
    return ;
}

//连对
void DoubleShunZi::tack(int *arr){
    for (int i = x; i < x + len; i++) {
        arr[i] -= 2;
    }
    return ;
}

void DoubleShunZi::back(int *arr){
    for (int i = x; i < x + len; i++) {
        arr[i] += 2;
    }
}

//火箭
void Rocket::tack(int *arr) {
    arr[16] -= 1;
    arr[17] -= 1;
    return ;
}

void Rocket::back(int *arr) {
    arr[16] += 1;
    arr[17] += 1;
    return ;
}

//不要
void Pass::tack(int *arr) { return ; }
void Pass::back(int *arr) { return ; }
