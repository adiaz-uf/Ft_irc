/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:41:52 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/20 12:38:44 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

    # include "IRCCommandHandler.hpp"

/*
*/

void IRCCommandHandler::who(std::vector<std::string> command, Server &server, Client &client)
{

    if (command.size() < 2)                                             return /* NOT ENOUGH PARAMS */;
    if (!server.isValidChannel(command[1]))                             return /* NOT VALID CHANNEL */;
    Channel *channel = server.getChannel(command[1]);

    if (!channel->isMember(client.getSocket()))                         return /* NOT IN CHANNEL */;
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
    server.sendMessageToClient(RPL_NAMEREPLY(client.getNickname(), channel->getName(), names), client.getSocket());
}
