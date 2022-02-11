/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Server
*/

#include "Server.hpp"
#include <SFML/Graphics.hpp>
#include "Coordinator.hpp"
#include "Phase.hpp"
#include "init.hpp"
#include "Input.hpp"
#include "MergeData.hpp"
#include "sfmlFunc.hpp"
#include "Motion.hpp"
#include "Ship.hpp"
#include "EntityObject.hpp"
#include <map>
#include "ServerProtocol.hpp"

sf::Vector2f windowScale;

Server::Server(asio::io_context &io_context, unsigned short port) : _socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
	this->_nb_connection = 0;
	this->_close = false;
	this->_data = new char[MSG_MAX_LEN];
	this->__start();
}

void Server::__start(void)
{
	std::thread(&Server::__gameLoop, this).detach();
	this->__receive();
}

void Server::__gameLoop()
{
	Coordinator coordinator;
	sf::RenderWindow window(sf::VideoMode(960, 540), "R-Type");
	window.setFramerateLimit(60);
	sf::Vector2u winSize = window.getSize();
	// window.close();

	windowScale = {float(winSize.x) / float(WINDOW_WIDTH), float(winSize.y) / float(WINDOW_HEIGHT)};
	coordinator.phase.set(Phase::Lobby, true);
	init(coordinator);

	static auto destroyOutOfScreenSystem = initDestroyOutOfScreenSystem(coordinator, winSize);
	static auto enemyMotionSystem = initEnemyMotionSystem(coordinator);
	static auto createEnemySystem = initCreateEnemySystem(coordinator);
	static auto mouvementSystem = initMouvementSystem(coordinator);
	static auto renderSystem = initRenderSystem(coordinator, &window);
	static auto weaponSystem = initWeaponsSystem(coordinator);
	static auto collideSystem = initCollide(coordinator);
	static auto killEnemySystem = initKillEnemy(coordinator);

	std::map<unsigned short, Entity> _players;
	std::map<Entity, int> _mobs;
	auto timeOut = std::chrono::high_resolution_clock::now();

	while (1) {
		char *data;
		do {
			data = this->getData();
			playerObj po;
			if (std::chrono::duration<float, std::chrono::seconds::period>(std::chrono::high_resolution_clock::now() - timeOut).count() >= 5) {
				std::cerr << "Server time out" << std::endl;
				exit(0);
			}
			if (mergeData::getProtocol(data) != 0)
				timeOut = std::chrono::high_resolution_clock::now();
			if (mergeData::getProtocol(data) == ServerGamePlayProtool::PLAYER_POSITION) {
				this->__writeToAll(data, MSG_MAX_LEN);
				po = mergeData::unPack<playerObj>(data).second;
				if (_players.find(po.id) == _players.end()) {
					Entity pentity = coordinator.createEntity();
					coordinator.addComponent<Motion>(pentity, {sf::Vector2f(0, 0), sf::Vector2f(0, 0)});
					coordinator.addComponent<Sprite>(pentity, createSprite(po.texture, Phase::Play));
					coordinator.addComponent<Ship>(pentity, {true, 0, 0, 3});
					_players.insert({po.id, pentity});
				}
				auto &sprite = coordinator.getComponent<Sprite>(_players.at(po.id));
				sprite.sprite.setPosition({po.pos.x * windowScale.x, po.pos.y * windowScale.y});
			} else if (mergeData::getProtocol(data) == ServerGamePlayProtool::BULLET_PLAYER) {
				this->__writeToAll(data, MSG_MAX_LEN);
				bulletObj bo = mergeData::unPack<bulletObj>(data).second;
				Entity bullet_entity = coordinator.createEntity();
				coordinator.addComponent<Motion>(bullet_entity, {sf::Vector2f(0, 0), sf::Vector2f(0, 0)});
				coordinator.addComponent<Sprite>(bullet_entity, createSprite(bo.texture, Phase::Play));
				coordinator.addComponent<Bullet_Comp>(bullet_entity, {BULLET_DAMAGE::ShitBullet, true});
				auto &motion = coordinator.getComponent<Motion>(bullet_entity);
				auto &sprite = coordinator.getComponent<Sprite>(bullet_entity);
				motion = bo.motion;
				sprite.sprite.setPosition(bo.pos.x * windowScale.x, bo.pos.y * windowScale.y);
			} else if (mergeData::getProtocol(data) == ServerGamePlayProtool::LAUNCH_GAME) {
				coordinator.phase.set(Phase::Play, true);
				coordinator.phase.set(Phase::Lobby, false);
				this->__writeToAll(mergeData::mergeBinaries<char>(ServerGamePlayProtool::LAUNCH_GAME, 0), MSG_MAX_LEN);
			}
		} while (mergeData::getProtocol(data) != 0);
		static int i = 4;
		if (coordinator.phase[Phase::Play]) {
			for (auto const &enemy : createEnemySystem->update()) {
				_mobs[enemy] = i;
				i += 1;
				auto &sprite = coordinator.getComponent<Sprite>(enemy);
				auto &motion = coordinator.getComponent<Motion>(enemy);
				enemyObj eo;
				eo.id = _mobs[enemy];
				eo.motion = motion;
				eo.pos = {sprite.sprite.getPosition().x / windowScale.x, sprite.sprite.getPosition().y / windowScale.y};
				std::strcpy(eo.texture, sprite.path.c_str());
				char *data_enemy = mergeData::mergeBinaries<enemyObj>(ServerGamePlayProtool::ENEMY_POSITION, eo);
				this->__writeToAll(data_enemy, MSG_MAX_LEN);
			}
			for (auto const &enemy : enemyMotionSystem->update()) {
				auto &sprite = coordinator.getComponent<Sprite>(enemy);
				auto &motion = coordinator.getComponent<Motion>(enemy);
				enemyObj eo;
				eo.id = _mobs[enemy];
				eo.motion = motion;
				eo.pos = {sprite.sprite.getPosition().x / windowScale.x, sprite.sprite.getPosition().y / windowScale.y};
				std::strcpy(eo.texture, sprite.path.c_str());
				char *data_enemy = mergeData::mergeBinaries<enemyObj>(ServerGamePlayProtool::ENEMY_POSITION, eo);
				this->__writeToAll(data_enemy, MSG_MAX_LEN);
			}
		}
		for (auto const &bullet_entity : weaponSystem->update()) {
			auto &sprite = coordinator.getComponent<Sprite>(bullet_entity);
			auto &motion = coordinator.getComponent<Motion>(bullet_entity);
			bulletObj bullet_obj;
			bullet_obj.motion = motion;
			bullet_obj.pos = {sprite.sprite.getPosition().x / windowScale.x, sprite.sprite.getPosition().y / windowScale.y};
			std::strcpy(bullet_obj.texture, sprite.path.c_str());
			char *data_enemy = mergeData::mergeBinaries<bulletObj>(ServerGamePlayProtool::BULLET_ENEMY, bullet_obj);
			this->__writeToAll(data_enemy, MSG_MAX_LEN);
		}
		std::vector<Entity> playerDestroyed;
		std::vector<Entity> enemyDestroyed;
		for (auto const &entity_to_destroy : killEnemySystem->update()) {
			if (_mobs.find(entity_to_destroy) != _mobs.end()) {
				auto &sprite = coordinator.getComponent<Sprite>(entity_to_destroy);
				auto &motion = coordinator.getComponent<Motion>(entity_to_destroy);
				enemyObj eo;
				eo.id = _mobs[entity_to_destroy];
				eo.motion = motion;
				eo.pos = {sprite.sprite.getPosition().x / windowScale.x, sprite.sprite.getPosition().y / windowScale.y};
				std::strcpy(eo.texture, sprite.path.c_str());
				char *data_enemy = mergeData::mergeBinaries<enemyObj>(ServerGamePlayProtool::ENEMY_POSITION, eo);
				enemyDestroyed.push_back(entity_to_destroy);
				for (size_t i = 0; i < 3; i++)
					this->__writeToAll(data_enemy, MSG_MAX_LEN);
			}
			for (auto &it : _players) {
				if (it.second == entity_to_destroy) {
					char *data_death_id = mergeData::mergeBinaries<uint16_t>(ServerGamePlayProtool::PLAYER_DEATH, it.first);
					playerDestroyed.push_back(entity_to_destroy);
					for (size_t i = 0; i < 5; i++)
						this->__writeToAll(data_death_id, MSG_MAX_LEN);
					break;
				}
			}
		}
		for (Entity d : playerDestroyed) {
			coordinator.destroyEntity(d);
			this->_nb_connection -= 1;
		}
		for (Entity d : enemyDestroyed) {
			auto &ship = coordinator.getComponent<Ship>(d);
			coordinator._score.second += ship.difficulty;
			coordinator.destroyEntity(d);
		}
		if (this->_nb_connection == 0) {
			char *endGame = mergeData::mergeBinaries<int>(ServerGamePlayProtool::END_GAME, int(coordinator._score.second));
			for (size_t i = 0; i < 5; i++)
				this->__writeToAll(endGame, MSG_MAX_LEN);
			std::exit(0);
		}

		renderSystem->update();

		destroyOutOfScreenSystem->update();
		mouvementSystem->update();
		collideSystem->update(mouvementSystem->_entities);
		window.display();
		window.clear();
	}
}

