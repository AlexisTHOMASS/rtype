/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** TextBox
*/

#include "TextBox.hpp"
#include "iostream"
#include "Sprite.hpp"
#include "Clickable.hpp"
#include "Text.hpp"

void TextBox::init(Coordinator *coordinator, sf::RenderWindow *window)
{
    _coordinator = coordinator;
    _window = window;
    _keypressed = false;
}

void TextBox::update()
{
    sf::Event event;
    while (_window->pollEvent(event)) {
        for (auto const& entity : _entities) {
        auto &button = _coordinator->getComponent<Clickable>(entity);
        auto &text = _coordinator->getComponent<Text>(entity);
        if (button._alwaysClicked == true) {
            if (event.key.code == sf::Keyboard::BackSpace)
                text._text = text._text.substr(0, text._text.size() - 1), _keypressed = true;
            if (event.key.code == sf::Keyboard::Left) {
                text._text = "LEFT ARROW";
                text.key = event.key.code;
            }
            if (event.key.code == sf::Keyboard::Right) {
                text._text = "RIGHT ARROW";
                text.key = event.key.code;
            }
            if (event.key.code == sf::Keyboard::Up) {
                text._text = "UP ARROW";
                text.key = event.key.code;
            } 
            if (event.key.code == sf::Keyboard::Down) {
                text._text = "DOWN ARROW";
                text.key = event.key.code;
            }
            else if (event.type == sf::Event::TextEntered) {
                text.key = event.key.code - 97;
                if (event.text.unicode < 128 && event.key.code != 8) {
                    if (text.max == 1)
                        text._text = static_cast<char>(event.text.unicode);
                    else if (text.max != 0 && text._text.size() <= (std::size_t)text.max)
                        text._text = text._text + static_cast<char>(event.text.unicode);
                }
            }
        }
        }
    }
}

std::string TextBox::get(int id)
{
    for (auto const &entity : _entities) {
        Signature sig = _coordinator->getSignature(entity);
        if (!sig[_coordinator->getComponentType<Text>()])
            continue;
        auto &text =  _coordinator->getComponent<Text>(entity);
        if (text.id == id)
            return text._text;
    }
    return "";
}