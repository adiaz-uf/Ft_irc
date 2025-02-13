/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:43 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/02/13 11:38:31 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"

/*
Command: NICK: Parameters: <nickname>
*/

void IRCCommandHandler::nick(std::vector<std::string> command, Server &server, Client &client)
{
    int clientFd = client.getSocket();
    const std::string nick = client.getNickname();

    if (command.size() < 2) return (server.sendMessageToClient(ERR_NONICKNAMEGIVEN(nick), clientFd));
        
    std::string new_nick = command[1];

    if (new_nick == nick)
        return;
    
    switch(server.nickValid(new_nick))
    {
        case 1: 
            return (server.sendMessageToClient(ERR_ERRONEUSNICKNAME(nick, new_nick), clientFd));
        case 2: 
            return (server.sendMessageToClient(ERR_NICKNAMEINUSE(nick, new_nick), clientFd));
        default:
            if (client.isAuthenticated()) 
                server.sendMessageToClient(NICK_LOG(nick, client.getUsername(), new_nick), clientFd);
            client.setNickname(new_nick);
    }
}