/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "SFML/Window/Keyboard.hpp"

struct Input {
    sf::Keyboard::Key Up = sf::Keyboard::Up;
    sf::Keyboard::Key Down = sf::Keyboard::Down;
    sf::Keyboard::Key Right = sf::Keyboard::Right;
    sf::Keyboard::Key Left = sf::Keyboard::Left;

    static bool keyPressed(sf::Keyboard::Key key)
    {
        return (sf::Keyboard::isKeyPressed(key));
    }
};

#endif /* !INPUT_HPP_ */
