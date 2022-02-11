/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** PrintText
*/

#include "PrintText.hpp"
#include "Text.hpp"
#include "iostream"

void PrintText::init(Coordinator *coordinator, sf::RenderWindow *window)
{
    _coordinator = coordinator;
    _window = window;
    _font.loadFromFile("data/font/arial.ttf");
}

void PrintText::update()
{
    for (auto const& entity : _entities) {
        auto &text = _coordinator->getComponent<Text>(entity);
        if (_coordinator->phase[text.phase]) {
            if (!text.set) {
                text._sftext.setString(text._text);
                text.set = true;
            }
            text._sftext.setFont(_font);
            text._sftext.setString(text._text);
            _window->draw(text._sftext);
        }
    }
}
