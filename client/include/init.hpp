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
#include "Parallaxe.hpp"

void init(Coordinator &coordinator);
std::shared_ptr<Render> initRenderSystem(Coordinator &coordinator, sf::RenderWindow *window);
std::shared_ptr<Mouvement> initMouvementSystem(Coordinator &coordinator);
std::shared_ptr<PlayerMotion> initPlayerMotionSystem(Coordinator &coordinator);
std::shared_ptr<GestButton> initGestButtonSystem(Coordinator &coordinator, sf::RenderWindow *windows);
std::shared_ptr<DestroyOutOfScreen> initDestroyOutOfScreenSystem(Coordinator &coordinator,  sf::Vector2u window);
std::shared_ptr<Weapons> initWeaponsSystem(Coordinator &coordinator);
std::shared_ptr<EnemyMotion> initEnemyMotionSystem(Coordinator &coordinator);
std::shared_ptr<CreateEnemy> initCreateEnemySystem(Coordinator &coordinator);
std::shared_ptr<PrintText> initPrintText(Coordinator &coordinator, sf::RenderWindow *window);
std::shared_ptr<TextBox> initTextBox(Coordinator &coordinator, sf::RenderWindow *window);
std::shared_ptr<Collide> initCollide(Coordinator &coordinator);
std::shared_ptr<Settingsys> initSettingsSystem(Coordinator &coordinator);
std::shared_ptr<MovingBar> initMovingBarSystem(Coordinator &coordinator, sf::RenderWindow *window, sf::Sound *sound);
std::shared_ptr<Parallaxe> initParallaxeSystem(Coordinator &coordinator, sf::RenderWindow *window);

#endif /* !INIT_HPP_ */
