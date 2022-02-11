/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** play
*/

#include "init.hpp"
#include "Sprite.hpp"
#include "Motion.hpp"
#include "Input.hpp"
#include "Weapon.hpp"
#include "initPhase.hpp"
#include "Phase.hpp"
#include "Clickable.hpp"
#include "iostream"
#include "GestButton.hpp"
#include "Ship.hpp"
#include "sfmlFunc.hpp"
#include "Text.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Font.hpp"
#include "Settingsys.hpp"
#include "Settings.hpp"
#include "Bar.hpp"
#include "ParallaxeComp.hpp"

extern sf::Vector2f windowScale;

void initPlay(Coordinator &coordinator, std::pair<uint16_t, Entity> &playerId)
{
    // Creating player
    Entity player = coordinator.createEntity();
    coordinator.addComponent<Motion>(player, {sf::Vector2f(0, 0), sf::Vector2f(0, 0)});
    coordinator.addComponent<Sprite>(player, createSprite(allPlayerSprite.at(PlayerList(playerId.first)), Phase::LobbyAndPlay));
    coordinator.addComponent<Input>(player, {sf::Keyboard::Z, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::Q});
    coordinator.addComponent<Ship>(player, {});
    auto &playerSprite = coordinator.getComponent<Sprite>(player);
    playerSprite.sprite.setPosition({590 * windowScale.x, (200 * playerId.first) * windowScale.y});

    // Creating Weapon
    coordinator.addComponent<Weapon>(player, {WEAPON_TYPE::CrossBigAssMediumGun});
    playerId.second = player;
    coordinator._player = player;
}

void initMainMenu(Coordinator &coordinator)
{
    sf::Color color = sf::Color::White;

    Entity background = coordinator.createEntity();
    coordinator.addComponent<Sprite>(background, createSprite("data/sprite/background.jpg", Phase::MainMenu));

    Entity title = coordinator.createEntity();
    coordinator.addComponent<Sprite>(title, createSprite("data/sprite/title.png", Phase::MainMenu));
    auto &titleSprite = coordinator.getComponent<Sprite>(title);
    titleSprite.sprite.setPosition({594 * windowScale.x, 60 * windowScale.y});

    Entity connectButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(connectButton, createSprite("data/sprite/connectButton.png", Phase::MainMenu));
    coordinator.addComponent<Clickable>(connectButton, {connect});
    auto &connectSprite = coordinator.getComponent<Sprite>(connectButton);
    connectSprite.sprite.setPosition({1547 * windowScale.x, 28 * windowScale.y});
    connectSprite.sprite.setColor(color);

    Entity exitButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(exitButton, createSprite("data/sprite/exitButton.png", Phase::MainMenu));
    coordinator.addComponent<Clickable>(exitButton, {exitFun});
    auto &exitSprite = coordinator.getComponent<Sprite>(exitButton);
    exitSprite.sprite.setPosition({1373 * windowScale.x, 880 * windowScale.y});
    exitSprite.sprite.setColor(color);

    Entity playButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(playButton, createSprite("data/sprite/playButton.png", Phase::MainMenu));
    coordinator.addComponent<Clickable>(playButton, {chooseGame});
    auto &PlaySprite = coordinator.getComponent<Sprite>(playButton);
    PlaySprite.sprite.setPosition({622 * windowScale.x, 850 * windowScale.y});
    PlaySprite.sprite.setColor(color);

    Entity settingsButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(settingsButton, createSprite("data/sprite/settingsButton.png", Phase::MainMenu));
    coordinator.addComponent<Clickable>(settingsButton, {settingsFun});
    auto &settingsSprite = coordinator.getComponent<Sprite>(settingsButton);
    settingsSprite.sprite.setPosition({63 * windowScale.x , 880 * windowScale.y});
    settingsSprite.sprite.setColor(color);
}

