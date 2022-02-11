/*
** EPITECH PROJECT, 2021
** rType
** File description:
** DestroyOutOfScreen
*/

#ifndef DESTROYOUTOFSCREEN_HPP_
#define DESTROYOUTOFSCREEN_HPP_

#include "System.hpp"
#include "Coordinator.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class DestroyOutOfScreen  : public System {
    public:
        void init(Coordinator *coordinator, sf::Vector2u windowSize);
        void update();

    private:
        Coordinator *_coordinator;
        sf::Vector2u _windowSize;
        std::vector<Entity> _toDestroy;
};

#endif /* !DESTROYOUTOFSCREEN_HPP_ */
