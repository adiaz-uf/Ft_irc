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
    std::string ircCommands[13] = { "JOIN", "PART", "NICK", "QUIT", "TOPIC", \
    "KICK", "INVITE", "MODE", "PING", "PONG", "PRIVMSG", "HELP", "NOTICE" };
    
    std::vector<std::string> command = IRCCommandHandler::split_istringstream(input);
    do
        n++;
    while (n < 13 && command[0] != ircCommands[n]);  
    switch (n)
    {
        case 0:  // JOIN
            join(command, server, client);
            break;
        case 1: // PART
            part(command, server, client);
            break;
        case 2: // NICK
            nick(command, server, client);
            break;
        case 3: // QUIT
            quit(command, server, client);
            break;
        case 4: // TOPIC
            topic(command, server, client);
            break;
        case 5: // KICK
            kick(command, server, client);
            break;
        case 6: // INVITE
            invite(command, server, client);
            break;
        case 7: // MODE
            mode(command, server, client);
            break;
        case 8: // PING
            ping(command, server, client);
            break;
        case 9: // PONG
            pong(command, server, client);
            break;
        case 10: // PRIVMSG
            privmsg(command, server, client);
            break;
        case 11: // HELP
            help(command, server, client);
            break;
        case 12: // NOTICE
            notice(command, server, client);
            break;
        default:
            std::cout << "INVALID COMMAND" << std::endl;
            break;
    }
}