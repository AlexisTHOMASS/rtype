/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Mouvement
*/

#include "Mouvement.hpp"
#include "Sprite.hpp"
#include "Motion.hpp"
#include "Input.hpp"
#include <chrono>
#include <iostream>

extern sf::Vector2f windowScale;

void Mouvement::init(Coordinator *coordinator)
{
    _coordinator = coordinator;
    _lastUpdate = std::chrono::high_resolution_clock::now();
    _timeFps = std::chrono::high_resolution_clock::now();
    _fps = 0;
}

void Mouvement::update()
{
    float timeEplasped = std::chrono::duration<float, std::chrono::seconds::period>(std::chrono::high_resolution_clock::now() - _lastUpdate).count();
    _lastUpdate = std::chrono::high_resolution_clock::now();

    _fps += 1;
    if (std::chrono::duration<float, std::chrono::seconds::period>(std::chrono::high_resolution_clock::now() - _timeFps).count() >= 1) {
        _timeFps = std::chrono::high_resolution_clock::now();
        _fps = 0;
    }

    for (auto const& entity : _entities) {
        auto &sprite = _coordinator->getComponent<Sprite>(entity);
        auto &motion = _coordinator->getComponent<Motion>(entity);
        Signature sig = _coordinator->getSignature(entity);
        

        sprite.sprite.move({motion.velocity.x * timeEplasped * windowScale.x, motion.velocity.y * timeEplasped * windowScale.y}); // Velocity in px/s
        if (motion.rotation != 0)
            sprite.sprite.rotate(motion.rotation * timeEplasped);

        motion.velocity.x += motion.acceleration.x * timeEplasped;
        motion.velocity.y += motion.acceleration.y * timeEplasped;

        if (motion.velocity.x < -500)
            return;
        if (motion.acceleration.x == 0 && sig[_coordinator->getComponentType<Input>()])
            motion.velocity.x /= 1 + 1.5 * timeEplasped;
        if (motion.acceleration.y == 0 && sig[_coordinator->getComponentType<Input>()])
            motion.velocity.y /= 1 + 1.5 * timeEplasped;

    }
}