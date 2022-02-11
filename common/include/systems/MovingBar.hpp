/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** MovingBar
*/

#ifndef MOVINGBAR_HPP_
#define MOVINGBAR_HPP_

#include "System.hpp"
#include "Coordinator.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class MovingBar : public System{
    public:
        void init(Coordinator *coordinator, sf::RenderWindow *window, sf::Sound *sound);
        void update();
    protected:
    private:
        Coordinator *_coordinator;
        sf::RenderWindow *_window;
        sf::Sound *_sound;
};

#endif /* !MOVINGBAR_HPP_ */
