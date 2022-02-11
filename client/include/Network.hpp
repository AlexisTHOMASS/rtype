/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <asio.hpp>
#include <iostream>

#include "MergeData.hpp"
#include "ServerProtocol.hpp"

class Network
{
	public:
		Network(asio::io_context &io_context, const char* host, const char* port);
		~Network();

	public:
		char *write(void* data, size_t size);
		std::string createServer(unsigned short port);

	private:
		void __init(const char* host, const char* port);

	private:
		asio::io_context& _io_context;
		asio::ip::tcp::socket _socket;
};

#endif /* !NETWORK_HPP_ */
