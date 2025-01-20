/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:10:53 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/20 14:11:02 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"

/* 
TOPIC: Parameters: <channel> [<topic>]
- TOPIC #test :New topic    ; Setting the topic on "#test" to "New topic".
- TOPIC #test :             ; Clearing the topic on "#test"
- TOPIC #test               ; Checking the topic for "#test"

ERR_NEEDMOREPARAMS (461)        [x]
ERR_NOSUCHCHANNEL (403)         [x]
ERR_NOTONCHANNEL (442)          [x]
ERR_CHANOPRIVSNEEDED (482)      [x]

NOT ERRORS TO BE IMPLEMENTED IN JOIN
    RPL_NOTOPIC (331)               
    RPL_TOPIC (332)                 
 */

void	IRCCommandHandler::topic(std::vector<std::string> command, Server &server, Client &client)
{  
    int         clientFd      = client.getSocket();
    std::string nick    = client.getNickname();

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
        std::cout << "Clearing the topic on \"" << channel->getName() << "\"" << std::endl;
        channel->setTopic(":No topic is set");
        server.sendMessageToClient(TOPIC_SET_LOG(nick, client.getUsername(), command[1], channel->getTopic()), clientFd);
    }
    else
    {
        std::cout << " Setting the topic on \"" << channel->getName() << "\" to " << command[2] << std::endl;
        channel->setTopic(new_topic);
        server.sendMessageToClient(TOPIC_SET_LOG(nick, client.getUsername(), command[1], new_topic), clientFd);
    }
}
