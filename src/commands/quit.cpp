/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:06 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/17 09:25:56 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommandHandler.hpp"

void IRCCommandHandler::quit(std::vector<std::string> command, Server &server, Client &client)
{

    server.deleteMemberAllChannels(client.getSocket());
    server.disconnectClient(client.getSocket());
    std::string message = aggregate(command, 3);
    if (message == "")
        message = ":Client Quit";
    std::set<int> contacts = server.getContacts(client.getSocket());
    for (std::set<int>::iterator it = contacts.begin(); it != contacts.end(); it++)
        server.sendMessageToClient(QUIT_LOG(client.getNickname(), client.getUsername(), message), (*it));
}
