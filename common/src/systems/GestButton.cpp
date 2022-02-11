/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** GestButton
*/

#include "Clickable.hpp"
#include "GestButton.hpp"
#include "Sprite.hpp"
#include "SFML/Graphics.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

extern sf::Vector2f windowScale;

void GestButton::init(Coordinator *coordinator, sf::RenderWindow *window)
{
    _window = window;
    _coordinator = coordinator;
    _isClicked = false;
}

void GestButton::update()
{
    if (_isClicked == true and !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (_button.funcButton != nullptr)
            _button.funcButton(_coordinator);
        _isClicked = false;
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return;
    }
    sf::Vector2i pos = sf::Mouse::getPosition(*_window);	
    for (auto const& entity : _entities) {
        Signature sig = _coordinator->getSignature(entity);
        if (!sig[_coordinator->getComponentType<Sprite>()] || !sig[_coordinator->getComponentType<Clickable>()])
            continue;
        auto &sprite = _coordinator->getComponent<Sprite>(entity);
        auto &button = _coordinator->getComponent<Clickable>(entity);
        button._alwaysClicked = false;
        sf::Color color = sf::Color::White;
        sprite.sprite.setColor(color);
        sf::Vector2f coord = sprite.sprite.getPosition();
        sf::Vector2u size = sprite.tex.getSize();
        if (pos.x >= coord.x && pos.x <= coord.x + size.x && pos.y >= coord.y && pos.y <= size.y + coord.y && _coordinator->phase[sprite.phase]) {
            _isClicked = true;
            _button = button;
            button._alwaysClicked = true;
            sf::Color color(255, 0, 0);
            sprite.sprite.setColor(color);
        }
    }
}

void exitFun(Coordinator *coord) 
{
    coord->phase.set(Phase::Exit, 1);
}

void playFun(Coordinator *coord) 
{
    coord->phase.set(Phase::ChooseGame, 1);
    coord->phase.set(Phase::MainMenu, 0);
}

void settingsFun(Coordinator *coord) 
{
    coord->phase.set(Phase::Settings, 1);
    coord->phase.set(Phase::MainMenu, 0);
}

void chooseGame(Coordinator *coord)
{
    coord->phase.set(Phase::MainMenu, 0);
    coord->phase.set(Phase::ChooseGame, 1);
}

void joinGame(Coordinator *coord) 
{
    coord->phase.set(Phase::JoinGame, 1);
    coord->phase.set(Phase::ChooseGame, 0);
}

void returnHomeFromSettings(Coordinator *coord)
{
    coord->phase.set(Phase::MainMenu, 1);
    coord->phase.set(Phase::Settings, 0);
}

void returnHomeFromChooseGame(Coordinator *coord)
{
    coord->phase.set(Phase::MainMenu, 1);
    coord->phase.set(Phase::ChooseGame, 0);
}

void returnHomeFromJoinGame(Coordinator *coord)
{
    coord->phase.set(Phase::ChooseGame, 1);
    coord->phase.set(Phase::JoinGame, 0);
}

void gameFromJoin(Coordinator *coord)
{
    coord->phase.set(Phase::Play, 1);
    coord->phase.set(Phase::JoinGame, 0);
}

void connect(Coordinator *coord)
{
    coord->phase.set(Phase::MainMenu, 0);
    coord->phase.set(Phase::Connect, 1);
}

void returnHomeFromConnect(Coordinator *coord)
{
    coord->phase.set(Phase::MainMenu, 1);
    coord->phase.set(Phase::Connect, 0);
}

void returnHomeFromScore(Coordinator *coord)
{
    coord->phase.set(Phase::MainMenu, 1);
    coord->phase.set(Phase::Score, 0);
}

void joinToJoinId(Coordinator *coord)
{
    coord->phase.set(Phase::JoinGame, 0);
    coord->phase.set(Phase::JoinGameId, 1);
}

void goConnection(Coordinator *coord)
{
    coord->phase.set(Phase::Connect, 0);
    coord->phase.set(Phase::Connection, 1);
}

void returnHomeFromCreateGame(Coordinator *coord)
{
    coord->phase.set(Phase::CreateGame, 0);
    coord->phase.set(Phase::ChooseGame, 1);
}

void createToGameId(Coordinator *coord)
{
    coord->phase.set(Phase::CreateGameId, 1);
    coord->phase.set(Phase::CreateGame, 0);
}

void createGame(Coordinator *coord)
{
    coord->phase.set(Phase::ChooseGame, 0);
    coord->phase.set(Phase::CreateGame, 1);
}