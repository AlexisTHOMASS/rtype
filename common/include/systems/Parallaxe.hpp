/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** parallaxe
*/

#ifndef PARALLAXE_HPP_
#define PARALLAXE_HPP_

#include "System.hpp"
#include "Coordinator.hpp"
#include "SFML/Graphics.hpp"
#include <chrono>

class Parallaxe : public System{
    public:
        void init(Coordinator *coordinator, sf::RenderWindow *window);
        void update();
    protected:
    private:
        Coordinator *_coordinator;
        sf::RenderWindow *_window;
        std::chrono::high_resolution_clock::time_point _clock;
};

#endif /* !PARALLAXE_HPP_ */