char *Server::getData()
{
	char *tmp = new char[MSG_MAX_LEN];
	std::memset(tmp, 0, MSG_MAX_LEN);
	if (!_queueData.size())
		return tmp;
	std::memcpy(tmp, _queueData.front(), MSG_MAX_LEN);
	delete [] _queueData.front();
	_queueData.pop();
	return tmp;
}

void Server::__receive(void)
{
	this->_socket.async_receive_from(
		asio::buffer(this->_data, MSG_MAX_LEN),
		this->_sender_endpoint,
		[this](std::error_code ec, std::size_t bytes_recvd) {
			if (!ec && bytes_recvd > 0)
				this->__handleReceive(this->_data, this->_sender_endpoint);
			else
				this->__receive();
		}
	);
}

bool Server::__isConnectionNew(asio::ip::udp::endpoint endpoint)
{
	for (auto it : this->_endpoint_list)
		if (it == endpoint)
			return false;
	return true;
}

void Server::__handleReceive(char* data, asio::ip::udp::endpoint endpoint)
{
	if (this->__isConnectionNew(endpoint) && this->_nb_connection < 4) {
		this->_endpoint_list.push_back(endpoint);
		this->_nb_connection += 1;
		this->__writeToSender(endpoint, mergeData::mergeBinaries<int>(ServerGamePlayProtool::PLAYER_ID, this->_nb_connection), 1 + sizeof(int));
		data = this->getData();
		this->__receive();
	}
	char *tmp = new char[MSG_MAX_LEN];
	std::memcpy(tmp, data, MSG_MAX_LEN);
	_queueData.push(tmp);
	std::memset(data, 0, MSG_MAX_LEN);
	this->__receive();
}

void Server::__writeToSender(asio::ip::udp::endpoint endpoint, char* data, std::size_t size)
{
	this->_socket.send_to(asio::buffer(data, size), endpoint);
}
;
void Server::__writeToAll(char* data, std::size_t size)
{
	for (auto it : this->_endpoint_list) {
		try {
			this->__writeToSender(it, data, size);
		} catch(const std::exception& e) {}
		
	}
}

Server::~Server()
{
}
