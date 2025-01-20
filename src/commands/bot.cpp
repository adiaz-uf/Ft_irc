/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:50 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/17 07:25:51 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IRCCommandHandler.hpp"

void makeJoke(Server &server, Client &client)
{
    int fd = client.getSocket();
    srand(time(NULL));
    int randNum = (rand() % 4);

    switch (randNum)
    {
        case 0:
            server.sendMessageToClient("What do you call a pony with a cough? A little horse.\r\n", fd);
            break;
        case 1:
            server.sendMessageToClient("What did one hat say to the other? you wait here. I’ll go on a head.\r\n", fd);
            break;
        case 2:
            server.sendMessageToClient("What do you call a magic dog? A labracadabrador.\r\n", fd);
            break;
        default:
            server.sendMessageToClient("What did the shark say when he ate the clownfish? This tastes a little funny.\r\n", fd);
            break;
    }
}

void sayDate(Server &server, Client &client)
{
    std::time_t result = std::time(NULL);
    std::cout << std::ctime(&result);
    server.sendMessageToClient(std::ctime(&result), client.getSocket());
}

void	IRCCommandHandler::bot(std::vector<std::string> command, Server &server, Client &client)
{
    int         n = -1;
    std::string ircCommands[2] = { "JOKE", "DATE" };
    
    do
        n++;
    while (n < 2 && command[1] != ircCommands[n]); 
    switch (n)
    {
		case 0:  
			makeJoke(server, client);
			break;
        case 1:  
            sayDate(server, client);
            break;
        default:
            std::cout << "INVALID BOT COMMAND" << std::endl;
            break;
    }
}