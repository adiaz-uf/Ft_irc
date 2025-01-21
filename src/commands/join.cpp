/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:50 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/21 11:34:14 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"

/*
Command: JOIN: Parameters: <channel>{,<channel>} [<key>{,<key>}]
*/

//TODO Channel info on join
void    IRCCommandHandler::join(std::vector<std::string> command, Server &server, Client &client)
{
    std::queue<std::string> channels;
    std::queue<std::string> keys;
	std::string split;              
	int clientFd = client.getSocket();
	std::string nick = client.getNickname();
	bool	permission;
	Channel *channel;

	if (command.size() < 2) 
		return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "JOIN"), clientFd));
	std::istringstream ss1(command[1]);
	while (std::getline(ss1, split, ','))                                                                                                                                                                            
		channels.push(split);
	if (command.size() > 2)
	{
		std::istringstream ss2(command[2]); 
		while (std::getline(ss2, split, ','))                                                                                                                                                                               
			keys.push(split);
	}
	while (!channels.empty())
	{
		permission = ACCEPTED;
		if (!server.isValidChannel(channels.front()))
		{
			server.addChannel(channels.front());
			server.getChannel(channels.front())->makeMember(server, clientFd);
			server.getChannel(channels.front())->broadcastMessage(JOIN_LOG((nick), client.getUsername(), channels.front()), 0);
		}
		else
		{
			channel = server.getChannel(channels.front());
			if (channel->isMember(clientFd) == true) 
				permission = DENIED;
			if (permission && (channel->hasMode(KEY_WORD) && (keys.empty() || !channel->checkPassword(keys.front())))) 	
			{
				permission = DENIED;
				server.sendMessageToClient(ERR_BADCHANNELKEY(nick, channel->getName()), clientFd);
			}
			if (permission && (channel->hasMode(SIZE_LIMIT) && channel->userCount() >= channel->getUsersLimit())) 		
			{
				permission = DENIED; 
				server.sendMessageToClient(ERR_CHANNELISFULL(nick, channel->getName()), clientFd);
			}
			if (permission && (channel->hasMode(INVITE_ONLY) && !channel->isInvited(clientFd))) 						
			{
				permission = DENIED; 
				server.sendMessageToClient(ERR_INVITEONLYCHAN(nick, channel->getName()), clientFd);
			}
			if (permission == ACCEPTED)																					
			{
				channel->makeMember(server, clientFd);
				channel->broadcastMessage(JOIN_LOG((nick), client.getUsername(), channels.front()), 0);
			}
		}
		if (!keys.empty())
			keys.pop();
		channels.pop();
	}
}
