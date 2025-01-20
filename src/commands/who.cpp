/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:41:52 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/18 00:46:24 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

    # include "IRCCommandHandler.hpp"

/*
*/

void IRCCommandHandler::who(std::vector<std::string> command, Server &server, Client &client)
{
    int clientFd = client.getSocket();
    std::string     nick        = client.getNickname();

    if (command.size() < 2)                                         
        return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, "WHO"), clientFd));
    if (!server.isValidChannel(command[1]))                            
        return (server.sendMessageToClient(ERR_NOSUCHCHANNEL(command[1], server.getChannel(command[1])->getName()), clientFd));

    Channel *channel = server.getChannel(command[1]);
    if (!channel->isMember(client.getSocket()))                         
        return (server.sendMessageToClient(ERR_NOTONCHANNEL(nick, server.getChannel(command[1])->getName()), clientFd));

    std::string is_operator;
    for (std::map<int, Client*>::iterator it = channel->getMembers()->begin(); it != channel->getMembers()->end(); it++)
    {
        is_operator = EMPTY;
        if (channel->isOperator((*it).first))
            is_operator = OPERTATOR;
        server.sendMessageToClient(WHO_ENTRY( 
            client.getNickname(),
            channel->getName(), 
            (*it).second->getUsername(), 
            "127.0.0.1",
            "FT_IRCSERV",
            (*it).second->getNickname(),
            is_operator,
            "0",
            "realname"),
            client.getSocket());
    }
    //std::cout << WHO_END(client.getNickname(), channel->getName()) << std::endl;
    server.sendMessageToClient(WHO_END(client.getNickname(), channel->getName()), client.getSocket());
}
