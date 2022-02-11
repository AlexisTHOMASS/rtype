/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** ServerManager
*/

#include "ServerManager.hpp"
#include "ClientConnection.hpp"

ServerManager::ServerManager(asio::io_context &io_context, unsigned short port) : _io_context(io_context), _acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
	this->__startAccept();
}

void ServerManager::__startAccept(void)
{
	ClientConnection* client_connection = new ClientConnection(this->_io_context);

	this->_acceptor.async_accept(
		*(client_connection->getSocket()),
		std::bind(&ServerManager::__handleAccept, this, client_connection)
	);
}

void ServerManager::__handleAccept(ClientConnection* client_connection)
{
	client_connection->start();
	this->__startAccept();
}

ServerManager::~ServerManager()
{
}
