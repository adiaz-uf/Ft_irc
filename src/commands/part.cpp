/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:10 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/21 10:17:43 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommandHandler.hpp"

void IRCCommandHandler::part(std::vector<std::string> command, Server &server, Client &client)
{
    std::string nick    = client.getNickname();
    int         fd      = client.getSocket();

    if (command.size() < 3)                              
        return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, command[0]), fd));
    if (!server.isValidChannel(command[1]))              
        return (server.sendMessageToClient(ERR_NOSUCHCHANNEL (nick, command[1]), fd));
    Channel *channel     = server.getChannel(command[1]);
    if (!channel->isMember(fd))                          
        return (server.sendMessageToClient(ERR_NOTONCHANNEL  (nick, command[1]), fd));
    channel->broadcastMessage(PART_LOG(nick, client.getUsername(), command[1]), 0);
    channel->removeMember(fd);
    if (channel->isOperator(fd))
        channel->removeOperator(fd);
}
