/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Ship
*/

#ifndef SHIP_HPP_
#define SHIP_HPP_

struct Ship {
		// int id;
    bool isFreindly = true;
    float speed = 0;
    int xPos = 0;
    int hp = 0;
    float difficulty = 1;
    bool stop = false;
};

#endif /* !SHIP_HPP_ */
