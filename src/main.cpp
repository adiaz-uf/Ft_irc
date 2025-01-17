/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:24 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/17 07:25:25 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "Server.hpp"

int main(int argc, char **argv)
{
	int			port;
	std::string	password;

	if (argc != 3)
		return (std::cerr << "Usage: ./ircserv <port> <password>" << std::endl, 1);
	std::stringstream ss(argv[1]);
	ss >> port;
	password = argv[2];
	try
	{
		Server server(port, password);
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return 0;
}
