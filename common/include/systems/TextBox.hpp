/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** TextBox
*/

#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_

#include "System.hpp"
#include "Coordinator.hpp"
#include "SFML/Graphics.hpp"
#include <chrono>

class TextBox : public System{
    public:
        void init(Coordinator *coordinator, sf::RenderWindow *window);
        void update();
        std::string get(int id);
    protected:
    private:
        Coordinator *_coordinator;
        sf::RenderWindow *_window;
        bool _keypressed;

};

#endif /* !TEXTBOX_HPP_ */
