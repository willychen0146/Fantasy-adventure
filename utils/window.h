#ifndef WINDOW_H
#define WINDOW_H

#include <codecvt>
#include <locale>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <string>

extern std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
extern sf::RenderWindow window;
extern sf::Font font;
extern sf::Text textOb;
extern sf::Event event;
const unsigned int maxCharsPerLine = 90;
const int STRING_POSITION = 780;

class FallingText{
public:
    FallingText(const std::wstring& text, const sf::Font& font, unsigned int characterSize, float fallSpeed, float startDelay);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    float getYPosition();
private:
    sf::Text textObject;
    std::wstring text;
    const sf::Font& font;
    unsigned int characterSize;
    float fallSpeed;
    float startDelay;
    static const int windowWidth;  // Adjust according to your window size
    static const int windowHeight; // Adjust according to your window size
};

void font_setting(sf::Font& font, sf::Text& textOb);

void windows_event(sf::RenderWindow& window, sf::Event& event);

void draw_black_box(sf::RenderWindow& window, sf::RectangleShape& blackRect);

void text_show(sf::RenderWindow& window, sf::Text& textOb, std::wstring& wline);

void show_wstring(std::string text, sf::RenderWindow& window, sf::Text& textOb);

void final_ending(sf::RenderWindow& window, sf::Text& textOb, std::ifstream& inputFile, sf::Texture& texture, sf::Texture& pdogs);

#endif