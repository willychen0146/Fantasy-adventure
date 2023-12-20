#ifndef ITEM_H
#define ITEM_H

#include "./window.h"
#include <string>

class Item {
protected:
    std::string name;

public:
    Item(const std::string& n);
    std::string getname() const;
};

//敵人攻擊技能
class EnemyAttack : public Item {
private:
    int damagePower; // hp damage power

public:
    EnemyAttack(const std::string& n);
    EnemyAttack(const std::string& n, int dp);
    EnemyAttack(const EnemyAttack& ea);
    void setDP(int dp);
    int returnDP();
};

//一般道具
class OrdinaryItem : public Item {
private:
    int getHP; //增加多少血量
    int getSTR; //增加多少力量
    int getMP; //增加多少魔力

public:
    OrdinaryItem(const std::string& n);
    OrdinaryItem(const std::string& n, int getHP, int getSTR, int getMP);
    OrdinaryItem(const OrdinaryItem& it);
    void print() const;
    int getHealth() const; // 回傳增加多少血量
    int getStrength() const; // 回傳增加多少力量
    int getMagic() const; // 回傳增加多少魔力
};


//魔法
class Magic : public Item {
private:
    int health; // 減少敵人生命
    int costMagicPower; // 需消耗魔力值

public:
    Magic(const std::string& n);
    Magic(const std::string& n, int hp, int costMagicPower);
    Magic(const Magic& ma);
    void print() const;
    int getHealth() const;
    int getCostMagicPower() const;
};


#endif