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
    std::cout << input << std::endl;
    int         n = -1;
    std::string ircCommands[9] = { "PASS", "JOIN", "NICK", "TOPIC", \
    "KICK", "MODE", "PRIVMSG", "INVITE", "USER" };
    
    std::vector<std::string> command = IRCCommandHandler::split_istringstream(input);
    do
        n++;
    while (n < 8 && command[0] != ircCommands[n]); 
	
	if (!client.isAuthenticated() && n != 0 && n != 2 && n != 8)
	{
		server.sendMessageToClient("You must provide the PASSWORD USER and NICK first.\r\n", client.getSocket());
		return;
	}
    switch (n)
    {
		case 0:  
			pass(command, server, client);
			break;
        case 1:  
            join(command, server, client);
            //JOIN_LOG(nick, user, channel);
            break;
        case 2: 
            nick(command, server, client);
            //NICK(oldnick, user, newnick) 
            break;
        case 3: 
            topic(command, server, client);
            //TOPIC_GET(nick, channel, topic)
            //TOPIC_SET(todo)
            break;
        case 4: 
            kick(command, server, client);
            break;
        case 5: 
            //mode(command, server, client);
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
        default:
            std::cout << "INVALID COMMAND" << std::endl;
            break;
    }
    if (client.isAuthenticated() == false) client.authenticate(server);
}
