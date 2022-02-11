/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** parallaxe
*/

#include "Parallaxe.hpp"
#include "SFML/Graphics.hpp"
#include "Sprite.hpp"
#include "iostream"

void Parallaxe::init(Coordinator *coordinator, sf::RenderWindow *window)
{
    _coordinator = coordinator;
    _window = window;
    _clock = std::chrono::high_resolution_clock::now();
}

void Parallaxe::update()
{
    if (std::chrono::duration<float, std::chrono::milliseconds::period>(std::chrono::high_resolution_clock::now() - _clock).count() < 20)
        return;
    for (auto const& entity : _entities) {
        auto &sprite = _coordinator->getComponent<Sprite>(entity);
        sf::Vector2f coord = sprite.sprite.getPosition();
        if (coord.x == -1920)
            sprite.sprite.setPosition(-3840, coord.y);
        else if (coord.x == -5760)
            sprite.sprite.setPosition(0, coord.y);
        else 
            sprite.sprite.setPosition(coord.x -1, coord.y);
    }
    _clock = std::chrono::high_resolution_clock::now();
}