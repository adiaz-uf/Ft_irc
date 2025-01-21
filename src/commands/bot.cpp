/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:50 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/21 11:28:43 by adiaz-uf         ###   ########.fr       */
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
            server.sendMessageToClient("What did one hat say to the other? you wait here. I'll go on a head.\r\n", fd);
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
    std::string date(std::ctime(&result));
    std::string message = "Hi! todays date is " + date; 
    server.sendMessageToClient(message, client.getSocket());
}

void countClients(Server &server, Client &client)
{
    int count = server.getClientsCount();
    std::stringstream ss;
    ss << count;
    std::string str = "Clients in server: " + ss.str() + "\r\n";
    server.sendMessageToClient(str, client.getSocket());
}

void	IRCCommandHandler::bot(std::vector<std::string> command, Server &server, Client &client)
{
    int         n = -1;
    std::string ircCommands[3] = { "JOKE", "DATE", "CLIENTS" };
    
    do
        n++;
    while (n < 3 && command[1] != ircCommands[n]); 
    switch (n)
    {
		case 0:  
			makeJoke(server, client);
			break;
        case 1:  
            sayDate(server, client);
            break;
        case 2: 
            countClients(server, client);
            break;
        default:
            server.sendMessageToClient("Invalid Bot Command, available commands: JOKE, DATE, CLIENTS.\r\n", client.getSocket());
            break;
    }
}