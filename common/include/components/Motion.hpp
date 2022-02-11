/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Motion
*/

#ifndef MOTION_HPP_
#define MOTION_HPP_

#include <SFML/System/Vector2.hpp>

struct Motion {
    sf::Vector2f velocity; // Velocity in px/s
    sf::Vector2f acceleration;
    float rotation = 0;
};

#endif /* !MOTION_HPP_ */
