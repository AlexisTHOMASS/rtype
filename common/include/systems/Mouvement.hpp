/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** PlayerMouvement
*/

#ifndef PLAYERMOUVEMENT_HPP_
#define PLAYERMOUVEMENT_HPP_

#include "System.hpp"
#include "Coordinator.hpp"
#include <chrono>

class Mouvement : public System {
    public:
        void init(Coordinator *coordinator);
        void update();

    protected:
    private:
        std::chrono::high_resolution_clock::time_point _lastUpdate;
        std::chrono::high_resolution_clock::time_point _timeFps;
        Coordinator *_coordinator;
        int _fps;
};

#endif /* !PLAYERMOUVEMENT_HPP_ */
