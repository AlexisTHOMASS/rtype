/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Render
*/

#include "Render.hpp"
#include "Sprite.hpp"

extern sf::Vector2f windowScale;

void Render::init(Coordinator *coordinator, sf::RenderWindow *window)
{
    _coordinator = coordinator;
    _window = window;
}

void Render::update()
{
    for (auto const& entity : _entities) {
        auto &sprite = _coordinator->getComponent<Sprite>(entity);

        if (_coordinator->phase[sprite.phase]) {
            if (!sprite.set) {
                sprite.sprite.setTexture(sprite.tex);
                sprite.sprite.setScale(windowScale);
                sprite.set = true;
            }
            _window->draw(sprite.sprite);
        }
    }
}