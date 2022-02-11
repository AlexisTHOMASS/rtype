/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Settingsys
*/

#include "Settingsys.hpp"
#include "Text.hpp"
#include "Input.hpp"
#include "iostream"

void Settingsys::init(Coordinator *coordinator)
{
    _coordinator = coordinator;
}

void Settingsys::update()
{
    for (auto const& entity : _entities) {
        auto &settings = _coordinator->getComponent<SettingsStr>(entity);
        auto &text = _coordinator->getComponent<Text>(entity);
        auto &input = _coordinator->getComponent<Input>(_coordinator->_player);
    switch (settings.modifSettings)
    {
    case ModifSettings::moveForward:
        if (text.key == 0)
            input.Up = sf::Keyboard::Z;
        else
            input.Up = sf::Keyboard::Key(text.key);
        break;
    case ModifSettings::moveDown:
        if (text.key == 0)
            input.Down = sf::Keyboard::S;
        else
            input.Down = sf::Keyboard::Key(text.key);
        break;
    case ModifSettings::moveLeft:
        if (text.key == 0)
            input.Left = sf::Keyboard::Q;
        else
            input.Left = sf::Keyboard::Key(text.key);
        break;
    case ModifSettings::moveRight:
        if (text.key == 0)
            input.Right = sf::Keyboard::D;
        else
            input.Right = sf::Keyboard::Key(text.key);
        break;
    default:
        break;
    }
    }
}