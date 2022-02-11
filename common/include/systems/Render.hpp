/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Render
*/

#ifndef RENDER_HPP_
#define RENDER_HPP_

#include "System.hpp"
#include "Coordinator.hpp"
#include "SFML/Graphics.hpp"

class Render : public System {
    public:
        void init(Coordinator *coordinator, sf::RenderWindow *window);
        void update();

    protected:
    private:
        sf::RenderWindow *_window;
        Coordinator *_coordinator;
};

#endif /* !RENDER_HPP_ */
