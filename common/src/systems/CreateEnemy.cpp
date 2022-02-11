/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** CreateEnemy
*/

#include "CreateEnemy.hpp"
#include "Random.hpp"
#include "Motion.hpp"
#include "Sprite.hpp"
#include "Ship.hpp"
#include "Weapon.hpp"
#include "sfmlFunc.hpp"
#include <iostream>

extern sf::Vector2f windowScale;

void CreateEnemy::init(Coordinator *coordinator)
{
    _coordinator = coordinator;
    _timeWave = std::chrono::high_resolution_clock::now();
    _level = Level::Lvl1;
    _wave = 0;
    _infiniteDifficulty = 5;
    _infiniteSpawnSpeed = 5;
}

std::vector<Entity> CreateEnemy::update()
{
    static Random<int> ySpawn(50, 1020);
    static Random<int> xPos(1400, 1700);
    std::vector<Entity> newEnemy;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        std::vector<Entity> toDestroy;
        for (auto const &entity : _entities) {
            toDestroy.push_back(entity);
        }
        for (auto it : toDestroy)
            _coordinator->destroyEntity(it);
    }
    if (_level == Level::Infinite) {
        __levelInfinite(newEnemy);
        return newEnemy;
    }
    bool noEnemy = true;
    if (allLvl.at(_level).size() == size_t(_wave)) {
        for (auto it : _entities) {
            auto ship = _coordinator->getComponent<Ship>(it);
            if (!ship.isFreindly) {
                noEnemy = false;
                break;
            }
        }
        if (noEnemy) {
            _level = Level(_level + 1);
            _wave = 0;
        }
        return newEnemy;
    }
    if (std::chrono::duration<float, std::chrono::seconds::period>(std::chrono::high_resolution_clock::now() - _timeWave).count()
    > allLvl.at(_level).at(_wave).first) {
        for (size_t i = 0 ; i != allLvl.at(_level).at(_wave).second.size() ; i += 1) {
            for (size_t j = 0 ; j != allLvl.at(_level).at(_wave).second.at(i).second ; j += 1) {
                Entity enemy = _coordinator->createEntity();
                _coordinator->addComponent<Motion>(enemy, {sf::Vector2f(-enemyStats.at(allLvl.at(_level).at(_wave).second.at(i).first).speed, 0), sf::Vector2f(0, 0)});
                _coordinator->addComponent<Sprite>(enemy, createSprite(enemyStats.at(allLvl.at(_level).at(_wave).second.at(i).first).sprite, Phase::Play));
                _coordinator->addComponent<Ship>(enemy, {false, enemyStats.at(allLvl.at(_level).at(_wave).second.at(i).first).speed, int(xPos.rand() * windowScale.x),
                enemyStats.at(allLvl.at(_level).at(_wave).second.at(i).first).hp, enemyStats.at(allLvl.at(_level).at(_wave).second.at(i).first).difficulty});
                _coordinator->addComponent<Weapon>(enemy, {WEAPON_TYPE::ShitGun, -1, sf::Color(255, 0, 0, 255), 800});
                auto &enemySprite = _coordinator->getComponent<Sprite>(enemy);
                enemySprite.sprite.setPosition({1918 * windowScale.x, ySpawn.rand() * windowScale.y});
                newEnemy.push_back(enemy);
            }
        }
        _timeWave = std::chrono::high_resolution_clock::now();
        _wave += 1;
    }
    return newEnemy;
}

void CreateEnemy::__levelInfinite(std::vector<Entity> &newEnemy)
{
    static Random<float> difficultyMult(1, 1.5);
    static Random<int> getEnemy(0, EnemyList::NbEnemy - 1);
    static Random<int> ySpawn(50, 1020);
    static Random<int> xPos(1400, 1700);

    if (std::chrono::duration<float, std::chrono::seconds::period>(std::chrono::high_resolution_clock::now() - _timeWave).count()
    > _infiniteSpawnSpeed) {
        float difficulty = _infiniteDifficulty * difficultyMult.rand();
        while (difficulty > enemyStats.at(EnemyList::Small1).difficulty) {
            EnemyList enemyType = EnemyList(getEnemy.rand());
            for (int i = 2 ; enemyStats.at(enemyType).difficulty > difficulty ; i += 1)
                enemyType = EnemyList(getEnemy.rand() / i);
            Entity enemy = _coordinator->createEntity();
            _coordinator->addComponent<Motion>(enemy, {sf::Vector2f(-enemyStats.at(enemyType).speed, 0), sf::Vector2f(0, 0)});
            _coordinator->addComponent<Sprite>(enemy, createSprite(enemyStats.at(enemyType).sprite, Phase::Play));
            _coordinator->addComponent<Ship>(enemy, {false, enemyStats.at(enemyType).speed, int(xPos.rand() * windowScale.x), enemyStats.at(enemyType).hp, enemyStats.at(enemyType).difficulty});
            _coordinator->addComponent<Weapon>(enemy, {WEAPON_TYPE::ShitGun, -1, sf::Color(255, 255, 255, 255),750});
            auto &enemySprite = _coordinator->getComponent<Sprite>(enemy);
            enemySprite.sprite.setPosition({1918 * windowScale.x, ySpawn.rand() * windowScale.y});
            difficulty -= enemyStats.at(enemyType).difficulty;
            newEnemy.push_back(enemy);
        }
        _infiniteDifficulty += 0.4;
        _infiniteSpawnSpeed /= 1.03;
        _timeWave = std::chrono::high_resolution_clock::now();
    }
}