/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:48 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/02/13 11:48:15 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"


/* 
KICK:  Parameters: <channel> <user> *( "," <user> ) [<comment>]
*/
void	IRCCommandHandler::kick(std::vector<std::string> command, Server &server, Client &client)
{
	int clientFd = client.getSocket();
	const std::string nick = client.getNickname();
	if (command.size() < 3)
		return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, "KICK"), clientFd));
	Channel *channel = server.getChannel(command[1]);
	if (!server.isValidChannel(command[1]))
		server.sendMessageToClient(ERR_NOSUCHCHANNEL(client.getUsername() , command[1]), clientFd);
	else if (!channel->isMember(clientFd))
		server.sendMessageToClient(ERR_NOTONCHANNEL(nick, channel->getName()), clientFd);
	else if (channel->getMember(command[2]) == NULL || !channel->isMember(channel->getMember(command[2])->getSocket()))
		server.sendMessageToClient(ERR_USERNOTINCHANNEL(client.getUsername(), nick, channel->getName()), clientFd);
    else if (!channel->isOperator(clientFd))
		server.sendMessageToClient(ERR_CHANOPRIVSNEEDED(nick, channel->getName()), clientFd);
	else
	{
		int socket = channel->getMember(command[2])->getSocket();
		if (command.size() > 3)
		{
			std::string message = aggregate(command, 3);
			if (!message.empty() && message[0] == ':')
				message.erase(0, 1);
			channel->broadcastMessage(KICK_LOG((nick), command[2], command[1], message), 0);
		}
		else if (command.size() == 3)
			channel->broadcastMessage(KICK_LOG((nick), command[2], command[1], "No reason"), 0);
		channel->deleteMember(socket);
		if (channel->userCount() == 0)
        	server.deleteChannel(toUpperCase(command[1]));
	}
}
