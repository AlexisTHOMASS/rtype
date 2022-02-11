/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** GestButton
*/

#ifndef GESTBUTTON_HPP_
#define GESTBUTTON_HPP_

#include "System.hpp"
#include "Coordinator.hpp"
#include "Clickable.hpp"

class GestButton : public System{
    public:
        void init(Coordinator *coordinator, sf::RenderWindow *window);
        void update();
    protected:
    private:
        Coordinator *_coordinator;
        sf::RenderWindow *_window;
        bool _isClicked;
        Clickable _button;
        bool _alwaysClied;
};

void playFun(Coordinator *coord);
void exitFun(Coordinator *coord);
void settingsFun(Coordinator *coord);
void chooseGame(Coordinator *coord);
void joinGame(Coordinator *coord);
void createGame(Coordinator *coord);
void returnHomeFromSettings(Coordinator *coord);
void returnHomeFromChooseGame(Coordinator *coord);
void returnHomeFromJoinGame(Coordinator *coord);
void gameFromJoin(Coordinator *coord);
void returnHomeFromCreateGame(Coordinator *coord);
void gameFromCreate(Coordinator *coord);
void returnHomeFromConnect(Coordinator *coord);
void connect(Coordinator *coord);
void returnHomeFromScore(Coordinator *coord);
void joinToJoinId(Coordinator *coord);
void goConnection(Coordinator *coord);
void createToGameId(Coordinator *coord);
void createGame(Coordinator *coord);
#endif /* !GESTBUTTON_HPP_ */
