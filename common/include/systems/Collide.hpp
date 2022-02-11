/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Collide
*/

#ifndef COLLIDE_HPP_
#define COLLIDE_HPP_

#include "Coordinator.hpp"
#include "System.hpp"
#include "Sprite.hpp"

class Collide : public System {
    public:
        void init(Coordinator *coordinator);
        void update(std::set<Entity>);
    private:
        Coordinator *_coordinator;
};

#endif /* !COLLIDE_HPP_ */
