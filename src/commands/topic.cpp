/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:10:53 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/21 10:20:15 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"

/* 
TOPIC: Parameters: <channel> [<topic>]             
*/

void	IRCCommandHandler::topic(std::vector<std::string> command, Server &server, Client &client)
{  
    int         clientFd = client.getSocket();
    std::string nick = client.getNickname();

    if (command.size() < 2) 
        return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, "TOPIC"), clientFd));
    if (!server.isValidChannel(command[1])) 
        return (server.sendMessageToClient(ERR_NOSUCHCHANNEL(nick, command[1]), clientFd));
    Channel *channel = server.getChannel(command[1]);
    if (!channel->isMember(clientFd)) 
        return (server.sendMessageToClient(ERR_NOTONCHANNEL(nick, channel->getName()), clientFd));
    if (command.size() == 2) 
        return (server.sendMessageToClient(TOPIC_GET_LOG(nick, command[1], channel->getTopic()), clientFd));
    if (!channel->isOperator(clientFd) && channel->hasMode(TOPIC_PROTECTED))
        return (server.sendMessageToClient(ERR_CHANOPRIVSNEEDED(nick, channel->getName()), clientFd));
    std::string new_topic = aggregate(command, 2);
    if (new_topic.size() == 1)
    {
        channel->setTopic(":No topic is set");
        server.sendMessageToClient(TOPIC_SET_LOG(nick, client.getUsername(), command[1], channel->getTopic()), clientFd);
    }
    else
    {
        channel->setTopic(new_topic);
        server.sendMessageToClient(TOPIC_SET_LOG(nick, client.getUsername(), command[1], new_topic), clientFd);
    }
}
