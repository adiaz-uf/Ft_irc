/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:53 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/02/13 12:10:31 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"

/* 
INVITE: Parameters: <nickname> <channel>
*/

void	IRCCommandHandler::invite(std::vector<std::string> command, Server &server, Client &client)
{
    int             clientFd    = client.getSocket();
    std::string     nick        = client.getNickname();

	if (command.size() < 3)
		return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, "INVITE"), clientFd));
    else if (!server.isValidClient(command[1]))
        return (server.sendMessageToClient(ERR_NOSUCHNICK(command[2], command[1]), clientFd));
    int             invitedFd   = server.getClient(command[1])->getSocket();
    if (!server.isValidChannel(command[2]))
        return (server.sendMessageToClient(ERR_NOSUCHNICK(command[2], command[2]), clientFd));
    else if (!server.getChannel(command[2])->isMember(clientFd))
        return (server.sendMessageToClient(ERR_NOTONCHANNEL(nick, server.getChannel(command[2])->getName()), clientFd));
    else if (server.getChannel(command[2])->isMember(invitedFd))
        return (server.sendMessageToClient(ERR_USERONCHANNEL(nick, command[1], server.getChannel(command[2])->getName()), clientFd));
    else
    {
        server.getChannel(command[2])->invite(server, invitedFd);
        server.sendMessageToClient(INVITER_LOG(nick, command[1], command[2]), clientFd);
        server.sendMessageToClient(INVITEE_LOG(nick, client.getUsername(), command[1], command[2]), invitedFd);
    }
}
