/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:41:52 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/27 09:46:32 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"

void IRCCommandHandler::user(std::vector<std::string> command, Server &server, Client &client)
{
	int			clientFd	= client.getSocket();
	std::string nick		= client.getNickname();
	if (client.isAuthenticated() == true)
		return (server.sendMessageToClient(ERR_ALREADYREGISTERED(nick), clientFd));
	if (command.size() < 5) //>>> The <realname> may contain space characters<<< TODO
		return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, command[0]),clientFd));
	if (server.userValid(command[1]))
		return (server.sendMessageToClient("Username taken, try again...", clientFd));
	client.setUsername(command[1]);
}