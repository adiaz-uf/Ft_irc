/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:39 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/21 10:19:23 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"


/*
Command: PRIVMSG -> Parameters: <target>{,<target>} <text to be sent>
*/

void IRCCommandHandler::privmsg(std::vector<std::string> command, Server &server, Client &client)
{    
	std::string message;
	int			clientFd = client.getSocket();
	std::string nick = client.getNickname();
	std::string user = client.getUsername();
	
    if (command.size() < 3)
		return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, "PRIVMSG"), clientFd));
	for (size_t i = 2; i < command.size(); ++i)
	{
		if (i != 2)
			message += " ";
		message += command[i];
	}
	if (!message.empty() && message[0] == ':')
		message.erase(0, 1);
    if (server.isValidChannel(command[1]))
        server.getChannel(command[1])->broadcastMessage(PRIVMSG_LOG((nick), user, command[1], message), clientFd);
    else if (!server.isValidClient(command[1]))
		server.sendMessageToClient(ERR_NOSUCHNICK(nick, command[1]), clientFd);
    else
		server.sendMessageToClient(PRIVMSG_LOG((nick), user, command[1], message), server.getClient(command[1])->getSocket());
}