void initSettings(Coordinator &coordinator)
{
    Entity background = coordinator.createEntity();
    coordinator.addComponent<Sprite>(background, createSprite("data/sprite/background.jpg", Phase::Settings));

    Entity movingForward = coordinator.createEntity();
    coordinator.addComponent<Text>(movingForward, {sf::Text(), "Moving Up :", Phase::Settings, 100});
    auto &movingForwardText = coordinator.getComponent<Text>(movingForward);
    movingForwardText._sftext.setPosition({230 * windowScale.x, 265 * windowScale.y});
    movingForwardText._sftext.setFillColor(sf::Color::Black);
    movingForwardText._sftext.setStyle(sf::Text::Bold);
    Entity movingForwardModif = coordinator.createEntity();
    coordinator.addComponent<Sprite>(movingForwardModif, createSprite("data/sprite/emptybox.png", Phase::Settings));
    coordinator.addComponent<Clickable>(movingForwardModif, {});
    coordinator.addComponent<Text>(movingForwardModif, {sf::Text(), "z", Phase::Settings, 1});
    coordinator.addComponent<SettingsStr>(movingForwardModif, {ModifSettings::moveForward});
    auto &movingForwardModifText = coordinator.getComponent<Text>(movingForwardModif);
    movingForwardModifText._sftext.setPosition({420 * windowScale.x, 267 * windowScale.y});
    movingForwardModifText._sftext.setFillColor(sf::Color::Black);
    movingForwardModifText._sftext.setStyle(sf::Text::Bold);
    auto &spriteMovingForward = coordinator.getComponent<Sprite>(movingForwardModif);
    spriteMovingForward.sprite.setPosition({180 * windowScale.x, 225 * windowScale.y});

    Entity MovingDown = coordinator.createEntity();
    coordinator.addComponent<Text>(MovingDown, {sf::Text(), "Moving Down :", Phase::Settings, 100});
    auto &MovingDownText = coordinator.getComponent<Text>(MovingDown);
    MovingDownText._sftext.setPosition({230 * windowScale.x, 390 * windowScale.y});
    MovingDownText._sftext.setFillColor(sf::Color::Black);
    MovingDownText._sftext.setStyle(sf::Text::Bold);
    Entity MovingDownModif = coordinator.createEntity();
    coordinator.addComponent<Sprite>(MovingDownModif, createSprite("data/sprite/emptybox.png", Phase::Settings));
    coordinator.addComponent<Clickable>(MovingDownModif, {});
    coordinator.addComponent<Text>(MovingDownModif, {sf::Text(), "s", Phase::Settings, 1});
    coordinator.addComponent<SettingsStr>(MovingDownModif, {ModifSettings::moveDown});
    auto &MovingDownModifText = coordinator.getComponent<Text>(MovingDownModif);
    MovingDownModifText._sftext.setPosition({450 * windowScale.x, 392 * windowScale.y});
    MovingDownModifText._sftext.setFillColor(sf::Color::Black);
    MovingDownModifText._sftext.setStyle(sf::Text::Bold);
    auto &spriteMovingDown = coordinator.getComponent<Sprite>(MovingDownModif);
    spriteMovingDown.sprite.setPosition({180 * windowScale.x, 350 * windowScale.y});

    Entity MovingLeft = coordinator.createEntity();
    coordinator.addComponent<Text>(MovingLeft, {sf::Text(), "Moving Left :", Phase::Settings, 100});
    auto &MovingLeftText = coordinator.getComponent<Text>(MovingLeft);
    MovingLeftText._sftext.setPosition({230 * windowScale.x, 515 * windowScale.y});
    MovingLeftText._sftext.setFillColor(sf::Color::Black);
    MovingLeftText._sftext.setStyle(sf::Text::Bold);
    Entity MovingLeftModif = coordinator.createEntity();
    coordinator.addComponent<Sprite>(MovingLeftModif, createSprite("data/sprite/emptybox.png", Phase::Settings));
    coordinator.addComponent<Clickable>(MovingLeftModif, {});
    coordinator.addComponent<Text>(MovingLeftModif, {sf::Text(), "q", Phase::Settings, 1});
    coordinator.addComponent<SettingsStr>(MovingLeftModif, {ModifSettings::moveLeft});
    auto &MovingLeftModifText = coordinator.getComponent<Text>(MovingLeftModif);
    MovingLeftModifText._sftext.setPosition({425 * windowScale.x, 517 * windowScale.y});
    MovingLeftModifText._sftext.setFillColor(sf::Color::Black);
    MovingLeftModifText._sftext.setStyle(sf::Text::Bold);
    auto &spriteMovingLeft = coordinator.getComponent<Sprite>(MovingLeftModif);
    spriteMovingLeft.sprite.setPosition({180 * windowScale.x, 475 * windowScale.y});

    Entity MovingRight = coordinator.createEntity();
    coordinator.addComponent<Text>(MovingRight, {sf::Text(), "Moving Right :", Phase::Settings, 100});
    auto &MovingRightText = coordinator.getComponent<Text>(MovingRight);
    MovingRightText._sftext.setPosition({230 * windowScale.x, 640 * windowScale.y});
    MovingRightText._sftext.setFillColor(sf::Color::Black);
    MovingRightText._sftext.setStyle(sf::Text::Bold);
    Entity MovingRightModif = coordinator.createEntity();
    coordinator.addComponent<Sprite>(MovingRightModif, createSprite("data/sprite/emptybox.png", Phase::Settings));
    coordinator.addComponent<Clickable>(MovingRightModif, {});
    coordinator.addComponent<Text>(MovingRightModif, {sf::Text(), "d", Phase::Settings, 1});
    coordinator.addComponent<SettingsStr>(MovingRightModif, {ModifSettings::moveRight});
    auto &MovingRightModifText = coordinator.getComponent<Text>(MovingRightModif);
    MovingRightModifText._sftext.setPosition({450 * windowScale.x, 642 * windowScale.y});
    MovingRightModifText._sftext.setFillColor(sf::Color::Black);
    MovingRightModifText._sftext.setStyle(sf::Text::Bold);
    auto &spriteMovingRight = coordinator.getComponent<Sprite>(MovingRightModif);
    spriteMovingRight.sprite.setPosition({180 * windowScale.x, 600 * windowScale.y});

    Entity FpsText = coordinator.createEntity();
    coordinator.addComponent<Text>(FpsText, {sf::Text(), "FPS", Phase::Settings, 0});
    auto &FpsTextText = coordinator.getComponent<Text>(FpsText);
    FpsTextText._sftext.setPosition({1361 * windowScale.x, 240 * windowScale.y});
    FpsTextText._sftext.setFillColor(sf::Color::White);
    FpsTextText._sftext.setStyle(sf::Text::Bold);
    Entity FpsBar = coordinator.createEntity();
    coordinator.addComponent<Sprite>(FpsBar, createSprite("data/sprite/bar.png", Phase::Settings));
    auto &spriteFpsBar = coordinator.getComponent<Sprite>(FpsBar);
    spriteFpsBar.sprite.setPosition({1077 *windowScale.x, 301 * windowScale. y});
    Entity FpsBarPointer = coordinator.createEntity();
    coordinator.addComponent<Sprite>(FpsBarPointer, createSprite("data/sprite/barPointer.png", Phase::Settings));
    coordinator.addComponent<Bar>(FpsBarPointer, {1081, 1673, 0, 144, 20});
    coordinator.addComponent<Text>(FpsBarPointer, {sf::Text(), "144%", Phase::Settings, 0});
    auto &spriteFpsBarPointer = coordinator.getComponent<Sprite>(FpsBarPointer);
    spriteFpsBarPointer.sprite.setPosition({1673 *windowScale.x, 282 * windowScale. y});
    auto &textFpsBarPointer = coordinator.getComponent<Text>(FpsBarPointer);
    textFpsBarPointer._sftext.setPosition({1734 *windowScale.x, 307 * windowScale. y});
    textFpsBarPointer._sftext.setFillColor(sf::Color::White);
    textFpsBarPointer._sftext.setStyle(sf::Text::Bold);

    Entity SoundText = coordinator.createEntity();
    coordinator.addComponent<Text>(SoundText, {sf::Text(), "Sound", Phase::Settings, 0});
    auto &SoundTextText = coordinator.getComponent<Text>(SoundText);
    SoundTextText._sftext.setPosition({1350 * windowScale.x, 436 * windowScale.y});
    SoundTextText._sftext.setFillColor(sf::Color::White);
    SoundTextText._sftext.setStyle(sf::Text::Bold);
    Entity SoundBar = coordinator.createEntity();
    coordinator.addComponent<Sprite>(SoundBar, createSprite("data/sprite/bar.png", Phase::Settings));
    auto &spriteSoundBar = coordinator.getComponent<Sprite>(SoundBar);
    spriteSoundBar.sprite.setPosition({1077 *windowScale.x, 498 * windowScale. y});
    Entity SoundBarPointer = coordinator.createEntity();
    coordinator.addComponent<Sprite>(SoundBarPointer, createSprite("data/sprite/barPointer.png", Phase::Settings));
    coordinator.addComponent<Bar>(SoundBarPointer, {(1081), 1673, 1, 100, 0});
    coordinator.addComponent<Text>(SoundBarPointer, {sf::Text(), "50%", Phase::Settings, 0});
    auto &spriteSoundBarPointer = coordinator.getComponent<Sprite>(SoundBarPointer);
    spriteSoundBarPointer.sprite.setPosition({1377 *windowScale.x, 478 * windowScale. y});
    auto &textSoundBarPointer = coordinator.getComponent<Text>(SoundBarPointer);
    textSoundBarPointer._sftext.setPosition({1734 *windowScale.x, 509 * windowScale. y});
    textSoundBarPointer._sftext.setFillColor(sf::Color::White);
    textSoundBarPointer._sftext.setStyle(sf::Text::Bold);

    Entity ReturnButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(ReturnButton, createSprite("data/sprite/return.png", Phase::Settings));
    coordinator.addComponent<Clickable>(ReturnButton, {returnHomeFromSettings});
    auto &ReturnButtonSprite = coordinator.getComponent<Sprite>(ReturnButton);
    ReturnButtonSprite.sprite.setPosition({48 * windowScale.x, 902 * windowScale.y});
}

