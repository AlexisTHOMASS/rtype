/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Network
*/

#include "Network.hpp"

Network::Network(asio::io_context &io_context, const char* host, const char* port) : _io_context(io_context), _socket(asio::ip::tcp::socket(io_context))
{
	this->__init(host, port);
}

void Network::__init(const char* host, const char* port)
{
	asio::ip::tcp::resolver resolver(this->_io_context);
	asio::connect(this->_socket, resolver.resolve(host, port));
}

std::string Network::createServer(unsigned short port)
{
	char* msg = mergeData::mergeBinaries<unsigned int>(ServerManagerProtocol::CREATE_SERVER, port);
	char* response = this->write(msg, 4 + sizeof(unsigned int));
	unsigned int newPort = mergeData::unPack<unsigned int>(response).second;
	delete [] response;

	return(std::to_string(newPort));
}

char *Network::write(void* data, size_t size)
{
	std::error_code ec;
	char *response = new char[MSG_MAX_LEN];

	size_t write_size = asio::write(this->_socket, asio::buffer(data, size));
	if (write_size <= 0)
		return ((char*)"Error: failed to write to socket");
	this->_socket.read_some(asio::buffer(response, MSG_MAX_LEN));
	return (response);
}

Network::~Network()
{
	this->_socket.close();
}
