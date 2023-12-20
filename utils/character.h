#ifndef CHARACTER_H
#define CHARACTER_H

#include "./item.h"

const int ItemListSize = 5;
const int MagicListSize = 5;

class Character {
public:
    std::string name;
    int health;  //生命值
    Character(const std::string& n, int hp) : name(n), health(hp) {}
    virtual void setHealth(int hp) = 0;
};

class Player : public Character {
private:
    int strength;         //力量值
    int magicPower;       //魔法值
    OrdinaryItem** itemLists; //道具欄
    Magic** magicLists;       //可使用魔法欄

public:
    Player();
    Player(const std::string& n, int hp, int str, int mp);
    ~Player();

    std::string getName() const { return name;}
    int getHealth() const { return health; }
    int getStrength() const { return strength; }
    int getMagicPower() const { return magicPower; }
    void setHealth(int hp) override;
    void setMagicPower(int mp);
    void setStrength(int str);
    void print() const;
    void addItem(OrdinaryItem& item);
    void addMagic(Magic& magic);
    void basicAttack(Character& target);
    void useItem();
    void useMagic(Character& target);
    void playerTurn(Character& target, sf::Sprite& sprite, sf::RectangleShape& blackRect);
    bool canUseMagic();
    bool hasItems();
};

class Enemy : public Character {
private:
    EnemyAttack** enemyAttackists; // 攻擊技能列

public:
    Enemy(const std::string& n, int hp);
    ~Enemy();

    void print() const; // 輸出敵人資訊
    std::string getName() const;
    void setHealth(int hp) override; // 設定敵人血量
    void addEnemyAttack(EnemyAttack& ea); // 增加敵人攻擊技能
    void enemyTurn(Player& target, sf::Sprite sprite, sf::RectangleShape blackRect);
};

#endif