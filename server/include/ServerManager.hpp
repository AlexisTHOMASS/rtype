/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** ServerManager
*/

#ifndef SERVERMANAGER_HPP_
#define SERVERMANAGER_HPP_

#include <asio.hpp>
#include <iostream>

#include "ClientConnection.hpp"
#include "ServerProtocol.hpp"

class ServerManager
{
	public:
		ServerManager(asio::io_context &io_context, unsigned short port);
		~ServerManager();

	private:
		void __startAccept(void);
		void __handleAccept(ClientConnection* client_connection);

	private:
		asio::io_context &_io_context;
		asio::ip::tcp::acceptor _acceptor;
};

#endif /* !SERVERMANAGER_HPP_ */
