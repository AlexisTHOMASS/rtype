/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** PlayerMotion
*/

#ifndef PLAYERMOTION_HPP_
#define PLAYERMOTION_HPP_

#include "System.hpp"
#include "Coordinator.hpp"


class PlayerMotion : public System {
    public:
        void init(Coordinator *coordinator);
        void update();

    protected:
    private:
        Coordinator *_coordinator;
};

#endif /* !PLAYERMOTION_HPP_ */