void initChooseGame(Coordinator &coordinator)
{
    Entity background = coordinator.createEntity();
    coordinator.addComponent<Sprite>(background, createSprite("data/sprite/background.jpg", Phase::ChooseGame));

    Entity joinButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(joinButton, createSprite("data/sprite/joingame.png", Phase::ChooseGame));
    coordinator.addComponent<Clickable>(joinButton, {joinGame});
    auto &joinSprite = coordinator.getComponent<Sprite>(joinButton);
    joinSprite.sprite.setPosition({700 * windowScale.x, 280 * windowScale.y});

    Entity ReturnButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(ReturnButton, createSprite("data/sprite/return.png", Phase::ChooseGame));
    coordinator.addComponent<Clickable>(ReturnButton, {returnHomeFromChooseGame});
    auto &ReturnButtonSprite = coordinator.getComponent<Sprite>(ReturnButton);
    ReturnButtonSprite.sprite.setPosition({48 * windowScale.x, 902 * windowScale.y});

    Entity CreateButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(CreateButton, createSprite("data/sprite/creategame.png", Phase::ChooseGame));
    coordinator.addComponent<Clickable>(CreateButton, {createGame});
    auto &createSprite = coordinator.getComponent<Sprite>(CreateButton);
    createSprite.sprite.setPosition({700 * windowScale.x, 427 * windowScale.y});
}

