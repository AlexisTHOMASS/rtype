/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include "Phase.hpp"

struct Sprite {
    sf::Sprite sprite;
    sf::Texture tex;
    Phase phase;
    std::string path;
    int spritId = 0;
    bool set = false;
};

#endif /* !PLAYER_HPP_ */
