/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

enum ModifSettings {
    moveForward = 25,
    moveDown = 18,
    moveLeft = 16,
    moveRight = 3
};

struct SettingsStr {
    ModifSettings modifSettings;
};


#endif /* !SETTINGS_HPP_ */


