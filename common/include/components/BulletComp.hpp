/*
** EPITECH PROJECT, 2021
** rType
** File description:
** BulletComp
*/

#ifndef BULLETCOMP_HPP_
#define BULLETCOMP_HPP_

enum BULLET_DAMAGE {
    ShitBullet = 10,
    MediumBullet = 20,
    BigAssBullet = 30,
    OtsutsukiBullet = 50,
};

struct Bullet_Comp {
    BULLET_DAMAGE bullet_damage = ShitBullet;
    bool isFrendly = true;
};

#endif /* !BULLETCOMP_HPP_ */