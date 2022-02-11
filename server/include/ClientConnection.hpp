/*
** EPITECH PROJECT, 2021
** test_server_client_asio
** File description:
** Session
*/


#ifndef SESSION_HPP_
#define SESSION_HPP_

#include <asio.hpp>
#include <iostream>

#include "Server.hpp"
#include "MergeData.hpp"
#include "ServerProtocol.hpp"

class ClientConnection
{
  public:
		ClientConnection(asio::io_context &io_context);
    ~ClientConnection();

	public:
		void start(void);
		asio::ip::tcp::socket* getSocket(void);

  private:
    void __handleRead(void);
		void __createServer(unsigned short port);
    void __handleMessage(char *data);
    void __write(void* data, size_t size);

  private:
    char *_data;
    asio::ip::tcp::socket _socket;
		std::vector<Server*> _server_list;
		asio::io_context &_io_context(asio::io_context io_context);
};

#endif /* !SESSION_HPP_ */
