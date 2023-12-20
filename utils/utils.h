#ifndef UTILS_H
#define UTILS_H

#include "./character.h"

bool battle(Player& player, Enemy& enemy, sf::RenderWindow& window, sf::Text& textOb, sf::Event& event, sf::Texture& texture);
void final_ending(sf::RenderWindow& window, sf::Text& textOb);

#endif