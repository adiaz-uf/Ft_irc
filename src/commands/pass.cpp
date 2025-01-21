/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:41:53 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/21 10:17:57 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommandHandler.hpp"

/*
PASS <password>
*/

void IRCCommandHandler::pass(std::vector<std::string> command, Server &server, Client &client)
{
	int			clientFd		= client.getSocket();
	std::string	nick	= client.getNickname();
	
	if (client.isAuthenticated())
		return (server.sendMessageToClient(ERR_ALREADYREGISTERED(nick) + "\r\n", clientFd));
    else if (command.size() < 2)
		return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, "PASS") + "\r\n", clientFd));
	std::string	passwordClient = command[1];
	if (passwordClient != server.getPassword())
	{ 
		server.sendMessageToClient(ERR_PASSWDMISMATCH(nick), clientFd);
		server.disconnectClient(clientFd);
		return ;
	}
	client.setPassPos();
}
