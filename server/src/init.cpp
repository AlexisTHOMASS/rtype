/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** init
*/

#include "init.hpp"
#include "Coordinator.hpp"
#include "Sprite.hpp"
#include "Motion.hpp"
#include "Input.hpp"
#include "GestButton.hpp"
#include "Clickable.hpp"
#include "Weapon.hpp"
#include "BulletComp.hpp"
#include "iostream"
#include "DestroyOutOfScreen.hpp"
#include "Ship.hpp"
#include "EnemyMotion.hpp"
#include "Text.hpp"
#include "PrintText.hpp"
#include <SFML/Graphics.hpp>
#include "TextBox.hpp"
#include "Collide.hpp"
#include "KillEnemy.hpp"

#include "Settings.hpp"
#include "Settingsys.hpp"
#include "Bar.hpp"
#include "MovingBar.hpp"

void init(Coordinator &coordinator)
{
    coordinator.registerComponent<Motion>();
    coordinator.registerComponent<Input>();
    coordinator.registerComponent<Sprite>();
    coordinator.registerComponent<Clickable>();
    coordinator.registerComponent<Text>();
    coordinator.registerComponent<Weapon>();
    coordinator.registerComponent<Bullet_Comp>();
    coordinator.registerComponent<Ship>();
    coordinator.registerComponent<SettingsStr>();
    coordinator.registerComponent<Bar>();
}

std::shared_ptr<Render> initRenderSystem(Coordinator &coordinator, sf::RenderWindow *window)
{
    Signature sig;
    auto renderSystem = coordinator.registerSystem<Render>();

    sig.set(coordinator.getComponentType<Sprite>());
    coordinator.setSystemSignature<Render>(sig);
    renderSystem->init(&coordinator, window);

    return (renderSystem);
}

std::shared_ptr<Mouvement> initMouvementSystem(Coordinator &coordinator)
{
    Signature sig;
    auto mouvementSystem = coordinator.registerSystem<Mouvement>();

    sig.set(coordinator.getComponentType<Motion>());
    sig.set(coordinator.getComponentType<Sprite>());
    coordinator.setSystemSignature<Mouvement>(sig);
    mouvementSystem->init(&coordinator);

    return (mouvementSystem);
}


std::shared_ptr<DestroyOutOfScreen> initDestroyOutOfScreenSystem(Coordinator &coordinator,  sf::Vector2u window)
{
    Signature sig;
    auto DestroyOutOfScreenSystem = coordinator.registerSystem<DestroyOutOfScreen>();

    sig.set(coordinator.getComponentType<Sprite>());
    sig.set(coordinator.getComponentType<Motion>());
    coordinator.setSystemSignature<DestroyOutOfScreen>(sig);
    DestroyOutOfScreenSystem->init(&coordinator, window);

    return (DestroyOutOfScreenSystem);
}

std::shared_ptr<Weapons> initWeaponsSystem(Coordinator &coordinator)
{

    Signature sig;
    auto WeaponsSystem = coordinator.registerSystem<Weapons>();

    sig.set(coordinator.getComponentType<Weapon>());
    coordinator.setSystemSignature<Weapons>(sig);
    WeaponsSystem->init(&coordinator);

    return (WeaponsSystem);
}

std::shared_ptr<EnemyMotion> initEnemyMotionSystem(Coordinator &coordinator)
{
    Signature sig;
    auto EnemyMotionSystem = coordinator.registerSystem<EnemyMotion>();

    sig.set(coordinator.getComponentType<Ship>());
    sig.set(coordinator.getComponentType<Motion>());
    sig.set(coordinator.getComponentType<Sprite>());
    coordinator.setSystemSignature<EnemyMotion>(sig);
    EnemyMotionSystem->init(&coordinator);

    return (EnemyMotionSystem);
}

std::shared_ptr<CreateEnemy> initCreateEnemySystem(Coordinator &coordinator)
{
    Signature sig;
    auto createEnemySystem = coordinator.registerSystem<CreateEnemy>();

    sig.set(coordinator.getComponentType<Ship>());
    coordinator.setSystemSignature<CreateEnemy>(sig);
    createEnemySystem->init(&coordinator);

    return (createEnemySystem);
}

std::shared_ptr<Collide> initCollide(Coordinator &coordinator)
{
    Signature sig;
    auto createCollideSystem = coordinator.registerSystem<Collide>();

    sig.set(coordinator.getComponentType<Ship>());
    sig.set(coordinator.getComponentType<Sprite>());
    coordinator.setSystemSignature<Collide>(sig);
    createCollideSystem->init(&coordinator);

    return (createCollideSystem);
}

std::shared_ptr<KillEnemy> initKillEnemy(Coordinator &coordinator)
{
    Signature sig;
    auto createKillEnemySystem = coordinator.registerSystem<KillEnemy>();

    sig.set(coordinator.getComponentType<Ship>());
    sig.set(coordinator.getComponentType<Motion>());
    coordinator.setSystemSignature<KillEnemy>(sig);
    createKillEnemySystem->init(&coordinator);

    return (createKillEnemySystem);
}