/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:10 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/17 08:48:58 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommandHandler.hpp"

//    ERR_NOSUCHCHANNEL     (403) [x]
//    ERR_NOTONCHANNEL      (442) [x]
//    ERR_NEEDMOREPARAMS    (461) [x]

void IRCCommandHandler::part(std::vector<std::string> command, Server &server, Client &client)
{
    std::string nick    = client.getNickname();
    int         fd      = client.getSocket();

    if (command.size() < 3)                              return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, command[0]), fd));
    if (!server.isValidChannel(command[1]))              return (server.sendMessageToClient(ERR_NOSUCHCHANNEL (nick, command[1]), fd));
    Channel *channel     = server.getChannel(command[1]);
    if (!channel->isMember(fd))                          return (server.sendMessageToClient(ERR_NOTONCHANNEL  (nick, command[1]), fd));
    channel->broadcastMessage(PART_LOG(nick, client.getUsername(), command[1]), 0);
    channel->removeMember(fd);
    if (channel->isOperator(fd))
        channel->removeOperator(fd);
}
