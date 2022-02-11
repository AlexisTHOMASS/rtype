/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** EnemyMotion
*/

#ifndef ENEMYMOTION_HPP_
#define ENEMYMOTION_HPP_

#include "Coordinator.hpp"
#include "System.hpp"
#include <vector>

class EnemyMotion : public System {
    public:
        void init(Coordinator *coordinator);
        std::vector<Entity> update();

    protected:
    private:
        Coordinator *_coordinator;
};

#endif /* !ENEMYMOTION_HPP_ */
