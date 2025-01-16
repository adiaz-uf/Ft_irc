/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:41:53 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/16 11:36:58 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommandHandler.hpp"

/*
The PASS command lets a user provide a connection password to the server. If a 
connection password is required by the server and not provided (or is incorrect),
 the user will not be able to successfully connect. This command cannot be used 
 after connection registration has completed.

PASS <password>
<password>: The password which the server evaluates.

If required by the server, this must be sent before any attempt to register the 
connection is made. In other words, the client sends this 

>>>>before sending the NICK/USER combination. <<<<

It is possible to send multiple PASS commands before 
registering, but only the last one sent is used for verification.

For standard IRC servers, the password must match the one in the server’s 
configuration. Other services (such as bouncers) may require other formats for the
 password which gets evaluated at runtime.

If a client tries to send the PASS command after connection registration has been  
completed, the ERR_ALREADYREGISTRED reply is sent and the command is ignored.

ERR_NEEDMOREPARAMS (461)		[x]
ERR_ALREADYREGISTRED (462)		[x]

*/

void IRCCommandHandler::pass(std::vector<std::string> command, Server &server, Client &client)
{
	int			clientFd		= client.getSocket();
	std::string	nick	= client.getNickname();
	
	if (client.isAuthenticated())
	{
		server.sendMessageToClient(ERR_ALREADYREGISTERED(nick) + "\r\n", clientFd);
		return ;
	}
    else if (command.size() < 2)
	{
		server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, "PASS") + "\r\n", clientFd);
		return ;
	}
	std::string	passwordClient = command[1];
	if (passwordClient != server.getPassword())
	{ 
		server.sendMessageToClient(ERR_PASSWDMISMATCH(nick), clientFd);
		server.disconnectClient(clientFd);
		return ;
	}
	client.setPassPos();
}
