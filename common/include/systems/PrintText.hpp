/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** PrintText
*/

#ifndef PRINTTEXT_HPP_
#define PRINTTEXT_HPP_

#include "System.hpp"
#include "Coordinator.hpp"
#include "SFML/Graphics.hpp"

class PrintText : public System{
    public:
        void init(Coordinator *coordinator, sf::RenderWindow *window);
        void update();
    protected:
    private:
        Coordinator *_coordinator;
        sf::RenderWindow *_window;
        sf::Font _font;
};

#endif /* !PRINTTEXT_HPP_ */
