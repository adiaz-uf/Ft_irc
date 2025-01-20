/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommandHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:15 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/20 14:37:56 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"

std::vector<std::string> IRCCommandHandler::split_istringstream(std::string str) {
    std::vector<std::string> split;
    std::istringstream isstream(str);
    std::string word;

    while(isstream >> word){
        split.push_back(word);
    }

    return split;
}

void IRCCommandHandler::handleCommand(Server &server, Client &client, std::string input)
{
    int         fd = client.getSocket();
    int         n = -1;
    std::string ircCommands[13] = { "PASS", "JOIN", "NICK", "TOPIC", "KICK", "MODE", "PRIVMSG", "INVITE", "USER", "PART", "QUIT", "WHO", "bot"};
    
    std::vector<std::string> command = IRCCommandHandler::split_istringstream(input);
    std::transform(command[0].begin(), command[0].end(), command[0].begin(), ::toupper);
    do
        n++;
    while (n < 13 && command[0] != ircCommands[n]); 
	
	if (!client.isAuthenticated() && n != 0 && n != 2 && n != 8)
		return(server.sendMessageToClient("You must provide the PASS, USER and NICK first.\r\n", client.getSocket()));
    
    switch (n)
    {
		case 0:  
			pass(command, server, client);
			break;
        case 1:  
            join(command, server, client);
            break;
        case 2: 
            nick(command, server, client);
            break;
        case 3: 
            topic(command, server, client);
            break;
        case 4: 
            kick(command, server, client);
            break;
        case 5: 
            mode(command, server, client);
            break;
        case 6:
            privmsg(command, server, client);
            break;
        case 7: 
            invite(command, server, client);
            break;
        case 8: 
            user(command, server, client);
            break;
        case 9: 
            part(command, server, client);
            break;
        case 10: 
            quit(command, server, client);
            break;
        case 11: 
            who(command, server, client);
            break;
        case 12:
            bot(command, server, client);
        default:
            std::cout << "INVALID COMMAND" << std::endl;
            break;
    }
    if (server.getClient(fd)) if (client.isAuthenticated() == false) client.authenticate(server);
}
