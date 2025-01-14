# include "IRCCommandHandler.hpp"

IRCCommandHandler::IRCCommandHandler(/* args */)
{
}

IRCCommandHandler::~IRCCommandHandler()
{
}

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
    int         n = -1;
    std::string ircCommands[8] = { "PASS", "JOIN", "NICK", "TOPIC", \
    "KICK", "MODE", "PRIVMSG", "INVITE" };
    
    std::vector<std::string> command = IRCCommandHandler::split_istringstream(input);
    do
        n++;
    while (n < 8 && command[0] != ircCommands[n]); 
	
	if (!client.isAuthenticated() && n != 0)
	{
		server.sendMessageToClient("You must provide the PASSWORD first.\r\n", client.getSocket());
		return;
	}
    switch (n)
    {
		case 0:  // PASS
			pass(command, server, client);
			break;
        case 1:  // JOIN
            join(command, server, client);
            //JOIN_LOG(nick, user, channel);
            break;
        case 2: // NICK
            nick(command, server, client);
            //NICK(oldnick, user, newnick) 
            break;
        case 3: // TOPIC
            topic(command, server, client);
            //TOPIC_GET(nick, channel, topic)
            //TOPIC_SET(todo)
            break;
        case 4: // KICK
            kick(command, server, client);
            break;
<<<<<<< Updated upstream
        case 4: // MODE
            mode(command, server, client);
=======
        case 5: // MODE
            //mode(command, server, client);
>>>>>>> Stashed changes
            break;
        case 6: // PRIVMSG
            privmsg(command, server, client);
            break;
        case 7: // INVITE
            invite(command, server, client);
            break;
        default:
            std::cout << "INVALID COMMAND" << std::endl;
            break;
    }
}
