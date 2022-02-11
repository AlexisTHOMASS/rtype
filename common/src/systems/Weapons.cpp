/*
** EPITECH PROJECT, 2021
** rType
** File description:
** Bullets
*/

#include "Weapons.hpp"
#include "Sprite.hpp"
#include "Input.hpp"
#include "Motion.hpp"
#include "Weapon.hpp"
#include "sfmlFunc.hpp"

extern sf::Vector2f windowScale;
static const int dual_separator = 35;
static const int dual_separator_cross = 10;


void Weapons::init(Coordinator *coordinator)
{
    _coordinator = coordinator;
    _lastShot = std::chrono::high_resolution_clock::now();
    _shoot = {
        {WEAPON_TYPE::ShitGun, &Weapons::__shitShoot},
        {WEAPON_TYPE::ShitGunDual, &Weapons::__shitShootDual},
        {WEAPON_TYPE::MediumGun, &Weapons::__mediumShoot},
        {WEAPON_TYPE::MediumGunDual, &Weapons::__mediumShootDual},
        {WEAPON_TYPE::CrossMediumShitGun, &Weapons::__crossMediumShitShoot},
        {WEAPON_TYPE::BigAssGun, &Weapons::__bigAssShoot},
        {WEAPON_TYPE::BigAssGunDual, &Weapons::__bigAssShootDual},
        {WEAPON_TYPE::CrossBigAssMediumGun, &Weapons::__crossBigAssMediumShoot}
    };
    _bulletShitTexture = (char*)("data/sprite/yellow_bullet.png");
    _bulletMediumTexture = (char*)("data/sprite/red_bullet.png");
    _bulletBigAssTexture = (char*)("data/sprite/blue_bullet.png");
}

std::vector<Entity> Weapons::update()
{
    static std::unordered_map<Entity, int> time_count;
    _new_bullets.clear();
    for (auto const &entity : _entities) {
        Signature sig = _coordinator->getSignature(entity);
        if (!sig[_coordinator->getComponentType<Weapon>()])
            continue;
        time_count[entity] += std::chrono::duration<float, std::chrono::milliseconds::period>(std::chrono::high_resolution_clock::now() - _lastShot).count();
        Weapon &weapon = _coordinator->getComponent<Weapon>(entity);
        if (time_count.at(entity) < weapon.cadence)
            continue;
        time_count.at(entity) = 0;
        (this->*_shoot.at(weapon.weapon_type))(entity, {});
    }
    _lastShot = std::chrono::high_resolution_clock::now();
    return _new_bullets;
}

void Weapons::shootWith(Entity player, Entity entity)
{
    Signature sig = _coordinator->getSignature(entity);
    Signature sigPlayer = _coordinator->getSignature(player);
    if (!sig[_coordinator->getComponentType<Weapon>()] || !sigPlayer[_coordinator->getComponentType<Sprite>()])
        return;
    Weapon &weapon = _coordinator->getComponent<Weapon>(entity);
    (this->*_shoot.at(weapon.weapon_type))(player, {});
}

void Weapons::__shoot(Entity playerEntity, sf::Vector2i offset, BULLET_DAMAGE damage, char *&path, float speed)
{
    auto &sprite = _coordinator->getComponent<Sprite>(playerEntity);
    auto &weapon = _coordinator->getComponent<Weapon>(playerEntity);
    sf::Vector2u size = sprite.tex.getSize();
    sf::Vector2f pos = sprite.sprite.getPosition();
    offset.x *= windowScale.x;
    offset.y *= windowScale.y;

    Entity bullet_entity = _coordinator->createEntity();
    _coordinator->addComponent<Motion>(bullet_entity, {sf::Vector2f((speed + weapon.boost_speed) * weapon.direction , 0), sf::Vector2f(0, 0)});
    _coordinator->addComponent<Sprite>(bullet_entity, createSprite(path, Phase::Play));
    _coordinator->addComponent<Bullet_Comp>(bullet_entity, {damage, weapon.direction > 0 ? true : false});
    auto &bulletSprite = _coordinator->getComponent<Sprite>(bullet_entity);
    bulletSprite.sprite.setColor(weapon.color);
    bulletSprite.sprite.setPosition({pos.x + size.x / 2 + offset.x, pos.y + size.y / 2 + (bulletSprite.tex.getSize().y * windowScale.y) / 2 + offset.y});
    _new_bullets.push_back(bullet_entity);
}

void Weapons::__shitShoot(Entity entity, sf::Vector2i offset)
{
    this->__shoot(entity, offset, BULLET_DAMAGE::ShitBullet, _bulletShitTexture, 500);
}

void Weapons::__shitShootDual(Entity entity, sf::Vector2i offset)
{
    this->__shitShoot(entity, {offset.x, offset.y - dual_separator});
    this->__shitShoot(entity, {-offset.x, -offset.y + dual_separator});
}

void Weapons::__mediumShoot(Entity entity, sf::Vector2i offset)
{
    this->__shoot(entity, offset, BULLET_DAMAGE::MediumBullet, _bulletMediumTexture, 550);
}

void Weapons::__mediumShootDual(Entity entity, sf::Vector2i offset)
{
    this->__mediumShoot(entity, {offset.x, offset.y - dual_separator});
    this->__mediumShoot(entity, {-offset.x, -offset.y + dual_separator});
}

void Weapons::__crossMediumShitShoot(Entity entity, sf::Vector2i _none)
{
    (void)_none;
    __shitShootDual(entity, {0, dual_separator_cross});
    __mediumShootDual(entity, {});
}

void Weapons::__bigAssShoot(Entity entity, sf::Vector2i offset)
{
    this->__shoot(entity, offset, BULLET_DAMAGE::BigAssBullet, _bulletBigAssTexture, 650);
}

void Weapons::__bigAssShootDual(Entity entity, sf::Vector2i offset)
{
    this->__bigAssShoot(entity, {offset.x, offset.y - dual_separator});
    this->__bigAssShoot(entity, {-offset.x, -offset.y + dual_separator});
}

void Weapons::__crossBigAssMediumShoot(Entity entity, sf::Vector2i _none)
{
    (void)_none;
    __mediumShootDual(entity, {0, dual_separator_cross});
    __bigAssShootDual(entity, {});
}