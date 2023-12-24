#include "./game.h"
using namespace std;

// Game
/*----------------------------------------------------------------------------------------------------------------------------*/

Game::Game() {
    this->chapterCnt = 0;
    this->gameOver = false;
    for (int i = 0; i < chapterMaxSize; i++) {
        chapters[i] = nullptr;
    }
}

Game::~Game() {
    for (int i = 0; i < chapterMaxSize; i++) {
        if (chapters[i] != nullptr) {
            delete chapters[i];
        }
    }
}

void Game::addChapter(std::ifstream& storyTxt) {
    this->chapters[this->chapterCnt] = &storyTxt;
    this->chapterCnt += 1;
}

void Game::startTheStory(sf::RenderWindow& window, sf::Text& textOb, sf::Music* music, sf::Music* battleMusic, sf::Texture* texture, sf::Texture* battleTexture, sf::Event& event) {
    for(int i = 0; i < this->chapterCnt; i++){
        music[i].play();
        music[i].setLoop(true);      
        this->gameOver = this->story_teller(*chapters[i], window, textOb, music[i], battleMusic, texture[i], battleTexture, event);
        music[i].stop();
        if(this->gameOver == true)
            break;
    }
}

bool Game::story_teller(std::ifstream& storyTxt, sf::RenderWindow& window, sf::Text& textOb, sf::Music& music, sf::Music* battleMusic, sf::Texture& texture, sf::Texture* battleTexture, sf::Event& event) {
    bool findSCtagMode = false;
    bool findSTtagMode = false;
    bool findSBtagMode = false;
    int choice = 0;

    while(!this->gameOver)
    {
        // goto (skip the windows event)
        STORY_RESET:

        // Clear the window
        window.clear();

        // 讀入一行
        string text;
        getline(storyTxt, text);
        cout << text << endl;

        // Draw the appropriate background image
        sf::Sprite sprite(texture);
        window.draw(sprite);  

        // Add a rectangle to fill the area below the text with black
        sf::RectangleShape blackRect(sf::Vector2f(1920, 1080));
        draw_black_box(window, blackRect);

        // 判別是否是標籤
        if(text[0] == '[')
        {
            // 標籤類型
            string tagType = text.substr(1, 2);
            char* codePtr = &text[3];
            
            // 標籤內的數字（若有的話）
            int code = 0;
            if((tagType == "OP") or (tagType == "SC") or (tagType == "CO") or (tagType == "AP") or (tagType == "HP") or (tagType == "MP") or (tagType == "SR"))
            {
                code = stoi(codePtr);
            }
            
            if(findSCtagMode)
            {
                // cout << "find SC" << endl;
                // 找到相應的場景，則停止找場景的mode
                if((tagType == "SC") and (code == choice))
                {
                    cout << "find SC" << endl;
                    findSCtagMode = false;
                    goto STORY_RESET;
                }
                else{
                    goto STORY_RESET;
                }
                
            }else if(findSTtagMode)
            {
                cout << "find ST" << endl;
                // 找到ST場景，則停止找場景的mode
                if(tagType == "ST")
                {
                    findSTtagMode = false;
                    goto STORY_RESET;
                }
                else{
                    goto STORY_RESET;
                }
                
            }else if(findSBtagMode)
            {
                // 找到SB場景，則停止找場景的mode
                if(tagType == "SB")
                {
                    findSBtagMode = false;
                    goto STORY_RESET;
                }
                
            }else
            {
                // 判別標籤類型
                if(tagType == "CP")
                {
                    cout << "find setting" << endl;
                    string name;
                    int health;
                    int strength;
                    int magicPower;
                    
                    storyTxt >> name >> health >> strength >> magicPower;
                    
                    Player chosenplayer(name, health, strength, magicPower);
                    this->setPlayer(chosenplayer);
                    
                }else if(tagType == "AM")
                {
                    
                    string name;
                    int health;
                    int costMagicPower;
                                        
                    storyTxt >> name >> health >> costMagicPower;
                    
                    Magic magic(name, health, costMagicPower);
                    this->player.addMagic(magic);
                    
                }else if(tagType == "AT")
                {
                    
                    string name;
                    int getHP;
                    int getSTR;
                    int getMP;
                    
                    storyTxt >> name >> getHP >> getSTR >> getMP;
                    
                    OrdinaryItem item(name, getHP, getSTR, getMP);
                    this->player.addItem(item);
                    
                }else if(tagType == "OP")
                {
                    // 印出題目
                    int pos = STRING_POSITION;
                    for (int i = 0; i < code + 1; i++) {
                        getline(storyTxt, text);
                        wstring wline = converter.from_bytes(text);
                        wstring subLine = wline;
                        
                        // Output the current substring
                        textOb.setString(subLine);
                        textOb.setPosition(10, pos);  // Adjust the position based on your layout
                        pos += 30;
                        window.draw(textOb);
                    }
                    
                    // 玩家進行選擇
                    string temp = "請輸入選項: ";
                    wstring wline = converter.from_bytes(temp);
                    textOb.setString(wline);
                    textOb.setPosition(10, pos);  // 請根據您的版面配置調整位置
                    window.draw(textOb);
                    window.display();

                    // 玩家進行選擇
                    while (window.waitEvent(event)) {
                        if (event.type == sf::Event::TextEntered && event.text.unicode >= '1' && event.text.unicode <= '0' + code) {
                            choice = event.text.unicode - '0';
                            break;
                        } 
                        else if(event.type == sf::Event::Closed){
                            window.close();
                        }
                    }
                    
                    // 開啟搜尋SC特定場景的模式
                    findSCtagMode = true;
                    goto STORY_RESET;
                    
                }else if(tagType == "SK")
                {
                    // 開啟搜尋ST場景的模式
                    findSTtagMode = true;
                    goto STORY_RESET;
                    
                }else if(tagType == "CO")
                {
                    // 印出題目
                    int pos = STRING_POSITION;
                    for (int i = 0; i < code + 1; i++) {
                        getline(storyTxt, text);
                        wstring wline = converter.from_bytes(text);
                        wstring subLine = wline;
                        
                        // Output the current substring
                        textOb.setString(subLine);
                        textOb.setPosition(10, pos);  // Adjust the position based on your layout
                        pos += 30;
                        window.draw(textOb);
                    }
                    window.display();
                    
                    // 玩家進行選擇，但只是個趣味的選擇，不會影響到任何劇情，所以不開啟搜尋SC特定場景的模式
                    string temp = "請輸入選項: ";
                    wstring wline = converter.from_bytes(temp);
                    textOb.setString(wline);
                    textOb.setPosition(10, pos);  // 請根據您的版面配置調整位置
                    window.draw(textOb);
                    window.display();

                    // 玩家進行選擇
                    while (window.waitEvent(event)) {
                        if (event.type == sf::Event::TextEntered && event.text.unicode >= '1' && event.text.unicode <= '0' + code) {
                            break;
                        } 
                        else if(event.type == sf::Event::Closed){
                            window.close();
                        }
                    }
                    
                }else if(tagType == "FI")
                {
                    
                    string name;
                    int health;
                    
                    storyTxt >> name >> health;
                    Enemy enemy(name, health);
                    
                    int attackCnt = 3;
                    
                    for(int i = 0; i < attackCnt; i++)
                    {
                        string attackName;
                        int damagePower;
                        
                        storyTxt >> attackName >> damagePower;
                        
                        EnemyAttack enemyAttack(attackName, damagePower);
                        enemy.addEnemyAttack(enemyAttack);
                    }
                    cout << "battle start" << endl;
                    music.stop();

                    if(name == "助教Wu"){
                        battleMusic[1].play();
                        battleMusic[1].setLoop(true); 
                        this->gameOver = battle(this->player, enemy, window, textOb, event, battleTexture[1]);
                        battleMusic[1].stop();
                    }
                    else if(name == "Professor_Ho"){
                        battleMusic[2].play();
                        battleMusic[2].setLoop(true);
                        this->gameOver = battle(this->player, enemy, window, textOb, event, battleTexture[2]);
                        battleMusic[2].stop();
                    }
                    else if(name == "Professor_Kong"){
                        battleMusic[3].play();
                        battleMusic[3].setLoop(true);
                        this->gameOver = battle(this->player, enemy, window, textOb, event, battleTexture[3]);
                        battleMusic[3].stop();
                    }
                    else{
                        battleMusic[0].play();
                        battleMusic[0].setLoop(true);
                        this->gameOver = battle(this->player, enemy, window, textOb, event, battleTexture[0]);
                        battleMusic[0].stop();
                    }                    
                    cout << gameOver << endl;
                    cout << "battle end" << endl;
                    music.play();
                    music.setLoop(true);
                    goto STORY_RESET;
                    
                }else if(tagType == "AP")
                {

                    int pos = STRING_POSITION;
                    for (int i = 0; i < code; i++) {
                        getline(storyTxt, text);
                        wstring wline = converter.from_bytes(text);
                        wstring subLine = wline;
                        
                        // Output the current substring
                        textOb.setString(subLine);
                        textOb.setPosition(10, pos);  // Adjust the position based on your layout
                        pos += 30;
                        window.draw(textOb);
                    }
                    window.display();
                    
                }else if(tagType == "EN")
                {
                    // 結束while迴圈
                    return 0;
                    
                }else if(tagType == "SJ")
                {
                    // 開啟搜尋SB場景的模式
                    findSBtagMode = true;
                    goto STORY_RESET;
                    
                }else if(tagType == "HP")
                {
                    this->player.setHealth(code);
                    string temp = "增加HP";
                    show_wstring(temp, window, textOb);
                    
                }else if(tagType == "MP")
                {
                    this->player.setMagicPower(code);
                    string temp = "增加MP";
                    show_wstring(temp, window, textOb);
                    
                }else if(tagType == "SR")
                {
                    this->player.setStrength(code);
                    string temp = "增加SR";
                    show_wstring(temp, window, textOb);
                    
                }else if(tagType == "GO")
                {
                    return 1;
                }
            }
        }
        else
        {
            if((!findSCtagMode) and (!findSTtagMode)) // 在這兩種模式時，直接跳過沒特定標籤的敘述
            {
                show_wstring(text, window, textOb);
            }
            else{
                goto STORY_RESET;
            }
        }
        cout << "pass" << endl;
        // Wait for Enter key or close event
        windows_event(window, event);
    };

    music.stop();

    return 1;
}

void Game::setPlayer(Player& chosenPlayer) {
    this->player = Player(chosenPlayer);
    string temp = "你選擇成為一位" + this->player.name;
    show_wstring(temp, window, textOb); 
}


