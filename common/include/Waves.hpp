/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Waves
*/

#ifndef WAVES_HPP_
#define WAVES_HPP_

#include <map>
#include <vector>
#include <string>


enum EnemyList {
    Small1,
    Med1,
    Big1,
    Small2,
    Med2,
    Big2,
    Small3,
    Med3,
    Big3,
    Small4,
    Med4,
    Big4,
    NbEnemy
};

struct EnemyStats {
    std::string sprite;
    int hp;
    float speed;
    float difficulty;
};

static const std::map<EnemyList, EnemyStats> enemyStats = {
    {Small1, {"data/sprite/enemy/SmallPhase1.png", 10, 200, 1}},
    {Med1, {"data/sprite/enemy/MedPhase1.png", 25, 200, 3}},
    {Big1, {"data/sprite/enemy/BigPhase1.png", 75, 200, 9}},
    {Small2, {"data/sprite/enemy/SmallPhase2.png", 15, 200, 2}},
    {Med2, {"data/sprite/enemy/MedPhase2.png", 37, 200, 4.5}},
    {Big2, {"data/sprite/enemy/BigPhase2.png", 112, 200, 11}},
    {Small3, {"data/sprite/enemy/SmallPhase3.png", 20, 200, 3}},
    {Med3, {"data/sprite/enemy/MedPhase3.png", 50, 200, 6}},
    {Big3, {"data/sprite/enemy/BigPhase3.png", 150, 200, 13}},
    {Small4, {"data/sprite/enemy/SmallPhase4.png", 25, 200, 4}},
    {Med4, {"data/sprite/enemy/MedPhase4.png", 62, 200, 7.5}},
    {Big4, {"data/sprite/enemy/BigPhase4.png", 187, 200, 15}}
};

enum Level {
    Lvl1,
    Lvl2,
    Lvl3,
    Lvl4,
    Infinite
};

/* {time to wait, {{EnemyList type, nb EnemyList}, {EnemyList type, nb EnemyList}, ...}}*/
using LevelType = const std::vector<std::pair<float, std::vector<std::pair<EnemyList, size_t>>>>;

static LevelType waveLvl1 = {
    {2, {{EnemyList::Small1, 1}}},
    {2, {{EnemyList::Small1, 2}}},
    {2, {{EnemyList::Small1, 4}}},
    {5, {{EnemyList::Small1, 2}, {EnemyList::Med1, 1}}},
    {6, {{EnemyList::Big1, 1}}}
};

static LevelType waveLvl2 = {
    {2, {{EnemyList::Small2, 1}}},
    {2, {{EnemyList::Small2, 2}}},
    {2, {{EnemyList::Small2, 4}}},
    {5, {{EnemyList::Small2, 2}, {EnemyList::Med2, 1}}},
    {6, {{EnemyList::Big2, 1}}}
};

static LevelType waveLvl3 = {
    {2, {{EnemyList::Small3, 1}}},
    {2, {{EnemyList::Small3, 2}}},
    {2, {{EnemyList::Small3, 4}}},
    {5, {{EnemyList::Small3, 2}, {EnemyList::Med3, 1}}},
    {6, {{EnemyList::Big3, 1}}}
};

static LevelType waveLvl4 = {
    {2, {{EnemyList::Small4, 1}}},
    {2, {{EnemyList::Small4, 2}}},
    {2, {{EnemyList::Small4, 4}}},
    {5, {{EnemyList::Small4, 2}, {EnemyList::Med4, 1}}},
    {6, {{EnemyList::Big4, 1}}}
};


static const std::map<Level, LevelType> allLvl = {
    {Level::Lvl1, waveLvl1},
    {Level::Lvl2, waveLvl2},
    {Level::Lvl3, waveLvl3},
    {Level::Lvl4, waveLvl4},
    {Level::Infinite, {}}
};



#endif /* !WAVES_HPP_ */
