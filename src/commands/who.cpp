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

    std::cout << "ENTERING 1" << std::endl;
    if (command.size() < 2)                                             return /* NOT ENOUGH PARAMS */;
    std::cout << "ENTERING 2" << std::endl;

    if (!server.isValidChannel(command[1]))                             return /* NOT VALID CHANNEL */;
    std::cout << "ENTERING 3" << std::endl;

    Channel *channel = server.getChannel(command[1]);

    if (!channel->isMember(client.getSocket()))                         return /* NOT IN CHANNEL */;
    std::cout << "ENTERING 4" << std::endl;

    std::string is_operator;
    for (std::map<int, Client*>::iterator it = channel->getMembers()->begin(); it != channel->getMembers()->end(); it++)
    {
        std::cout << "ENTERING 5" << std::endl;
        is_operator = EMPTY;
        if (channel->isOperator((*it).first))
            is_operator = OPERTATOR;
        server.sendMessageToClient(WHO_ARE_YOU( 
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
    std::cout << WHO_END(client.getNickname(), channel->getName()) << std::endl;
    server.sendMessageToClient(WHO_END(client.getNickname(), channel->getName()), client.getSocket());
}
