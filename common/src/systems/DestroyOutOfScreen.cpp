/*
** EPITECH PROJECT, 2021
** rType
** File description:
** DestroyOutOfScreen
*/

#include "DestroyOutOfScreen.hpp"
#include "Sprite.hpp"
#include <iostream>

void DestroyOutOfScreen::init(Coordinator *coordinator, sf::Vector2u windowSize)
{
    _coordinator = coordinator;
    _windowSize = windowSize;
}

void DestroyOutOfScreen::update()
{
    for (auto const &entity : _entities) {
        auto &sprite = _coordinator->getComponent<Sprite>(entity);
        sf::Vector2f pos = sprite.sprite.getPosition();
        sf::Vector2u size = sprite.tex.getSize();

        if (pos.x > _windowSize.x || pos.x + size.x < 0) {
            _toDestroy.push_back(entity);
        }
    }

    if (_toDestroy.size()) {
        for (auto it : _toDestroy)
            _coordinator->destroyEntity(it);
        _toDestroy.clear();
    }
}