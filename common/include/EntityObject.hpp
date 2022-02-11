/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** EntityObject
*/

#ifndef ENTITYOBJECT_HPP_
#define ENTITYOBJECT_HPP_

#include <SFML/Graphics.hpp> 
#include "Motion.hpp"

struct playerObj {
    uint16_t id;
    sf::Vector2f pos;
    char texture[100];
};

struct enemyObj {
	int id;
	Motion motion;
	sf::Vector2f pos;
	char texture[100];
};

struct bulletObj {
	Motion motion;
	sf::Vector2f pos;
	char texture[100];
};

#endif /* !ENTITYOBJECT_HPP_ */
