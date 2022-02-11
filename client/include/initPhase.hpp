/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** initPhase
*/

#ifndef INITPHASE_HPP_
#define INITPHASE_HPP_

#include <SFML/Graphics.hpp>
#include "Coordinator.hpp"

enum PlayerList {
    Blue1 = 1,
    Green1,
    Red1,
    Yellow1,
    Blue2,
    Green2,
    Red2,
    Yellow2,
    Blue3,
    Green3,
    Red3,
    Yellow3,
    Blue4,
    Green4,
    Red4,
    Yellow4,
};

static const std::map<PlayerList, std::string> allPlayerSprite = {
    {Blue1, "data/sprite/player/SpaceShipLvl1Blue.png"},
    {Green1, "data/sprite/player/SpaceShipLvl1Green.png"},
    {Red1, "data/sprite/player/SpaceShipLvl1Red.png"},
    {Yellow1, "data/sprite/player/SpaceShipLvl1Yellow.png"},
    {Blue2, "data/sprite/player/SpaceShipLvl2Blue.png"},
    {Green2, "data/sprite/player/SpaceShipLvl2Green.png"},
    {Red2, "data/sprite/player/SpaceShipLvl2Red.png"},
    {Yellow2, "data/sprite/player/SpaceShipLvl2Yellow.png"},
    {Blue3, "data/sprite/player/SpaceShipLvl3Blue.png"},
    {Green3, "data/sprite/player/SpaceShipLvl3Green.png"},
    {Red3, "data/sprite/player/SpaceShipLvl3Red.png"},
    {Yellow3, "data/sprite/player/SpaceShipLvl3Yellow.png"},
    {Blue4, "data/sprite/player/SpaceShipLvl4Blue.png"},
    {Green4, "data/sprite/player/SpaceShipLvl4Green.png"},
    {Red4, "data/sprite/player/SpaceShipLvl4Red.png"},
    {Yellow4, "data/sprite/player/SpaceShipLvl4Yellow.png"}
};

void initPlay(Coordinator &coordinator, std::pair<uint16_t, Entity> &playerId);
void initMainMenu(Coordinator &coordinator);
void initSettings(Coordinator &coordinator);
void initChooseGame(Coordinator &coordinator);
void initJoinGame(Coordinator &coordinator);
void initConnect(Coordinator &coordinator);
void initLobby(Coordinator &coordinator);
void initScore(Coordinator &Coordinator);
void initCreateGame(Coordinator &coordinator);

#endif /* !INITPHASE_HPP_ */
