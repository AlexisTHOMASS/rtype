/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** EntityData
*/

#ifndef ENTITYDATA_HPP_
#define ENTITYDATA_HPP_

#include "EntityObject.hpp"
#include "Coordinator.hpp"
#include <vector>

class EntityData {
    public:
        EntityData();
        ~EntityData();
        void loadData(char *data, Coordinator &coordinator);

        std::vector<int> intData;
        std::vector<playerObj> playerData;
        std::vector<enemyObj> enemyData;
        std::vector<bulletObj> bulletData;
        std::vector<bulletObj> bulletDataFriendly;
};

#endif /* !ENTITYDATA_HPP_ */
