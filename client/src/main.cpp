/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include "Coordinator.hpp"
#include "Sprite.hpp"
#include "Motion.hpp"
#include "Input.hpp"
#include "Mouvement.hpp"
#include "Render.hpp"
#include "init.hpp"
#include "initPhase.hpp"
#include "GestButton.hpp"
#include "iostream"
#include "DestroyOutOfScreen.hpp"
#include "PrintText.hpp"
#include "TextBox.hpp"
#include "Network.hpp"
#include "GameNetwork.hpp"
#include "MergeData.hpp"
#include "sfmlFunc.hpp"
#include "Ship.hpp"
#include "EntityObject.hpp"
#include "EntityData.hpp"
#include "ServerProtocol.hpp"
#include "ParallaxeComp.hpp"
#include "SFML/Audio.hpp"

sf::Vector2f windowScale;

void gameLoop(Coordinator &coordinator, sf::RenderWindow &window, std::map<uint16_t, Entity> &entityId, std::pair<uint16_t, Entity> &playerId)
{
    Network* net;
    auto tps = std::chrono::high_resolution_clock::now();
    std::map<int, Entity> _mobs;
    EntityData entityData;
    GameNetwork *gameNet;
    sf::SoundBuffer buffer;
    sf::Sound sound; //= buffer.loadFromFile("data/sound/music.ogg");
    asio::io_context io_context;
    asio::io_context io_context2;
    asio::io_context io_context3;

    auto mouvementSystem = initMouvementSystem(coordinator);
    auto renderSystem = initRenderSystem(coordinator, &window);
    auto playerMotionSystem = initPlayerMotionSystem(coordinator);
    auto gestButtonSystem = initGestButtonSystem(coordinator, &window);
    auto destroyOutOfScreenSystem = initDestroyOutOfScreenSystem(coordinator, window.getSize());
    auto weaponSystem = initWeaponsSystem(coordinator);
    auto printTextSystem = initPrintText(coordinator, &window);
    auto textBoxSystem = initTextBox(coordinator, &window);
    auto collideSystem = initCollide(coordinator);
    auto settingsSystem = initSettingsSystem(coordinator);
    auto movingbarSystem = initMovingBarSystem(coordinator, &window, &sound);
    auto parallaxeSystem = initParallaxeSystem(coordinator, &window);
    bool init = true;

    while (window.isOpen())
    {
        if (init) {
            initMainMenu(coordinator);
            initSettings(coordinator);
            initChooseGame(coordinator);
            initJoinGame(coordinator);
            initConnect(coordinator);
            initScore(coordinator);
            initLobby(coordinator);
            initCreateGame(coordinator);
            buffer.loadFromFile("data/sound/music.ogg");
            sound.setBuffer(buffer);
            sound.setLoop(true);
            sound.play();
            init = false;
        }
    
        // General system
        parallaxeSystem->update();
        renderSystem->update();
        gestButtonSystem->update();
        printTextSystem->update();
        textBoxSystem->update();
        settingsSystem->update();
        movingbarSystem->update();

        if (coordinator.phase[Phase::Play] || coordinator.phase[Phase::Lobby]) {
            playerMotionSystem->update();
            mouvementSystem->update();
            destroyOutOfScreenSystem->update();
            for (auto bullet_entity : weaponSystem->update()) {
                auto &sprite = coordinator.getComponent<Sprite>(bullet_entity);
	        	auto &motion = coordinator.getComponent<Motion>(bullet_entity);
	        	bulletObj bullet_obj;
	        	bullet_obj.motion = motion;
	        	bullet_obj.pos = {sprite.sprite.getPosition().x / windowScale.x, sprite.sprite.getPosition().y / windowScale.y};
	        	std::strcpy(bullet_obj.texture, sprite.path.c_str());
	        	char *data_enemy = mergeData::mergeBinaries<bulletObj>(ServerGamePlayProtool::BULLET_PLAYER, bullet_obj);
	        	gameNet->write(data_enemy);
                coordinator.destroyEntity(bullet_entity);
            }
            // -- To put in server --
            // enemyMotionSystem->update();
            // createEnemySystem->update();
            collideSystem->update(mouvementSystem->_entities);
            // -- --
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (Input::keyPressed(sf::Keyboard::Escape) || coordinator.phase[Phase::Exit])
            window.close();
        if (coordinator.phase[Phase::Lobby] && Input::keyPressed(sf::Keyboard::L)) {
            gameNet->write(mergeData::mergeBinaries<char>(ServerGamePlayProtool::LAUNCH_GAME, 0));
        }
        if (coordinator.phase[Phase::CreateGameId]) {
            net->createServer(std::stoi(textBoxSystem->get(4)));
            
            gameNet = new GameNetwork(io_context2, textBoxSystem->get(2).c_str(), textBoxSystem->get(4));
            gameNet->write((char*)"test");
            std::thread([&]{io_context2.run();}).detach();
            char *data;
            do {
                data = gameNet->getData();
            } while (mergeData::getProtocol(data) != ServerGamePlayProtool::PLAYER_ID);
            std::pair<int, uint16_t> getId = mergeData::unPack<uint16_t>(data);
            playerId.first = getId.second;
            initPlay(coordinator, playerId);
            coordinator.phase.set(Phase::CreateGameId, false);
            coordinator.phase.set(Phase::LobbyAndPlay, true);
            coordinator.phase.set(Phase::Lobby, true);
        }
        if (coordinator.phase[Phase::JoinGameId]) {
            gameNet = new GameNetwork(io_context2, textBoxSystem->get(2).c_str(), textBoxSystem->get(1));
            gameNet->write((char*)"test");
            std::thread([&]{io_context2.run();}).detach();
            char *data;
            do {
                data = gameNet->getData();
            } while (mergeData::getProtocol(data) != ServerGamePlayProtool::PLAYER_ID);
            std::pair<int, uint16_t> getId = mergeData::unPack<uint16_t>(data);
            playerId.first = getId.second;
            initPlay(coordinator, playerId);
            coordinator.phase.set(Phase::JoinGameId, false);
            coordinator.phase.set(Phase::LobbyAndPlay, true);
            coordinator.phase.set(Phase::Lobby, true);
        }
        if (coordinator.phase[Phase::Connection]) {
            try {
                net = new Network(io_context3, textBoxSystem->get(2).c_str(), textBoxSystem->get(3).c_str());
                io_context3.run();
                coordinator.phase.set(Phase::Connection, false);
                coordinator.phase.set(Phase::MainMenu, true);
            } catch(const std::exception& e) {
                std::cerr << e.what() << '\n';
            }
        }
        if (coordinator.phase[Phase::LobbyAndPlay]) {
            if (std::chrono::duration<float, std::chrono::milliseconds::period>(std::chrono::high_resolution_clock::now() - tps).count() >= 1000 / TPS) {
                playerObj po;
                Sprite sprite = coordinator.getComponent<Sprite>(playerId.second);
                po.id = playerId.first;
                po.pos = {sprite.sprite.getPosition().x / windowScale.x, sprite.sprite.getPosition().y / windowScale.y};
                std::strcpy(po.texture, sprite.path.c_str());
                char *toSend = mergeData::mergeBinaries<playerObj>(ServerGamePlayProtool::PLAYER_POSITION, po);
                gameNet->write(toSend);
                tps = std::chrono::high_resolution_clock::now();
            }

            /////////recive data/////////
            gameNet->__receive();
            char *data = gameNet->getData();
            while (mergeData::getProtocol(data) != 0) {
                if (mergeData::getProtocol(data) == ServerGamePlayProtool::PLAYER_DEATH) {
                    uint16_t id_death = mergeData::unPack<uint16_t>(data).second;
                    if (id_death == playerId.first) {
                        Motion &my_motion = coordinator.getComponent<Motion>(playerId.second);
                        my_motion.velocity.x = -550;
                        my_motion.rotation = 360;
                        ;// cancel input
                    }
                }
                entityData.loadData(data, coordinator);
                for (playerObj &pObj : entityData.playerData) {
                    if (playerId.first != pObj.id) {
                        if (entityId.find(pObj.id) == entityId.end()) {
                            Entity pentity = coordinator.createEntity();
                            coordinator.addComponent<Motion>(pentity, {sf::Vector2f(0, 0), sf::Vector2f(0, 0)});
                            coordinator.addComponent<Sprite>(pentity, createSprite(pObj.texture, Phase::LobbyAndPlay));
                            coordinator.addComponent<Ship>(pentity, {});
                            entityId.insert({pObj.id, pentity});
                        }
                        auto &spritePlayer = coordinator.getComponent<Sprite>(entityId.at(pObj.id));
                        spritePlayer.sprite.setPosition({pObj.pos.x * windowScale.x, pObj.pos.y * windowScale.y});
                    }
                }
                entityData.playerData.clear();
                for (enemyObj &eo : entityData.enemyData) {
                    if (entityId.find(eo.id) == entityId.end()) {
                        Entity entity_mob = coordinator.createEntity();
                        coordinator.addComponent<Motion>(entity_mob, eo.motion);
                        coordinator.addComponent<Sprite>(entity_mob, createSprite(eo.texture, Phase::Play));
                        coordinator.addComponent<Ship>(entity_mob, {false});
                        entityId.insert({eo.id, entity_mob});
                    }
                    Sprite &enemy_sprite = coordinator.getComponent<Sprite>(entityId.at(eo.id));
                    Motion &enemy_motion = coordinator.getComponent<Motion>(entityId.at(eo.id));
                    enemy_motion = eo.motion;
                    enemy_sprite.sprite.setPosition({eo.pos.x * windowScale.x, eo.pos.y * windowScale.y});
                }
                entityData.enemyData.clear();

                for (bulletObj &bo : entityData.bulletData) {
                    Entity entity_bullet = coordinator.createEntity();
                    coordinator.addComponent<Motion>(entity_bullet, bo.motion);
                    coordinator.addComponent<Sprite>(entity_bullet, createSprite(bo.texture, Phase::Play));
                    coordinator.addComponent<Bullet_Comp>(entity_bullet, {BULLET_DAMAGE::ShitBullet, false});
                    Sprite &bullet_sprite = coordinator.getComponent<Sprite>(entity_bullet);
                    Motion &bullet_motion = coordinator.getComponent<Motion>(entity_bullet);
                    bullet_motion = bo.motion;
                    bullet_sprite.sprite.setPosition({bo.pos.x * windowScale.x, bo.pos.y * windowScale.y});
                }
                entityData.bulletData.clear();

                for (bulletObj &bo : entityData.bulletDataFriendly) {
                    Entity entity_bullet = coordinator.createEntity();
                    coordinator.addComponent<Motion>(entity_bullet, bo.motion);
                    coordinator.addComponent<Sprite>(entity_bullet, createSprite(bo.texture, Phase::Play));
                    coordinator.addComponent<Bullet_Comp>(entity_bullet, {BULLET_DAMAGE::ShitBullet, true});
                    Sprite &bullet_sprite = coordinator.getComponent<Sprite>(entity_bullet);
                    Motion &bullet_motion = coordinator.getComponent<Motion>(entity_bullet);
                    bullet_motion = bo.motion;
                    bullet_sprite.sprite.setPosition({bo.pos.x * windowScale.x, bo.pos.y * windowScale.y});
                }
                entityData.bulletDataFriendly.clear();
                gameNet->__receive();
                data = gameNet->getData();
            }
        }
        window.display();
        window.clear();
    }
}

void tmp(asio::io_context io_context)
{
    io_context.run();
}

int main()
{
    Coordinator coordinator;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Type", sf::Style::Fullscreen);
    sf::Vector2u winSize = window.getSize();

    windowScale = {float(winSize.x) / float(WINDOW_WIDTH), float(winSize.y) / float(WINDOW_HEIGHT)};
    coordinator.phase.set(Phase::MainMenu, true);
    init(coordinator);
    
    // Init ECS
    std::map<uint16_t, Entity> entityId;
    std::pair<uint16_t, Entity> playerId;

    gameLoop(coordinator, window, entityId, playerId);

    return (0);
}