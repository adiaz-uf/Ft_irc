/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:06 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/21 10:18:45 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommandHandler.hpp"

void IRCCommandHandler::quit(std::vector<std::string> command, Server &server, Client &client)
{
    int clientFd = client.getSocket();
    
    std::string message = aggregate(command, 3);
    if (message == "")        message = "Client Quit";
    else                      message.erase(0,1);
    std::set<int> contacts = server.getContacts(clientFd);
    for (std::set<int>::iterator it = contacts.begin(); it != contacts.end(); it++)
        server.sendMessageToClient(QUIT_LOG(client.getNickname(), client.getUsername(), message), (*it));
    server.deleteMemberAllChannels(clientFd);
    server.disconnectClient(clientFd);
}
