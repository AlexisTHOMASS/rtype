/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** PlayerMotion
*/

#include "PlayerMotion.hpp"
#include "Input.hpp"
#include "Motion.hpp"
#include "Sprite.hpp"
#include <iostream>
#include "MergeData.hpp"

extern sf::Vector2f windowScale;

void PlayerMotion::init(Coordinator *coordinator)
{
    _coordinator = coordinator;
}

void PlayerMotion::update()
{
    for (auto const& entity : _entities) {
        auto &input = _coordinator->getComponent<Input>(entity);
        auto &motion = _coordinator->getComponent<Motion>(entity);
        if (motion.velocity.x < -500)
            return;
        bool up = Input::keyPressed(input.Up);
        bool down = Input::keyPressed(input.Down);
        bool left = Input::keyPressed(input.Left);
        bool right = Input::keyPressed(input.Right);
        sf::Vector2f speed(20 * windowScale.x, 20 * windowScale.y);
        sf::Vector2f maxBoost(400 * windowScale.x, 400 * windowScale.y);
        sf::Vector2f boost(0.2 * speed.x * windowScale.x, 0.2 * speed.y * windowScale.y);
        sf::Vector2f multiDirMaxBoost(maxBoost.x * 0.71 * windowScale.x, maxBoost.y * 0.71 * windowScale.y);
        sf::Vector2f multiDirSpeed(speed.x * 0.71 * windowScale.x, speed.y * 0.71 * windowScale.y);
        sf::Vector2f multiDirBoost(boost.x * 0.71 * windowScale.x, boost.y * 0.71 * windowScale.y);

        motion.acceleration.x = 0;
        motion.acceleration.y = 0;
        if (up && right) {
            motion.acceleration.x = multiDirSpeed.x;
            motion.acceleration.y = -multiDirSpeed.y;
            if (motion.velocity.x <= multiDirMaxBoost.x)
                motion.velocity.x += multiDirBoost.x;
            if (motion.velocity.y >= -multiDirMaxBoost.y)
                motion.velocity.y -= multiDirBoost.y;
        } else if (right && down) {
            motion.acceleration.x = multiDirSpeed.x;
            motion.acceleration.y = multiDirSpeed.y;
            if (motion.velocity.x <= multiDirMaxBoost.x)
                motion.velocity.x += multiDirBoost.x;
            if (motion.velocity.y <= multiDirMaxBoost.y)
                motion.velocity.y += multiDirBoost.y;
        } else if (down && left) {
            motion.acceleration.x = -multiDirSpeed.x;
            motion.acceleration.y = multiDirSpeed.y;
            if (motion.velocity.x >= -multiDirMaxBoost.x)
                motion.velocity.x -= multiDirSpeed.x;
            if (motion.velocity.y <= multiDirMaxBoost.y)
                motion.velocity.y += multiDirBoost.y;
        } else if (left && up) {
            motion.acceleration.x = -multiDirSpeed.x;
            motion.acceleration.y = -multiDirSpeed.y;
            if (motion.velocity.x >= -multiDirMaxBoost.x)
                motion.velocity.x -= multiDirSpeed.x;
            if (motion.velocity.y >= -multiDirMaxBoost.y)
                motion.velocity.y -= multiDirBoost.y;
        } else if (up) {
            motion.acceleration.y = -speed.y;
            if (motion.velocity.y >= -maxBoost.y)
                motion.velocity.y -= boost.y;
        } else if (right) {
            motion.acceleration.x = speed.x;
            if (motion.velocity.x <= maxBoost.x)
                motion.velocity.x += boost.x;
        } else if (down) {
            motion.acceleration.y = speed.y;
            if (motion.velocity.y <= maxBoost.y)
                motion.velocity.y += boost.y;
        } else if (left) {
            motion.acceleration.x = -speed.x;
            if (motion.velocity.x >= -maxBoost.x)
                motion.velocity.x -= boost.x;
        }

        // auto pos = sprite.sprite.getPostion();
        // sprite.sprite.setPosition(pos.x * windowssc);
        // obj playerObj = {sprite, motion, -2};
        // char *toSend = mergeData::mergeBinaries<obj>(420, playerObj);
        
    }
}
