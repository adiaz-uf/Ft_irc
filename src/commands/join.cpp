/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:50 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/17 07:25:51 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"

/*
Command: JOIN: Parameters: <channel>{,<channel>} [<key>{,<key>}]

Command Examples:
- JOIN #foobar                    ; join channel #foobar.
- JOIN #foo,&bar fubar            ; join channel #foo using key "fubar" and &bar using no key.
- JOIN #foo,#bar                  ; join channels #foo and #bar.
Message Examples:
- :WiZ JOIN #Twilight_zone        ; WiZ is joining the channel #Twilight_zone
- :dan-!d@localhost JOIN #test    ; dan- is joining the channel #test

ERR_NEEDMOREPARAMS (461)			[x]
ERR_BADCHANNELKEY (475)				[x]
ERR_INVITEONLYCHAN (473)			[x]
*/


//TODO Channel info on join
void    IRCCommandHandler::join(std::vector<std::string> command, Server &server, Client &client)
{
    std::queue<std::string> channels;
    std::queue<std::string> keys;
	std::string split;              
	int clientFd = client.getSocket();
	bool	permission;
	Channel *channel;

	if (command.size() < 2)
		server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "JOIN"), clientFd);
	std::istringstream ss1(command[1]);
	while (std::getline(ss1, split, ',')) // Separate channels into queue                                                                                                                                                                              
		channels.push(split);
	if (command.size() > 2)
	{
		std::istringstream ss2(command[2]); 
		while (std::getline(ss2, split, ',')) // Separate keys into queue                                                                                                                                                                                  
			keys.push(split);
	}
	std::cout << "Entered the function at least" << std::endl;
	while (!channels.empty())
	{
		permission = ACCEPTED;
		if (!server.isValidChannel(channels.front()))
		{
			server.addChannel(channels.front());
			server.getChannel(channels.front())->makeMember(server, clientFd);
			server.getChannel(channels.front())->broadcastMessage(JOIN_LOG((client.getNickname()), client.getUsername(), channels.front()), 0);
		}
		else
		{
			channel = server.getChannel(channels.front());
			if (channel->isMember(clientFd) == true) 
				permission = DENIED;
			if (permission && (channel->hasMode(KEY_WORD) && (keys.empty() || !channel->checkPassword(keys.front())))) 	
			{
				permission = DENIED;
				server.sendMessageToClient(ERR_BADCHANNELKEY(client.getNickname(), channel->getName()), clientFd);
			}
			if (permission && (channel->hasMode(SIZE_LIMIT) && channel->userCount() >= channel->getUsersLimit())) 		
			{
				permission = DENIED; 
				server.sendMessageToClient(ERR_CHANNELISFULL(client.getNickname(), channel->getName()), clientFd);
			}
			if (permission && (channel->hasMode(INVITE_ONLY) && !channel->isInvited(clientFd))) 						
			{
				permission = DENIED; 
				server.sendMessageToClient(ERR_INVITEONLYCHAN(client.getNickname(), channel->getName()), clientFd);
			}
			if (permission == ACCEPTED)																					
			{
				channel->makeMember(server, clientFd);
				channel->broadcastMessage(JOIN_LOG((client.getNickname()), client.getUsername(), channels.front()), 0);
			}
		}
		if (!keys.empty())
			keys.pop();
		channels.pop();
	}
}
