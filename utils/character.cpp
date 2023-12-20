#include "./character.h"
using namespace std;

// Player
/*----------------------------------------------------------------------------------------------------------------------------*/

Player::Player() : Character("player", 0) {
    strength = 0;//初始力量值
    magicPower = 0;//初始魔力值
    itemLists = new OrdinaryItem*[ItemListSize];
    magicLists = new Magic*[MagicListSize];
    for(int i = 0; i < ItemListSize; i++){
        if(itemLists[i] != nullptr)
            itemLists[i] = nullptr;
    }
    for(int i = 0; i < MagicListSize; i++){
        if(magicLists[i] != nullptr)
            magicLists[i] = nullptr;
    }
}

Player::Player(const string& n, int hp, int str, int mp) : Character(n, hp) {
    strength = str;//初始力量值
    magicPower = mp;//初始魔力值
    itemLists = new OrdinaryItem*[ItemListSize];
    magicLists = new Magic*[MagicListSize];
    for(int i = 0; i < ItemListSize; i++){
        if(itemLists[i] != nullptr)
            itemLists[i] = nullptr;
    }
    for(int i = 0; i < MagicListSize; i++){
        if(magicLists[i] != nullptr)
            magicLists[i] = nullptr;
    }
}

Player::~Player() {
    /*
    for(int i = 0; i < ItemListSize; i++){
        if(itemLists[i] != nullptr)
            delete itemLists[i];
    }
    for(int i = 0; i < MagicListSize; i++){
        if(magicLists[i] != nullptr)
            delete magicLists[i];
    }
    
    delete[] itemLists;
    delete[] magicLists;
    */
}

void Player::setHealth(int hp) {
    this->health += hp;
}

void Player::setMagicPower(int mp) {
    this->magicPower += mp;
}

void Player::setStrength(int str) {
    this->strength += str;
}

void Player::print() const {
    string temp = "你目前的能力值：";
    string temp2 = "生命值(HP):";
    temp += temp2 + to_string(this->health) + " 魔法值(MP):" + to_string(this->magicPower) + " 力量(STR):" + to_string(this->strength);
    show_wstring(temp, window, textOb);   
}

void Player::addItem(OrdinaryItem& item) {
    // 清掉滿了的道具欄再加新道具
    if (itemLists[ItemListSize - 1] != nullptr) {
        for (int i = 0; i < ItemListSize - 1; i++) {
            delete itemLists[i];
            itemLists[i] = new OrdinaryItem(*itemLists[i + 1]);
        }
        delete itemLists[ItemListSize - 1]; // 釋放最後一個元素的記憶體
        itemLists[ItemListSize - 1] = new OrdinaryItem(item);
    }
    // 沒滿加新道具
    else {
        for (int i = 0; i < ItemListSize; i++) {
            if (itemLists[i] == nullptr) {
                itemLists[i] = new OrdinaryItem(item);
                string temp = "成功新增道具：" + item.getname();
                show_wstring(temp, window, textOb);
                break;
            }
        }
    }
}

void Player::addMagic(Magic& magic) {
    //清掉滿了的魔法欄再加新魔法
    if(magicLists[MagicListSize - 1] != nullptr){
        for(int i = 0; i < MagicListSize - 1; i++){
            delete magicLists[i];
            magicLists[i] = new Magic(*magicLists[i + 1]);
        }
        delete magicLists[MagicListSize - 1]; // 釋放最後一個元素的記憶體
        magicLists[MagicListSize-1] = new Magic(magic);
    }
    //沒滿加新魔法
    else{
        for(int i = 0; i < MagicListSize; i++){
            if(magicLists[i] == nullptr){
                magicLists[i] = new Magic(magic);
                string temp = "成功新增魔法：" + (magic.getname());
                show_wstring(temp, window, textOb);                  
                break;
            }
        }
    }
}

void Player::basicAttack(Character& target) {
    target.health -= this->strength;
    string temp = "你對" + target.name + "造成了" + (to_string(this->strength)) + "點傷害";
    show_wstring(temp, window, textOb); 
}

