/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** CreateEnemy
*/

#ifndef CREATEENEMY_HPP_
#define CREATEENEMY_HPP_

#include "Coordinator.hpp"
#include "System.hpp"
#include "Waves.hpp"
#include <chrono>
#include <vector>

class CreateEnemy : public System {
    public:
        void init(Coordinator *coordinator);
        std::vector<Entity> update();
        void __levelInfinite(std::vector<Entity> &newEnemy);

    protected:
    private:
        Coordinator *_coordinator;
        std::chrono::high_resolution_clock::time_point _timeWave;
        Level _level;
        int _wave;
        float _infiniteDifficulty;
        float _infiniteSpawnSpeed;
};

#endif /* !CREATEENEMY_HPP_ */
