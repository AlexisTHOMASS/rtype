/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Settingsys
*/

#ifndef SETTINGSYS_HPP_
#define SETTINGSYS_HPP_

#include "System.hpp"
#include "Settings.hpp"
#include "Coordinator.hpp"

class Settingsys : public System {
    public:
        void init(Coordinator *coordinator);
        void update();
    protected:
    private:
        Coordinator *_coordinator;
};

#endif /* !SETTINGSYS_HPP_ */
