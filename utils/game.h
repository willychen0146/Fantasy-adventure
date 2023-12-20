#ifndef GAME_H
#define GAME_H

#include "./utils.h"

const int chapterMaxSize = 20;

class Game {
private:
    Player player;
    int chapterCnt;
    std::ifstream* chapters[chapterMaxSize];
    bool gameOver;

public:
    Game();
    ~Game();
    void addChapter(std::ifstream& storyTxt);
    void startTheStory(sf::RenderWindow& window, sf::Text& textOb, sf::Music* music, sf::Music* battleMusic, sf::Texture* texture, sf::Texture* battleTexture, sf::Event& event);
    bool story_teller(std::ifstream& storyTxt, sf::RenderWindow& window, sf::Text& textOb, sf::Music& music, sf::Music* battleMusic, sf::Texture& texture, sf::Texture* battleTexture, sf::Event& event);
    void setPlayer(Player& chosenPlayer);
};

#endif