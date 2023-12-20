#include "./utils.h"
using namespace std;

bool battle(Player& player, Enemy& enemy, sf::RenderWindow& window, sf::Text& textOb, sf::Event& event, sf::Texture& texture) {
    sf::Sprite sprite(texture);
    window.draw(sprite);
    sf::RectangleShape blackRect(sf::Vector2f(1920, 1080));
    draw_black_box(window, blackRect);
    
    string temp = "戰鬥開始!";
    show_wstring(temp, window, textOb);
    windows_event(window, event);

    // 紀錄能力值初始值
    int originalPlayerHP = player.getHealth();
    int originalPlayerMP = player.getMagicPower();
    int originalPlayerSTR = player.getMagicPower();
    cout << "what1" << endl;
    cout << player.health << " " << enemy.health << endl;

    while (player.health > 0 && enemy.health > 0) {
        // Clear the window
        window.clear();
        cout << "what2" << endl;

        sf::Sprite sprite(texture);
        window.draw(sprite);

        // Add a rectangle to fill the area below the text with black
        sf::RectangleShape blackRect(sf::Vector2f(1920, 1080));
        draw_black_box(window, blackRect);

        // 顯示玩家和敵人目前狀態
        player.print();
        enemy.print();
        windows_event(window, event);
        window.clear();
        window.draw(sprite);
        draw_black_box(window, blackRect);
        
        // 玩家回合
        player.playerTurn(enemy, sprite, blackRect);
        windows_event(window, event);
        window.clear();
        window.draw(sprite);      
        draw_black_box(window, blackRect);  

        // 檢查是否擊敗敵人
        if (enemy.health <= 0) {
            temp = "你贏了！恭喜你打倒 " + enemy.name + "!";
            show_wstring(temp, window, textOb);
            windows_event(window, event);

            //恢復成戰鬥前能力值
            player.setHealth(originalPlayerHP);
            player.setMagicPower(originalPlayerMP);
            player.setStrength(originalPlayerSTR);
            return 0;
        }
        
        // 顯示玩家和敵人當前狀態
        player.print();
        enemy.print();
        windows_event(window, event);
        window.clear();
        window.draw(sprite);
        draw_black_box(window, blackRect);
        
        // 敵人回合
        enemy.enemyTurn(player, sprite, blackRect);
        windows_event(window, event);
        window.clear();
        window.draw(sprite);
        draw_black_box(window, blackRect);

        // 檢查玩家是否被打敗
        if (player.health <= 0) {
            temp = "你輸了！你已被 "+ enemy.name + " 打倒。";
            show_wstring(temp, window, textOb);
            windows_event(window, event);
            return 1;
        }
    }
    
    return 1;
}

void final_ending(sf::RenderWindow& window, sf::Text& textOb) {
    // // 讀取銘謝詞
    ifstream creditsFile("./src/txt/credicts.txt");
    cout << "enter success" << endl;
    vector<string> creditsLines;
    string line;
    while (getline(creditsFile, line)) {
        creditsLines.push_back(line);
    }
    creditsFile.close();

    // 設定初始位置
    sf::Vector2f textPosition(window.getSize().x / 2 - textOb.getLocalBounds().width / 2, -textOb.getLocalBounds().height);

    textOb.setPosition(textPosition);

    // 設定時鐘
    sf::Clock clock;

    // 設定文字顯示間隔位置
    float lineHeight = 300.0f;
    float totalHeight = creditsLines.size() * lineHeight;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 計算時間
        sf::Time elapsed = clock.restart();

        // 計算文字下降速度
        float descentSpeed = 50.0f; // 調整這個值以改變下降速度
        textPosition.y += descentSpeed * elapsed.asSeconds();

        // 更新文字位置
        textOb.setPosition(textPosition);

        window.clear();

        // 繪製文字
        for (const auto& line : creditsLines) {
            textOb.setString(line);
            window.draw(textOb);
            textPosition.y += lineHeight;
        }

        window.display();
        cout << "finish" << endl;

        windows_event(window, event);

        // 檢查是否顯示完所有文字
        if (textPosition.y > window.getSize().y + totalHeight) {
            window.close();
        }
    }
}