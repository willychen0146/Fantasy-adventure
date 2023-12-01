#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/*----------------------------------------------Forward declarations----------------------------------------------*/

void clear_screen();
// void story_teller(const string& text);
void story_teller(const string& message);
void play_music(const string& str, sf::Music& music);
void read_dialogues(const string& filename, vector<string>& dialogues);

/*----------------------------------------------------class----------------------------------------------------*/

// 1: Basic Character class
class Character {
public:
    string name;
    int health;
    int attack;

    // Constructor
    Character(string n, int h, int a) : name(n), health(h), attack(a) {}

    // Member function
    void displayStats() const {
        cout << "角色: " << name << "\n生命值: " << health << "\n攻擊力: " << attack << endl;
        cin.ignore();
    }
};

// 2: Main Character class, inherits from Character
class MainCharacter : public Character {
public:
    string profession;

    // Constructor
    MainCharacter(string n, int h, int a, string p) : Character(n, h, a), profession(p) {}
};

// 3: NPC class
class NPC {
public:
    string name;
    string dialogue;

    // Constructor
    NPC(string n, string d) : name(n), dialogue(d) {}

    // Talk function
    void talk() const {
        cout << name << ": " << dialogue << endl;
        cin.ignore();
        clear_screen();
    }
};

// 4: Enemy class
class Enemy {
public:
    string name;
    int health;
    int attack;

    // Constructor
    Enemy(string n, int h, int a) : name(n), health(h), attack(a) {}

    // Member function
    void displayStats() const {
        cout << "敵人: " << name << "\n生命值: " << health << "\n攻擊力: " << attack << endl;
        cin.ignore();
    }
};

/*------------------------------------------------function headers------------------------------------------------*/

// choose_character
void choose_character(MainCharacter& player);
// interact with NPC in difference chapter
void NPC_interaction_s2(const vector<string>& dialogues);
void NPC_interaction_s4();
void NPC_interaction_s6();
// battle setting
void battle(Enemy& boss, MainCharacter& player);
// every scene
void scene_2(vector<string>& dialogues);
void scene_3(MainCharacter& player);
void scene_4();
void scene_5(MainCharacter& player);
void scene_6();
void scene_7(MainCharacter& player);
void scene_8(const MainCharacter& player);
void scene_9(const MainCharacter& player);
// ending scene
void ending_scene(const MainCharacter& player);
void ending_conclusion(const MainCharacter& player);

// Clear screen
void clear_screen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/Unix
#endif
}

// Story text showing function (1 text display 1 times)
void story_teller(const string& text) {
    cout << text;
    cin.ignore();
    clear_screen();
}

// play music
void play_music(const string& str, sf::Music& music){
    if (!music.openFromFile(str)) {
        cerr << "Failed to load music file!" << endl;
    }
}

// read txt dialogues file
void read_dialogues(const string& filename, vector<string>& dialogues) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        dialogues.push_back(line);
    }
    file.close();
}

/*----------------------------------------------------Main----------------------------------------------------*/
int main() {
    clear_screen();

    //create music object
    sf::Music music;

    // Scene 1
    play_music("./src/ost/The-Prelude.mp3", music);
    music.play();

    story_teller("歡迎來到冒險遊戲！請按 Enter 進入遊戲");
    story_teller("遊戲開始！");
    story_teller("請先選擇出身職業: ");

    // Create and choose the main character
    MainCharacter player("", 0, 0, "");
    choose_character(player);

    // Display selected main character information
    player.displayStats();
    clear_screen();
    story_teller("遊戲開始！");
    story_teller("請按 Enter 進入魔法學園");

    clear_screen();
    music.stop();

    // Scene 2
    play_music("./src/ost/Chasing-the-Black-Caped-Man.mp3", music);
    music.play();
    vector<string> dialogues;
    scene_2(dialogues);
    clear_screen();
    music.stop();

    // Scene 3
    play_music("./src/ost/Fighting.mp3", music);
    music.play();
    scene_3(player);
    clear_screen();
    music.stop();

    // Scene 4
    play_music("./src/ost/Chasing-the-Black-Caped-Man.mp3", music);
    music.play();
    scene_4();
    clear_screen();
    music.stop();

    // Scene 5
    play_music("./src/ost/Fighting.mp3", music);
    music.play();
    scene_5(player);
    clear_screen();
    music.stop();

    // Scene 6
    play_music("./src/ost/Chasing-the-Black-Caped-Man.mp3", music);
    music.play();
    scene_6();
    clear_screen();
    music.stop();

    // Scene 7
    play_music("./src/ost/J-E-N-O-V-A.mp3", music);
    music.play();
    scene_7(player);
    clear_screen();
    music.stop();

    // Scene 8
    play_music("./src/ost/Yomawari.mp3", music);
    music.play();
    scene_8(player);
    clear_screen();

    // Scene 9
    scene_9(player);
    clear_screen();
    music.stop();

    return 0;
}

