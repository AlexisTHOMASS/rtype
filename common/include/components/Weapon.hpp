/*
** EPITECH PROJECT, 2021
** rType
** File description:
** Weapon
*/

#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include <SFML/Graphics.hpp>

enum WEAPON_TYPE {
    ShitGun = 0,
    ShitGunDual,
    MediumGun,
    MediumGunDual,
    CrossMediumShitGun,
    BigAssGun,
    BigAssGunDual,
    CrossBigAssMediumGun,
    OtsutsukiGun,
};

struct Weapon {
    WEAPON_TYPE weapon_type = WEAPON_TYPE::ShitGun;
    int direction = 1;
    sf::Color color = sf::Color(255, 255, 255, 255);
    int cadence = 500;
    int boost_speed = 0;
};

#endif /* !WEAPON_HPP_ */