void Player::useItem() {
    //將目前可使用的魔法顯示出來
    int pos = STRING_POSITION;
    string showItemList = "目前可使用道具：";
    wstring wline = converter.from_bytes(showItemList);
    textOb.setString(wline);
    textOb.setPosition(10, pos);  // Adjust the position based on your layout
    pos += 30;
    window.draw(textOb);

    for (int i = 0; i < ItemListSize; i++) {
        if (itemLists[i] != nullptr){
            string allItem = to_string(i + 1) + '.' + (itemLists[i]->getname()) + ",可增加生命值：" + to_string(itemLists[i]->getHealth()) + "點,可增加魔力值：" + to_string(itemLists[i]->getMagic()) + "點,可增加力量值：" + to_string(itemLists[i]->getStrength()) + ",";
            wstring wline = converter.from_bytes(allItem);
            wstring subLine = wline;
            
            // Output the current substring
            textOb.setString(subLine);
            textOb.setPosition(10, pos);  // Adjust the position based on your layout
            pos += 30;
            window.draw(textOb);
        }
    }

    string chooseQuestion = "請輸入欲使用道具之編號:";
    wstring wline2 = converter.from_bytes(chooseQuestion); 
    textOb.setString(wline2);
    textOb.setPosition(10, pos);  // Adjust the position based on your layout
    pos += 30;
    window.draw(textOb);
    window.display();

    // ITEM_CHOOSE:
    // 玩家進行選擇
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::TextEntered && event.text.unicode > '0' && event.text.unicode <= ('0' + ItemListSize)) {
            int option = (event.text.unicode - 48) - 1;
            cout << "option " << option << endl; 
            if(itemLists[option] != nullptr){
                this->health += itemLists[option]->getHealth();
                this->strength += itemLists[option]->getStrength();
                this->magicPower += itemLists[option]->getMagic();

                //使用道具
                string temp = "你使用了" + (itemLists[option]->getname()) + "，增加了生命值" + to_string(itemLists[option]->getHealth()) + "點,魔力值" + to_string(itemLists[option]->getMagic()) + "點,力量值" + to_string(itemLists[option]->getStrength()) + "點";
                wstring wline2 = converter.from_bytes(temp); 
                textOb.setString(wline2);
                textOb.setPosition(10, pos);  // Adjust the position based on your layout
                window.draw(textOb);
                window.display();

                delete itemLists[option];  // 刪除使用過的道具
                itemLists[option] = nullptr;

                // 把使用過的道具後面所有道具都往前一個位置
                for (int i = option; i < ItemListSize - 1; i++) {
                    itemLists[i] = itemLists[i + 1];
                    itemLists[i + 1] = nullptr;
                }

                break;
            }
        } 
        else if(event.type == sf::Event::Closed){
            window.close();
        }
    }
}

void Player::useMagic(Character& target) {
    //將目前可使用的魔法顯示出來
    int pos = STRING_POSITION;
    string showMagicList = "目前可使用魔法：";
    wstring wline = converter.from_bytes(showMagicList);
    textOb.setString(wline);
    textOb.setPosition(10, pos);  // Adjust the position based on your layout
    pos += 30;
    window.draw(textOb);

    for (int i = 0; i < MagicListSize; i++) {
        if (magicLists[i] != nullptr){
            string allMagic = to_string(i + 1) + '.' + (magicLists[i]->getname()) + " 可對敵人造成傷害值: " + to_string(magicLists[i]->getHealth()) + " 消耗魔力值: " + to_string(magicLists[i]->getCostMagicPower());
            wstring wline = converter.from_bytes(allMagic);
            wstring subLine = wline;
            
            // Output the current substring
            textOb.setString(subLine);
            textOb.setPosition(10, pos);  // Adjust the position based on your layout
            pos += 30;
            window.draw(textOb);
        }
    }

    string chooseQuestion = "請輸入欲使用魔法之編號:";
    wstring wline2 = converter.from_bytes(chooseQuestion);    
    textOb.setString(wline2);
    textOb.setPosition(10, pos);  // Adjust the position based on your layout
    pos += 30;
    window.draw(textOb);
    window.display();

    MAGIC_CHOOSE:
    // 玩家進行選擇
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::TextEntered && event.text.unicode > '0' && event.text.unicode <= ('0' + MagicListSize)) { 
            int option = (event.text.unicode - 48) - 1;
            cout << "option " << option << endl; 
            if(magicLists[option] != nullptr){
                if (this->magicPower >= magicLists[option]->getCostMagicPower()) {
                    target.health -= magicLists[option]->getHealth();
                    this->magicPower -= magicLists[option]->getCostMagicPower();

                    string temp = "你使用了 " + (magicLists[option]->getname()) + "，消耗了" + to_string(magicLists[option]->getCostMagicPower()) + "點魔力值，對 " + (target.name) + "造成了" + to_string(magicLists[option]->getHealth()) + "點傷害。";
                    wstring wline = converter.from_bytes(temp); 
                    textOb.setString(wline);
                    textOb.setPosition(10, pos + 30);  // Adjust the position based on your layout
                    window.draw(textOb);
                    window.display();
                    break;
                }
                else {
                    string temp = "魔力值不足，無法使用此魔法！";
                    wstring wline2 = converter.from_bytes(temp);
                    textOb.setString(wline2);
                    textOb.setPosition(10, pos);  // Adjust the position based on your layout
                    window.draw(textOb);
                    window.display();
                    goto MAGIC_CHOOSE;
                }
            }
        } 
        else if(event.type == sf::Event::Closed){
            window.close();
        }
    }
}

