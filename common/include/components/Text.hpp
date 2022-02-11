/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "SFML/Graphics/Text.hpp"
#include "Phase.hpp"

struct Text {
    sf::Text _sftext;
    std::string _text; 
    Phase phase;
    int max;
    bool set = false;
    int key = 0;
    int id = 0;
};

#endif /* !TEXT_HPP_ */