/*---------------------------------------------------Ending---------------------------------------------------*/

/*---------------------------------------------------Scene 2---------------------------------------------------*/

void scene_2(vector<string>& dialogues) {
    string filename = "./src/text/scene_2.txt";
    read_dialogues(filename, dialogues);
    story_teller(dialogues[0]);
    NPC_interaction_s2(dialogues);
}

/*---------------------------------------------------Scene 3---------------------------------------------------*/

void scene_3(MainCharacter& player) {
    story_teller("你已經準備好面對敵人了！");
    // create enemy 1
    Enemy assistantProfessor("Assistant Professor", 50, 1);
    // enter battle
    battle(assistantProfessor, player);
}

/*---------------------------------------------------Scene 4---------------------------------------------------*/

void scene_4(){
    story_teller("冒險繼續，你進入了新的區域。");
    NPC_interaction_s4();
}

/*---------------------------------------------------Scene 5---------------------------------------------------*/

void scene_5(MainCharacter& player){
    story_teller("你已經準備好面對新的敵人了！");
    // create enemy 2
    Enemy mrHe("Mr. He", 50, 10);
    // enter battle
    battle(mrHe, player);
}

/*---------------------------------------------------Scene 6---------------------------------------------------*/

void scene_6(){
    story_teller("你進入了新的區域，準備迎接最終的挑戰！");
    NPC_interaction_s6();
}

/*---------------------------------------------------Scene 7---------------------------------------------------*/

void scene_7(MainCharacter& player){
    story_teller("你來到了最終區域，面對最強大的敵人！");
    // create final enemy
    Enemy mrKong("Mr. Kong", 50, 25);
    // enter battle
    battle(mrKong, player);
    story_teller("你成功擊敗了最終敵人 Mr. Kong，拯救了學院，遊戲結束！");
}

/*---------------------------------------------------Scene 8---------------------------------------------------*/

void scene_8(const MainCharacter& player){
    story_teller("遊戲結束，顯示結局！");
    ending_scene(player);
}

/*---------------------------------------------------Scene 9---------------------------------------------------*/

void scene_9(const MainCharacter& player){
    story_teller("冒險故事完結，讓我們一起回顧你的冒險過程！");
    ending_conclusion(player);
}

/*--------------------------------------------function implementation--------------------------------------------*/

// choose main character
void choose_character(MainCharacter& player) {
    int choice;
    cout << "請選擇你的主角職業：\n1. 巫師\n2. 劍士\n3. 學生\n";
    cin >> choice;
    cout << endl;

    switch (choice) {
        case 1:
            player = MainCharacter("巫師", 100, 20, "魔法");
            break;
        case 2:
            player = MainCharacter("劍士", 120, 15, "劍術");
            break;
        case 3:
            player = MainCharacter("一無所有的學生", 80, 10, "知識");
            break;
        default:
            cout << "無效選擇，默認為一無所有的學生。\n";
            player = MainCharacter("一無所有的學生", 80, 10, "知識");
    }

    cout << "你選擇了 " << player.name << " 作為你的職業。\n";
    cin.ignore();
}

// NPC interaction
void NPC_interaction_s2(const vector<string>& dialogues) {
    story_teller(dialogues[1]);

    // create NPC object
    NPC studentA(dialogues[2], dialogues[3]);
    NPC studentB(dialogues[4], dialogues[5]);
    NPC senior(dialogues[6], dialogues[7]);

    // NPC talk
    studentA.talk();
    studentB.talk();
    senior.talk();
    story_teller(dialogues[8]);
}

