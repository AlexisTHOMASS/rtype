/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** ClientConnection
*/

#include "ClientConnection.hpp"

ClientConnection::ClientConnection(asio::io_context &io_context) : _socket(io_context)
{
	this->_data = new char[MSG_MAX_LEN];
}

void ClientConnection::start(void)
{
	this->__handleRead();
}

asio::ip::tcp::socket* ClientConnection::getSocket(void)
{
	return (&this->_socket);
}

void ClientConnection::__createServer(unsigned short port)
{
	if (fork() == 0) {
		try {
			asio::io_context io_context;
			Server server(io_context, port);
			this->__write(mergeData::mergeBinaries<unsigned int>(ServerManagerProtocol::SERVER_CREATED, port), 4 + sizeof(int));
			io_context.run();
			return;
		}
		catch (std::exception &e) {
			this->__write((void*)&ServerManagerProtocol::SERVER_CREATION_FAILED, sizeof(ServerManagerProtocol::SERVER_CREATION_FAILED));
			return;
		}
	}
}

void ClientConnection::__handleRead(void)
{
	this->_socket.async_read_some(
		asio::buffer(this->_data, MSG_MAX_LEN),
		std::bind(&ClientConnection::__handleMessage, this, this->_data)
	);
}

void ClientConnection::__write(void* data, size_t size)
{
	asio::async_write(
		this->_socket,
		asio::buffer(data, size),
		std::bind(&ClientConnection::__handleRead, this)
	);
}

void ClientConnection::__handleMessage(char* data)
{
	std::pair<int, int> msg = mergeData::unPack<int>(data);

	if (msg.first == ServerManagerProtocol::CONNECTION)
		this->__write((void*)&ServerManagerProtocol::CONNECTION_ACCEPTED, sizeof(ServerManagerProtocol::CONNECTION_ACCEPTED));
	else if (msg.first == ServerManagerProtocol::CREATE_SERVER) {
		this->__createServer(msg.second);
	}
	else
		this->__write((void*)&ServerManagerProtocol::INVALID_REQUEST, sizeof(ServerManagerProtocol::INVALID_REQUEST));
	this->__handleRead();
}


ClientConnection::~ClientConnection()
{
	this->_socket.close();
	delete this->_data;
}
