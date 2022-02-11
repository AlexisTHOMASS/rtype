/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** ServerManagerProtocol
*/

#ifndef SERVERMANAGERPROTOCOL_HPP_
#define SERVERMANAGERPROTOCOL_HPP_

static const unsigned short MSG_MAX_LEN = 1024;

using protocolType = const unsigned char;

namespace ServerManagerProtocol {

    // Connection
    static protocolType CONNECTION = 100;
    static protocolType CONNECTION_ACCEPTED = 101;
    static protocolType CONNECTION_REFUSED = 102;

    // Server creation
    static protocolType CREATE_SERVER = 110;
    static protocolType SERVER_CREATED = 111;
    static protocolType CREATING_SERVER = 112;
    static protocolType SERVER_CREATION_FAILED = 113;

    // Error
    static protocolType INVALID_REQUEST = 200;
}

namespace ServerGamePlayProtool {
    static protocolType PLAYER_ID = 10;
    static protocolType PLAYER_POSITION = 11;
    static protocolType BULLET_PLAYER = 12;
    static protocolType PLAYER_DEATH = 13;
    static protocolType ENEMY_POSITION = 20;
    static protocolType BULLET_ENEMY = 21;
    static protocolType LAUNCH_GAME = 30;
    static protocolType END_GAME = 40;
}

#endif /* !SERVERMANAGERPROTOCOL_HPP_ */