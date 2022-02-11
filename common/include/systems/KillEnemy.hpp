/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** KillEnemy
*/

#ifndef KILLENEMY_HPP_
#define KILLENEMY_HPP_

#include "System.hpp"
#include "Coordinator.hpp"

class KillEnemy : public System {
    public:
        void init(Coordinator *coordinator);
        std::vector<Entity> update();

    protected:
    private:
        Coordinator *_coordinator;
};

#endif /* !KILLENEMY_HPP_ */
