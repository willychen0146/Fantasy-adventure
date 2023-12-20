#include "./utils/game.h"

using namespace std;

int main() {
    font_setting(font, textOb);

    // Create music objects array
    sf::Music music[10];
    string musicPaths[] = {
        "./src/ost/The-Prelude.mp3", // 1
        "./src/ost/Chasing-the-Black-Caped-Man.mp3", // 2
        "./src/ost/Memoria.mp3", // 3
        "./src/ost/Chasing-the-Black-Caped-Man.mp3", // 4 with battle
        "./src/ost/People-of-the-Far-North.mp3", // 5
        "./src/ost/Terra.mp3", // 6
        "./src/ost/Chasing-the-Black-Caped-Man.mp3", // 7 with battle
        "./src/ost/telarz.mp3", // 8
        "./src/ost/Chasing-the-Black-Caped-Man.mp3", // 9 with battle
        "./src/ost/Yomawari.mp3", // 10
    };

    // Load music
    for (int i = 0; i < 10; ++i) {
        if (!music[i].openFromFile(musicPaths[i])) {
            cerr << "Failed to load music " << i + 1 << endl;
        }
    }

    // Create battle music objects array
    sf::Music battleMusic[5];
    string musicPaths2[] = {
        "./src/ost/Fighting.mp3", // normal battle
        "./src/ost/Decisive-Battle.mp3", // boss 1 
        "./src/ost/J-E-N-O-V-A.mp3", // boss 2
        "./src/ost/One-Winged Angel - Rebirth.mp3", // boss 3
        "./src/ost/Rose-of-may.mp3" // ending
    };

    // Load battle music
    for (int i = 0; i < 5; ++i) {
        if (!battleMusic[i].openFromFile(musicPaths2[i])) {
            cerr << "Failed to load music " << i + 1 << endl;
        }
    }

    // Create background image array
    sf::Texture texture[10];
    string imagePaths[] = {
        "./src/image/chapter1.jpg", // 1
        "./src/image/chapter2.jpg", // 2
        "./src/image/chapter3.jpg", // 3
        "./src/image/chapter4.jpg", // 4 with battle
        "./src/image/chapter5.jpg", // 5
        "./src/image/chapter6.jpg", // 6
        "./src/image/chapter7.jpg", // 7 with battle
        "./src/image/chapter8.jpg", // 8
        "./src/image/chapter9.jpg", // 9 with battle
        "./src/image/chapter10.jpg", // 10
    };

    // Load image
    for (int i = 0; i < 10; ++i) {
        if (!texture[i].loadFromFile(imagePaths[i])) {
            cerr << "Failed to load image " << i + 1 << endl;
        }
    }

    // Create battle background image array
    sf::Texture battleTexture[5];
    string imagePaths2[] = {
        "./src/image/battle.jpg", // normal battle
        "./src/image/boss1.jpg", // boss 1 
        "./src/image/boss2.jpg", // boss 2
        "./src/image/boss3.jpg", // boss 3
        "./src/image/ending.jpg" // ending
    };

    // Load battle image
    for (int i = 0; i < 5; ++i) {
        if (!battleTexture[i].loadFromFile(imagePaths2[i])) {
            cerr << "Failed to load image " << i + 1 << endl;
        }
    }

    Game game;
    
    ifstream chapter1("./src/txt/chapter1.txt");
    ifstream chapter2("./src/txt/chapter2.txt");
    ifstream chapter3("./src/txt/chapter3.txt");
    ifstream chapter4("./src/txt/chapter4.txt");
    ifstream chapter5("./src/txt/chapter5.txt");
    ifstream chapter6("./src/txt/chapter6.txt");
    ifstream chapter7("./src/txt/chapter7.txt");
    ifstream chapter8("./src/txt/chapter8.txt");
    ifstream chapter9("./src/txt/chapter9.txt");
    ifstream chapter10("./src/txt/chapter10.txt");


    game.addChapter(chapter1);
    game.addChapter(chapter2);
    game.addChapter(chapter3);
    game.addChapter(chapter4);
    game.addChapter(chapter5);
    game.addChapter(chapter6);
    game.addChapter(chapter7);
    game.addChapter(chapter8);
    game.addChapter(chapter9);
    game.addChapter(chapter10);

    
    while (window.isOpen()) {
        game.startTheStory(window, textOb, music, battleMusic, texture, battleTexture, event);
        break;
    }
    
    // final ending
    ifstream ending("./src/txt/ending.txt");
    sf::Texture pdogs;
    if (!pdogs.loadFromFile("./src/image/pdogs.png")) {
        cerr << "Failed to load image " << endl;
    }
    battleMusic[4].play();
    battleMusic[4].setLoop(true);
    final_ending(window, textOb, ending, battleTexture[4], pdogs);
    battleMusic[4].stop();    
       
    return 0;
}