// NPC interaction
void NPC_interaction_s4() {
    story_teller("在新區域冒險，你遇到了一些新的NPC：");

    // create NPC object
    NPC studentA("學生A", "聽說Mr. He的攻擊模式是先進行物理攻擊，然後使用強力的魔法。");
    NPC senior("資深生", "這是一個能夠減免傷害的護身符，希望對你的冒險有幫助。");

    // NPC talk
    studentA.talk();
    senior.talk();

    story_teller("收集情報結束，你即將進入boss的房間。");
}

// NPC interaction
void NPC_interaction_s6() {
    story_teller("在最終區域冒險，你遇到了一些重要的NPC：");

    // create NPC object
    NPC studentB("學生B", "Mr. Kong的攻擊模式是隨機的，要小心應對。");
    NPC sisters("姐妹們", "這是一個能夠回復生命值的神秘藥劑，拿去吧。");

    // NPC talk
    studentB.talk();
    sisters.talk();

    story_teller("收集情報結束，你即將進入boss的房間。");
}

// battle setting
void battle(Enemy &boss, MainCharacter& player) {
    cout << "你進入了 " << boss.name << " 的房間，一場激烈的戰鬥即將展開！" << endl;
    cin.ignore();

    // Displays the initial state of enemies and players
    cout << "敵人信息：\n";
    boss.displayStats();
    clear_screen(); 
    cout << "你的信息:\n";
    player.displayStats();
    clear_screen(); 

    // battle loop
    while (boss.health > 0 && player.health > 0) {
        // player's turn
        boss.health -= player.attack;
        cout << "你對 " << boss.name << " 造成了 " << player.attack << " 點傷害。\n";
        cin.ignore();
        clear_screen(); 

        // check if enemy is defeated
        if (boss.health <= 0) {
            cout << boss.name << " 被你擊敗了！\n";
            cin.ignore();
            clear_screen(); 
            break;
        }

        // enemy's turn
        player.health -= boss.attack;
        cout << boss.name << " 對你造成了 " << boss.attack << " 點傷害。\n";
        cin.ignore();
        clear_screen(); 

        // check if player is dead
        if (player.health <= 0) {
            cout << "你被 " << boss.name << " 打敗了，遊戲結束。\n";
            cin.ignore();
            clear_screen(); 
            exit(0);
        }
    }

    story_teller("戰鬥結束。");
}

// ending scene
void ending_scene(const MainCharacter& player) {
    // Different endings depending on the player's life value
    if (player.health > 50) {
        cout << "你完成了冒險，身體力行展現了 " << player.profession << " 的強大力量，拯救了學院！";
        cin.ignore();
    } else {
        story_teller("儘管受傷，但你堅持到了最後，成功擊敗了最終敵人，為學院帶來了新的希望。");
    }

    // Gives different endings depending on the player's profession
    if (player.profession == "巫師") {
        story_teller("你以強大的魔法技能展現了巫師的力量。");
    } else if (player.profession == "劍士") {
        story_teller("你以高超的劍術技能戰勝了所有的敵人。");
    } else {
        story_teller("你以卓越的知識和靈活的操作，成功擊敗了所有敵人。");
    }
}

// ending scene2
void ending_conclusion(const MainCharacter& player) {
    story_teller("你在冒險過程中的一些亮點和成就：");

    // Displays information according to the player's profession
    if (player.profession == "巫師") {
        story_teller("作為一名巫師，你使用強大的魔法技能解決了眾多難題。");
    } else if (player.profession == "劍士") {
        story_teller("作為一名劍士，你的劍術技能在戰鬥中發揮了重要作用。");
    } else {
        story_teller("作為一名學生，你充分發揮了自己的知識和靈活性。");
    }

    // Displays a message based on the player's life value
    if (player.health > 50) {
        story_teller("你保持著良好的生命狀態，這讓你更有信心應對各種挑戰。");
    } else {
        story_teller("儘管受傷，你仍然堅持冒險，展現了極大的毅力。");
    }

    story_teller("感謝你參與這次冒險，希望你度過了一個精彩的冒險之旅！");
}