void initJoinGame(Coordinator &coordinator)
{
    
    Entity background = coordinator.createEntity();
    coordinator.addComponent<Sprite>(background,createSprite("data/sprite/background.jpg", Phase::JoinGame));
    
    Entity GameId = coordinator.createEntity();
    coordinator.addComponent<Sprite>(GameId, createSprite("data/sprite/gameid.png", Phase::JoinGame));
    coordinator.addComponent<Clickable>(GameId, {});
    coordinator.addComponent<Text>(GameId, {sf::Text(), "", Phase::JoinGame, 4, 0, 0, 1});
    auto &GameIdText = coordinator.getComponent<Text>(GameId);
    GameIdText._sftext.setPosition({1030 * windowScale.x, 306 * windowScale.y});
    GameIdText._sftext.setFillColor(sf::Color::Black);
    GameIdText._sftext.setStyle(sf::Text::Bold);
    GameIdText._sftext.setCharacterSize(50);
    auto &spriteMovingRight = coordinator.getComponent<Sprite>(GameId);
    spriteMovingRight.sprite.setPosition({700 * windowScale.x, 280 * windowScale.y});
    
    Entity Join = coordinator.createEntity();
    coordinator.addComponent<Sprite>(Join, createSprite("data/sprite/join.png", Phase::JoinGame));
    coordinator.addComponent<Clickable>(Join, {joinToJoinId});
    auto &spriteJoin = coordinator.getComponent<Sprite>(Join);
    spriteJoin.sprite.setPosition({700 * windowScale.x, 427 * windowScale.y});

    Entity ReturnButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(ReturnButton, createSprite("data/sprite/return.png", Phase::JoinGame));
    coordinator.addComponent<Clickable>(ReturnButton, {returnHomeFromJoinGame});
    auto &ReturnButtonSprite = coordinator.getComponent<Sprite>(ReturnButton);
    ReturnButtonSprite.sprite.setPosition({48 * windowScale.x, 902 * windowScale.y});
}

