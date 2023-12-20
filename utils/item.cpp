#include "./item.h"
using namespace std;

// Item
/*----------------------------------------------------------------------------------------------------------------------------*/

Item::Item(const string& n) : name(n) {}

string Item::getname() const {
    return name;
}

// EnemyAttack
/*----------------------------------------------------------------------------------------------------------------------------*/

EnemyAttack::EnemyAttack(const string& n) : Item(n), damagePower(0) {}

EnemyAttack::EnemyAttack(const string& n, int dp) : Item(n), damagePower(dp) {}

EnemyAttack::EnemyAttack(const EnemyAttack& ea) : EnemyAttack(ea.name, ea.damagePower) {}

void EnemyAttack::setDP(int dp) {
    this->damagePower = dp;
}

int EnemyAttack::returnDP() {
    return damagePower;
}

// OrdinaryItem
/*----------------------------------------------------------------------------------------------------------------------------*/
OrdinaryItem::OrdinaryItem(const std::string& n) : Item(n), getHP(0), getSTR(0), getMP(0) {}

OrdinaryItem::OrdinaryItem(const std::string& n, int getHP, int getSTR, int getMP) : Item(n) {
    this->getHP = getHP;
    this->getSTR = getSTR;
    this->getMP = getMP;
}

OrdinaryItem::OrdinaryItem(const OrdinaryItem& it) : Item(it.name) {
    this->getHP = it.getHP;
    this->getSTR = it.getSTR;
    this->getMP = it.getMP;
}

void OrdinaryItem::print() const {
    // Implementation of print function
}

int OrdinaryItem::getHealth() const {
    return getHP;
}

int OrdinaryItem::getStrength() const {
    return getSTR;
}

int OrdinaryItem::getMagic() const {
    return getMP;
}

// Magic
/*----------------------------------------------------------------------------------------------------------------------------*/

Magic::Magic(const std::string& n) : Item(n), health(0), costMagicPower(0) {}

Magic::Magic(const std::string& n, int hp, int costMagicPower) : Item(n) {
    this->health = hp;
    this->costMagicPower = costMagicPower;
}

Magic::Magic(const Magic& ma) : Item(ma.name) {
    this->health = ma.health;
    this->costMagicPower = ma.costMagicPower;
}

void Magic::print() const {
    string temp = "魔法名稱：" + name + " 可造成的傷害值:" + (to_string(health)) + " 需消耗" + (to_string(costMagicPower)) + "魔力值(MP)";
    show_wstring(temp, window, textOb);
}

int Magic::getHealth() const {
    return health;
}

int Magic::getCostMagicPower() const {
    return costMagicPower;
}




