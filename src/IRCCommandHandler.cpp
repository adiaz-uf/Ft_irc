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
    std::string ircCommands[7] = { "JOIN", "NICK", "TOPIC", \
    "KICK", "MODE", "PRIVMSG", "INVITE" };
    
    std::vector<std::string> command = IRCCommandHandler::split_istringstream(input);
    do
        n++;
    while (n < 7 && command[0] != ircCommands[n]);  
    switch (n)
    {
        case 0:  // JOIN
            join(command, server, client);
            //JOIN_LOG(nick, user, channel);
            break;
        case 1: // NICK
            nick(command, server, client);
            //NICK(oldnick, user, newnick) 
            break;
        case 2: // TOPIC
            topic(command, server, client);
            //TOPIC_GET(nick, channel, topic)
            //TOPIC_SET(todo)
            break;
        case 3: // KICK
            kick(command, server, client);
            break;
        case 4: // MODE
            mode(command, server, client);
            break;
        case 5: // PRIVMSG
            privmsg(command, server, client);
            break;
        case 6: // INVITE
            invite(command, server, client);
            break;
        default:
            std::cout << "INVALID COMMAND" << std::endl;
            break;
    }
}