/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:41:52 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/17 07:06:01 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

    # include "IRCCommandHandler.hpp"

/*
3.1.3 User message

      Command: USER
   Parameters: <user> <mode> <unused> <realname>

   The USER command is used at the beginning of connection to specify
   the username, hostname and realname of a new user.

 >>> The <realname> may contain space characters<<<

   Numeric Replies:

           ERR_NEEDMOREPARAMS              [x]
           ERR_ALREADYREGISTRED            [x]

   Example:

   USER guest 0 * :Ronnie Reagan   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan".

   USER guest 8 * :Ronnie Reagan   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan", and asking to be set
                                   invisible.
*/


void IRCCommandHandler::user(std::vector<std::string> command, Server &server, Client &client)
{
    bool changed = false;
    if (client.isAuthenticated() == true)
        return (server.sendMessageToClient(ERR_ALREADYREGISTERED(client.getUsername()), client.getSocket()));
    if (command.size() < 5) //>>> The <realname> may contain space characters<<<
		return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), command[0]),client.getSocket()));
    if (server.userValid(command[1]))
        return (server.sendMessageToClient("Username taken, try again...", client.getSocket()));
    client.setUsername(command[1]);
}