/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** init
*/

#ifndef INIT_HPP_
#define INIT_HPP_

#include "Coordinator.hpp"
#include "SFML/Graphics.hpp"
#include "PlayerMotion.hpp"
#include "Mouvement.hpp"
#include "Render.hpp"
#include "GestButton.hpp"
#include "DestroyOutOfScreen.hpp"
#include "PrintText.hpp"
#include "TextBox.hpp"
#include "Weapons.hpp"
#include "EnemyMotion.hpp"
#include "CreateEnemy.hpp"
#include "Collide.hpp"
#include "Settingsys.hpp"
#include "MovingBar.hpp"
#include "KillEnemy.hpp"

void init(Coordinator &coordinator);
std::shared_ptr<Render> initRenderSystem(Coordinator &coordinator, sf::RenderWindow *window);
std::shared_ptr<Mouvement> initMouvementSystem(Coordinator &coordinator);
std::shared_ptr<DestroyOutOfScreen> initDestroyOutOfScreenSystem(Coordinator &coordinator, sf::Vector2u window);
std::shared_ptr<Weapons> initWeaponsSystem(Coordinator &coordinator);
std::shared_ptr<EnemyMotion> initEnemyMotionSystem(Coordinator &coordinator);
std::shared_ptr<CreateEnemy> initCreateEnemySystem(Coordinator &coordinator);
std::shared_ptr<Collide> initCollide(Coordinator &coordinator);
std::shared_ptr<KillEnemy> initKillEnemy(Coordinator &coordinator);

#endif /* !INIT_HPP_ */
