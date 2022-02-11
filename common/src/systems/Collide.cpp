/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Collide
*/

#include "Collide.hpp"
#include <iostream>
#include "Ship.hpp"
#include "BulletComp.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void Collide::init(Coordinator *coordinator)
{
    _coordinator = coordinator;
}

void Collide::update(std::set<Entity> mouvementEntities)
{
     for (auto const &entity : _entities) {
        Signature sig = _coordinator->getSignature(entity);
        if (!sig[_coordinator->getComponentType<Ship>()])
            continue;
        auto &ship = _coordinator->getComponent<Ship>(entity);
        auto &sprite_player = _coordinator->getComponent<Sprite>(entity);
        auto player_global_bounds = sprite_player.sprite.getGlobalBounds();
        for (auto const &entityd : mouvementEntities) {
            Signature sigd = _coordinator->getSignature(entityd);
            if (!sigd[_coordinator->getComponentType<Bullet_Comp>()])
                continue;
            auto &bullet = _coordinator->getComponent<Bullet_Comp>(entityd);
            if (ship.isFreindly == bullet.isFrendly)
                continue;
            auto &bullet_sprite = _coordinator->getComponent<Sprite>(entityd);
            if (bullet_sprite.sprite.getGlobalBounds().intersects(player_global_bounds)) {
                if (ship.isFreindly)
                    ship.hp -= 1;
                else
                    ship.hp -= 5;
                _coordinator->destroyEntity(entityd);
            }
        }
    }
}