/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** GameNetwork
*/

#ifndef GAMENETWORK_HPP_
#define GAMENETWORK_HPP_

#include <asio.hpp>
#include <iostream>
#include <queue>

#include "MergeData.hpp"
#include "ServerProtocol.hpp"

static const uint8_t TPS = 60;

class GameNetwork {
	public:
		GameNetwork(asio::io_context &io_context, std::string ip, std::string port);
		~GameNetwork();

	public:
		char* getData(void);
		void write(char* data);

		void __receive(void);

	private:
		void __handleReceive(char* data);

	private:
		std::queue<char*> _fullData;
		char* _data;
		char *_tmp;
		char* _empty;
		asio::ip::udp::socket _socket;
		asio::ip::udp::endpoint _endpoint;
};

#endif /* !GAMENETWORK_HPP_ */
