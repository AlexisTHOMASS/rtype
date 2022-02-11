/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** MovingBar
*/

#include "MovingBar.hpp"
#include "Sprite.hpp"
#include "SFML/Graphics.hpp"
#include "Bar.hpp"
#include "Text.hpp"
#include <iostream>
#include <SFML/Audio.hpp>

extern sf::Vector2f windowScale;

void MovingBar::init(Coordinator *coordinator, sf::RenderWindow *window, sf::Sound *sound)
{
    _coordinator = coordinator;
    _window = window;
    _sound = sound;
}

void MovingBar::update()
{
    sf::Vector2i pos = sf::Mouse::getPosition(*_window);

    for (auto const& entity : _entities) {
        auto &sprite = _coordinator->getComponent<Sprite>(entity);
        auto &bar = _coordinator->getComponent<Bar>(entity);
        auto &text = _coordinator->getComponent<Text>(entity);
        sf::Vector2f coord = sprite.sprite.getPosition();
        sf::Vector2u size = sprite.tex.getSize();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pos.x >= coord.x && pos.x <= coord.x + size.x && pos.y >= coord.y && pos.y <= size.y + coord.y && _coordinator->phase[sprite.phase] && bar.ispressed == false) {
            bar.ispressed = true;
            bar.posXmouse = pos.x;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            bar.ispressed = false;
        else if (pos.x >= bar.x && pos.x <= bar.y && bar.ispressed == true) {
            if (pos.x >= bar.posXmouse)
                sprite.sprite.setPosition((coord.x + (pos.x - bar.posXmouse)) * windowScale.x, coord.y * windowScale.y);
            else
                sprite.sprite.setPosition((coord.x - (bar.posXmouse - pos.x)) * windowScale.x, coord.y * windowScale.y);
            bar.posXmouse = pos.x;
        }
        if (pos.x < bar.x && bar.ispressed == true)
            sprite.sprite.setPosition(bar.x * windowScale.x, coord.y * windowScale.y);
        else if (pos.x > bar.y && bar.ispressed == true)
            sprite.sprite.setPosition(bar.y * windowScale.x, coord.y * windowScale.y);
        float pourcent = bar.y - bar.x;
        float value = pourcent / (bar.max - bar.min);
        float sizeBar = coord.x - bar.x;
        float x = sizeBar / value + bar.min;
        text._text = std::to_string(int(x));
        if (bar.params == 0)
            _window->setFramerateLimit(int(x));
        if(bar.params == 1)
            _sound->setVolume(int(x));
    }
}