void initCreateGame(Coordinator &coordinator)
{
    Entity background = coordinator.createEntity();
    coordinator.addComponent<Sprite>(background,createSprite("data/sprite/background.jpg", Phase::CreateGame));

    Entity GameId = coordinator.createEntity();
    coordinator.addComponent<Sprite>(GameId, createSprite("data/sprite/gameid.png", Phase::CreateGame));
    coordinator.addComponent<Clickable>(GameId, {});
    coordinator.addComponent<Text>(GameId, {sf::Text(), "", Phase::CreateGame, 4, 0, 0, 4});
    auto &GameIdText = coordinator.getComponent<Text>(GameId);
    GameIdText._sftext.setPosition({1030 * windowScale.x, 306 * windowScale.y});
    GameIdText._sftext.setFillColor(sf::Color::Black);
    GameIdText._sftext.setStyle(sf::Text::Bold);
    GameIdText._sftext.setCharacterSize(50);
    auto &spriteMovingRight = coordinator.getComponent<Sprite>(GameId);
    spriteMovingRight.sprite.setPosition({700 * windowScale.x, 280 * windowScale.y});
    
    Entity Join = coordinator.createEntity();
    coordinator.addComponent<Sprite>(Join, createSprite("data/sprite/create.png", Phase::CreateGame));
    coordinator.addComponent<Clickable>(Join, {createToGameId});
    auto &spriteJoin = coordinator.getComponent<Sprite>(Join);
    spriteJoin.sprite.setPosition({700 * windowScale.x, 427 * windowScale.y});

    Entity ReturnButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(ReturnButton, createSprite("data/sprite/return.png", Phase::CreateGame));
    coordinator.addComponent<Clickable>(ReturnButton, {returnHomeFromCreateGame});
    auto &ReturnButtonSprite = coordinator.getComponent<Sprite>(ReturnButton);
    ReturnButtonSprite.sprite.setPosition({48 * windowScale.x, 902 * windowScale.y});
}

void initConnect(Coordinator &coordinator)
{
    Entity background = coordinator.createEntity();
    coordinator.addComponent<Sprite>(background, createSprite("data/sprite/background.jpg", Phase::Connect));

    Entity IpModif = coordinator.createEntity();
    coordinator.addComponent<Sprite>(IpModif, createSprite("data/sprite/ip.png", Phase::Connect));
    coordinator.addComponent<Clickable>(IpModif, {});
    coordinator.addComponent<Text>(IpModif, {sf::Text(), "", Phase::Connect, 16, 0, 0, 2});
    auto &IpModifText = coordinator.getComponent<Text>(IpModif);
    IpModifText._sftext.setPosition({870 * windowScale.x, 306 * windowScale.y});
    IpModifText._sftext.setFillColor(sf::Color::Black);
    IpModifText._sftext.setStyle(sf::Text::Bold);
    IpModifText._sftext.setCharacterSize(50);
    auto &spriteMovingRight = coordinator.getComponent<Sprite>(IpModif);
    spriteMovingRight.sprite.setPosition({700 * windowScale.x, 280 * windowScale.y});

    Entity PortModif = coordinator.createEntity();
    coordinator.addComponent<Sprite>(PortModif, createSprite("data/sprite/port.png", Phase::Connect));
    coordinator.addComponent<Clickable>(PortModif, {});
    coordinator.addComponent<Text>(PortModif, {sf::Text(), "", Phase::Connect, 4, 0, 0, 3});
    auto &PortModifText = coordinator.getComponent<Text>(PortModif);
    PortModifText._sftext.setPosition({978 * windowScale.x, 453 * windowScale.y});
    PortModifText._sftext.setFillColor(sf::Color::Black);
    PortModifText._sftext.setStyle(sf::Text::Bold);
    PortModifText._sftext.setCharacterSize(50);
    auto &spritePortModif = coordinator.getComponent<Sprite>(PortModif);
    spritePortModif.sprite.setPosition({700 * windowScale.x, 427 * windowScale.y});

    Entity Join = coordinator.createEntity();
    coordinator.addComponent<Sprite>(Join, createSprite("data/sprite/bigconnectbutton.png", Phase::Connect));
    coordinator.addComponent<Clickable>(Join, {goConnection});
    auto &spriteJoin = coordinator.getComponent<Sprite>(Join);
    spriteJoin.sprite.setPosition({700 * windowScale.x, 574 * windowScale.y});

    Entity ReturnButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(ReturnButton, createSprite("data/sprite/return.png", Phase::Connect));
    coordinator.addComponent<Clickable>(ReturnButton, {returnHomeFromConnect});
    auto &ReturnButtonSprite = coordinator.getComponent<Sprite>(ReturnButton);
    ReturnButtonSprite.sprite.setPosition({48 * windowScale.x, 902 * windowScale.y});
}