void Player::playerTurn(Character& target, sf::Sprite& sprite, sf::RectangleShape& blackRect) {
    int choice = 0;
    bool validChoice = false;
    do {
        playerRESTART:
        window.clear();
        window.draw(sprite);
        draw_black_box(window, blackRect);
        string temp = "輪到你的回合了：請選擇你的行動: 1.普通攻擊, 2.使用魔法, 3.使用道具: ";
        show_wstring(temp, window, textOb);    
        window.clear();
        window.draw(sprite);
        draw_black_box(window, blackRect);

        // 玩家進行選擇
        while (window.waitEvent(event)) {
            if (event.type == sf::Event::TextEntered && event.text.unicode == '1') {
                basicAttack(target); // 普通攻擊
                validChoice = true;
                break;
            } 
            else if (event.type == sf::Event::TextEntered && event.text.unicode == '2') {
                // cout << MagicListSize << endl;
                // windows_event(window, event);
                if (canUseMagic()) { // 檢查是否有足夠的魔力值使用至少一個魔法
                    useMagic(target); // 使用魔法
                    validChoice = true;
                    break;
                }
                else {
                    string temp = "魔力值不足，無法使用魔法！";
                    show_wstring(temp, window, textOb);
                    windows_event(window, event);
                    goto playerRESTART;   
                }
            } 
            else if (event.type == sf::Event::TextEntered && event.text.unicode == '3') {
                if (hasItems()) { // 檢查是否有道具可以使用
                    useItem(); // 使用道具函數
                    validChoice = true;
                    break;
                }
                else {
                    string temp = "道具列表是空的，沒有道具可以使用！";
                    show_wstring(temp, window, textOb);  
                    windows_event(window, event);
                    goto playerRESTART;   
                }
            } 
            else if(event.type == sf::Event::Closed){
                window.close();
            }
        }; 
    } while (!validChoice);
}

bool Player::canUseMagic() {
    for (int i = 0; i < MagicListSize; i++) {
        if (magicLists[i] != nullptr && magicPower >= magicLists[i]->getCostMagicPower()) {
            return true;
        }
    }
    return false;
}

bool Player::hasItems() {
    for (int i = 0; i < ItemListSize; i++) {
        if (itemLists[i] != nullptr) {
            return true;
        }
    }
    return false;
}

// Enemy
/*----------------------------------------------------------------------------------------------------------------------------*/
Enemy::Enemy(const string& n, int hp) : Character(n, hp) {
    enemyAttackists = new EnemyAttack*[3];
    for (int i = 0; i < 3; i++) {
        if (enemyAttackists[i] != nullptr)
            enemyAttackists[i] = nullptr;
    }
}

Enemy::~Enemy() {
    for (int i = 0; i < 3; i++) {
        if (enemyAttackists[i] != nullptr)
            delete enemyAttackists[i];
    }
    delete[] enemyAttackists;
}

void Enemy::print() const {
    string temp = name + "目前的生命值(HP):" + to_string(health);
    wstring wline = converter.from_bytes(temp);
    textOb.setString(wline);
    textOb.setPosition(10, STRING_POSITION + 30); // 請根據您的版面配置調整位置
    window.draw(textOb);
    window.display();
}

void Enemy::setHealth(int hp) {
    this->health += hp;
}

void Enemy::addEnemyAttack(EnemyAttack& ea) {
    for (int i = 0; i < 3; i++) {
        if (enemyAttackists[i] == nullptr) {
            enemyAttackists[i] = new EnemyAttack(ea);
            break;
        }
    }
}

void Enemy::enemyTurn(Player& player, sf::Sprite sprite, sf::RectangleShape blackRect) {
    string temp = "輪到 " + name + " 的回合了";
    show_wstring(temp, window, textOb);
    windows_event(window, event);
    window.clear();
    window.draw(sprite);
    draw_black_box(window, blackRect);

    int enemyAction = rand() % 3; // 從0到2隨機選擇一個攻擊
    EnemyAttack* attack = enemyAttackists[enemyAction]; // 從敵人的攻擊技能列表中取得技能

    if (attack != nullptr) {
        player.health -= attack->returnDP(); // 玩家的血量被扣除敵人技能傷害值
        string temp = name + "使用了" + (attack->getname()) + "，對你造成了" + (to_string(attack->returnDP())) + "點傷害。";
        show_wstring(temp, window, textOb);
    }
}


