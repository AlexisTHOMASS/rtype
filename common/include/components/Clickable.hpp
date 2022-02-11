/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Clickable
*/

#ifndef CLICKABLE_HPP_
#define CLICKABLE_HPP_

#include <SFML/Graphics.hpp>
#include "Phase.hpp"
#include "Coordinator.hpp"

struct Clickable {
    void (*funcButton)(Coordinator *cord);
    bool _alwaysClicked = false;
};

#endif /* !CLICKABLE_HPP_ */