void initLobby(Coordinator &coordinator)
{
        // Create parallaxe
    Entity parallaxe = coordinator.createEntity();
    coordinator.addComponent<Sprite>(parallaxe, createSprite("data/sprite/parallaxe.png", Phase::LobbyAndPlay));
    coordinator.addComponent<ParallaxeComp>(parallaxe, {1});

    Entity launch = coordinator.createEntity();
    coordinator.addComponent<Text>(launch, {sf::Text(), "Press L to launch the game", Phase::Lobby, 200});
    auto &launchText = coordinator.getComponent<Text>(launch);
    launchText._sftext.setPosition({520 * windowScale.x, 930 * windowScale.y});
    launchText._sftext.setFillColor(sf::Color(200, 200, 200, 255));
    launchText._sftext.setStyle(sf::Text::Bold);
    launchText._sftext.setCharacterSize(70);

    Entity gameId = coordinator.createEntity();
    coordinator.addComponent<Text>(gameId, {sf::Text(), "Game ID: ", Phase::Lobby, 200});
    auto &gameIdText = coordinator.getComponent<Text>(gameId);
    gameIdText._sftext.setPosition({40 * windowScale.x, 20 * windowScale.y});
    gameIdText._sftext.setFillColor(sf::Color(200, 200, 200, 255));
    gameIdText._sftext.setStyle(sf::Text::Bold);
    gameIdText._sftext.setCharacterSize(70);
}

void initScore(Coordinator &coordinator)
{
    Entity background = coordinator.createEntity();
    coordinator.addComponent<Sprite>(background, createSprite("data/sprite/background.jpg", Phase::Score));

    Entity score = coordinator.createEntity();
    coordinator.addComponent<Sprite>(score, createSprite("data/sprite/emptybox.png", Phase::Score));
    coordinator.addComponent<Text>(score, {sf::Text(), "Score :", Phase::Score, 0});
    auto &scoreSprite = coordinator.getComponent<Sprite>(score);
    scoreSprite.sprite.setPosition({679 *windowScale.x, 154 *windowScale.y});
    auto &scoreText = coordinator.getComponent<Text>(score);
    scoreText._sftext.setPosition({730 *windowScale.x, 177 *windowScale.y});
    scoreText._sftext.setFillColor(sf::Color::Black);
    scoreText._sftext.setStyle(sf::Text::Bold);
    scoreText._sftext.setCharacterSize(50);
    coordinator._score.first = score;

    Entity ReturnButton = coordinator.createEntity();
    coordinator.addComponent<Sprite>(ReturnButton, createSprite("data/sprite/return.png", Phase::Score));
    coordinator.addComponent<Clickable>(ReturnButton, {returnHomeFromScore});
    auto &ReturnButtonSprite = coordinator.getComponent<Sprite>(ReturnButton);
    ReturnButtonSprite.sprite.setPosition({48 * windowScale.x, 902 * windowScale.y});
}