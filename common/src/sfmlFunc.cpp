/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** sfmlFunc
*/

#include "sfmlFunc.hpp"

Sprite createSprite(std::string file, Phase phase)
{
    sf::Texture tex;
    tex.loadFromFile(file);
    
    Sprite sprite = {sf::Sprite(), tex, phase, file};

    return (sprite);
}