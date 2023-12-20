#include "./window.h"
using namespace std;

const int windowX = 1920;
const int windowY = 1080;
const int FallingText::windowWidth = 1920;
const int FallingText::windowHeight = 1080;

std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
// Create the window
sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Fantasy Adventure", sf::Style::Fullscreen, sf::ContextSettings(0, 0, 0));
// Text object for the lower half
sf::Font font;
sf::Text textOb;
sf::Event event;

FallingText::FallingText(const std::wstring& text, const sf::Font& font, unsigned int characterSize, float fallSpeed, float startDelay)
    : text(text), font(font), characterSize(characterSize), fallSpeed(fallSpeed), startDelay(startDelay){
    textObject.setFont(font);
    textObject.setCharacterSize(characterSize);
    textObject.setString(text);
    textObject.setFillColor(sf::Color::White);

    // Initialize the position at the center of the window
    float xPosition = (windowWidth - textObject.getGlobalBounds().width) / 2.0f;
    textObject.setPosition(xPosition, -100);
}

void FallingText::update(float deltaTime){
    if (startDelay > 0.0f){
        startDelay -= deltaTime;
        return;
    }
    sf::Vector2f position = textObject.getPosition();
    position.y += fallSpeed * deltaTime;
    textObject.setPosition(position);
}

void FallingText::draw(sf::RenderWindow& window){
    window.draw(textObject);
}

float FallingText::getYPosition(){
    return textObject.getPosition().y;
}

void font_setting(sf::Font& font, sf::Text& textOb) {
    if (!font.loadFromFile("./src/font/Arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    textOb.setFont(font);
    textOb.setCharacterSize(20);
    textOb.setFillColor(sf::Color::White);
}

void windows_event(sf::RenderWindow& window, sf::Event& event) {
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            break;
        } else if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void draw_black_box(sf::RenderWindow& window, sf::RectangleShape& blackRect) {
    blackRect.setPosition(0, STRING_POSITION);
    blackRect.setFillColor(sf::Color::Black);
    window.draw(blackRect);
}

void text_show(sf::RenderWindow& window, sf::Text& textOb, std::wstring& wline) {
    // Process the text to limit the length
    for (size_t i = 0; i < wline.length(); i += maxCharsPerLine) {
        std::wstring subLine = wline.substr(i, maxCharsPerLine);
        
        // Output the current substring
        textOb.setString(subLine);
        textOb.setPosition(10, STRING_POSITION + static_cast<int>(i / maxCharsPerLine) * 25);  // Adjust the position based on your layout
        window.draw(textOb);
    }
}

void show_wstring(std::string text, sf::RenderWindow& window, sf::Text& textOb) {
    // string to wstring and display on window
    std::wstring wline = converter.from_bytes(text);
    text_show(window, textOb, wline);
    window.display();
}

void final_ending(sf::RenderWindow& window, sf::Text& textOb, std::ifstream& inputFile, sf::Texture& texture, sf::Texture& pdogs){
    const unsigned int defaultCharacterSize = 50;
    const unsigned int firstLastLineCharacterSize = 70;
    const float fallSpeed = 80.0f;

    sf::Sprite sprite(texture);
    window.draw(sprite);

    vector<FallingText> fallingTexts;

    float verticalSpacing = 0.1f;
    bool isFirstLine = true;
    string line;
    while (getline(inputFile, line))
    {
        wstring wline = converter.from_bytes(line);

        // Use different character size for the first and last lines
        unsigned int currentCharacterSize = isFirstLine || inputFile.eof() ? firstLastLineCharacterSize : defaultCharacterSize;

        fallingTexts.emplace_back(wline, font, currentCharacterSize, fallSpeed, verticalSpacing);
        if (isFirstLine) {
            verticalSpacing+=2.0f;
        }
        verticalSpacing+=1.5f;

        if (isFirstLine) {
            isFirstLine = false;
        }
    }

    inputFile.close();

    sf::Clock clock;

    // Load falling image texture
    sf::Sprite fallingImage(pdogs);
    fallingImage.setPosition(((windowX / 2.0f) - 500.0f), -200.0f);  // Set initial position above the window

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear();
        sf::Sprite sprite(texture);
        window.draw(sprite);
        // Draw the falling image
        fallingImage.move(0.0f, fallSpeed * deltaTime);
        window.draw(fallingImage);

        bool allTextOffScreen = true;  // Flag to check if all text is off the screen

        for (auto& fallingText : fallingTexts)
        {
            fallingText.update(deltaTime);
            fallingText.draw(window);
            // Check if any text is still on the screen
            if (fallingText.getYPosition() < 1080.0)
            {
                allTextOffScreen = false;
            }
        }

        window.display();

        // If all text is off the screen, close the window
        if (allTextOffScreen)
        {
            window.close();
        }
    }
}