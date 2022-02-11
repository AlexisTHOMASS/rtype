/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** GameNetwork
*/

#include "GameNetwork.hpp"
#include <thread>

GameNetwork::GameNetwork(asio::io_context& io_context, std::string ip, std::string port) : _socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)))
{
	asio::ip::udp::resolver resolver(io_context);
	asio::ip::udp::resolver::query query(asio::ip::udp::v4(), ip, port);

	this->_data = new char[MSG_MAX_LEN];
	this->_tmp = new char[MSG_MAX_LEN];
	this->_empty = new char[MSG_MAX_LEN];
	std::memset(this->_empty, 0, MSG_MAX_LEN);
	this->_endpoint = *(resolver.resolve(query));
	this->__receive();
}

char* GameNetwork::getData(void)
{
	if (_fullData.size() == 0)
		return this->_empty;
	memset(this->_tmp, 0, MSG_MAX_LEN);
	std::memcpy(this->_tmp, this->_fullData.front(), MSG_MAX_LEN);
	delete [] this->_fullData.front();
	this->_fullData.pop();

	return this->_tmp;
}

void GameNetwork::__receive(void)
{
	this->_socket.async_receive_from(
		asio::buffer(this->_data, MSG_MAX_LEN),
		this->_endpoint,
		[this](std::error_code ec, std::size_t bytes_recvd) {
			if (!ec && bytes_recvd > 0)
				this->__handleReceive(this->_data);
			else
				this->__receive();
		}
	);
}

void GameNetwork::__handleReceive(char *data)
{
	int prot = mergeData::getProtocol(data);
	if (prot != 0) {
		char *storedData = new char[MSG_MAX_LEN];
		std::memcpy(storedData, data, MSG_MAX_LEN);
		_fullData.push(storedData);
	}
	std::memset(_data, 0, MSG_MAX_LEN);
	this->__receive();
}

void GameNetwork::write(char *data)
{
	this->_socket.send_to(asio::buffer(data, MSG_MAX_LEN), this->_endpoint);
}

GameNetwork::~GameNetwork()
{
	delete [] _tmp;
	delete [] _empty;
}
