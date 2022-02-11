/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** EntityData
*/

#include "EntityData.hpp"
#include "MergeData.hpp"
#include <iostream>
#include "ServerProtocol.hpp"
#include "Phase.hpp"
#include "Text.hpp"

EntityData::EntityData()
{
}

EntityData::~EntityData()
{
}

void EntityData::loadData(char *data, Coordinator &coordinator)
{
    int protocol = mergeData::getProtocol(data);

    if (protocol == ServerGamePlayProtool::PLAYER_POSITION) {
        this->playerData.push_back(mergeData::unPack<playerObj>(data).second);
    } else if (protocol == ServerGamePlayProtool::ENEMY_POSITION) {
        this->enemyData.push_back(mergeData::unPack<enemyObj>(data).second);
    } else if (protocol == ServerGamePlayProtool::BULLET_ENEMY) {
        this->bulletData.push_back(mergeData::unPack<bulletObj>(data).second);
    } else if (protocol == ServerGamePlayProtool::BULLET_PLAYER) {
        this->bulletDataFriendly.push_back(mergeData::unPack<bulletObj>(data).second);
    } else if (protocol == ServerGamePlayProtool::LAUNCH_GAME) {
        coordinator.phase.set(Phase::Lobby, false);
        coordinator.phase.set(Phase::Play, true);
    } else if (protocol == ServerGamePlayProtool::END_GAME) {
        coordinator.phase.set(Phase::Play, false);
        coordinator.phase.set(Phase::LobbyAndPlay, false);
        coordinator.phase.set(Phase::Score, true);
        int score = mergeData::unPack<int>(data).second;
        auto &text = coordinator.getComponent<Text>(coordinator._score.first);
        text._text = "Score: " + std::to_string(score);
        text._sftext.setString("Score: " + std::to_string(score));
        coordinator.destroyEntity(coordinator._player);
    }
}