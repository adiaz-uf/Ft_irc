/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:41:52 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/21 10:23:15 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"

void IRCCommandHandler::who(std::vector<std::string> command, Server &server, Client &client)
{
    int             clientFd    = client.getSocket();
    std::string     nick        = client.getNickname();

    if (command.size() < 2)                                         
        return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, "WHO"), clientFd));
    if (!server.isValidChannel(command[1]))                            
        return (server.sendMessageToClient(ERR_NOSUCHCHANNEL(command[1], server.getChannel(command[1])->getName()), clientFd));

    Channel *channel = server.getChannel(command[1]);
    if (!channel->isMember(client.getSocket()))                         
        return (server.sendMessageToClient(ERR_NOTONCHANNEL(nick, server.getChannel(command[1])->getName()), clientFd));

    std::string is_operator;
    std::string names = "";

    for (std::map<int, Client*>::iterator it = channel->getMembers()->begin(); it != channel->getMembers()->end(); it++)
    {
        is_operator = EMPTY;
        if (channel->isOperator((*it).first))
        {
            is_operator = OPERTATOR;
            names += '@';
        }
        names.append((*it).second->getNickname());
        names += ' ';
    }
    server.sendMessageToClient(RPL_NAMEREPLY(nick, channel->getName(), names), client.getSocket());
}
