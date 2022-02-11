/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** main
*/

#include <SFML/Graphics.hpp>

#include <asio.hpp>
#include <iostream>
#include "ServerManager.hpp"

void print_help(void)
{
	std::cout << "Usage: ./r-type_server <port>" << std::endl;
}

int main(int ac, char** av)
{
	if (ac != 2) {
		print_help();
		return (0);
	}
  try {
    asio::io_context io_context;
    ServerManager server_manager(io_context, std::stoi(av[1]));
    io_context.run();
  }
  catch (std::exception &e) {
    std::cerr << "Error: could not launch server manager" << std::endl;
    return (84);
  }
  return (0);
}