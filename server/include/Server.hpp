/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <asio.hpp>
#include <iostream>
#include <stdbool.h>
#include <queue>

#include "MergeData.hpp"
#include "ServerProtocol.hpp"

class Server {
	public:
		Server(asio::io_context &io_context, unsigned short port);
		~Server();

		char *getData();

	private:
		void __start(void);
		void __receive(void);
		void __gameLoop();
		void __writeToAll(char* data, std::size_t size);
		bool __isConnectionNew(asio::ip::udp::endpoint endpoint);
		void __handleReceive(char* data, asio::ip::udp::endpoint endpoint);
		void __writeToSender(asio::ip::udp::endpoint endpoint, char* data, std::size_t size);

	private:
		bool _close;
		char* _data;
		std::queue<char *> _queueData;
		unsigned short _nb_connection;
		asio::ip::udp::socket _socket;
		asio::ip::udp::endpoint _sender_endpoint;
		std::vector<asio::ip::udp::endpoint> _endpoint_list;
};

#endif /* !SERVER_HPP_ */