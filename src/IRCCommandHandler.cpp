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
    (void)server;
    (void)client;
    int         n = -1;
    std::string ircCommands[14] = { "JOIN", "PART", "NICK", "QUIT", "MSG", "TOPIC", \
    "KICK", "INVITE", "MODE", "PING", "PONG", "PRIVMSG", "MODE", "HELP" };
    
    std::vector<std::string> command = IRCCommandHandler::split_istringstream(input);
    do
        n++;
    while (n < 14 && command[0] != ircCommands[n]);  
    switch (n)
    {
        case 0:  // JOIN
            break;
        case 1: // PART

            break;
        case 2: // NICK

            break;
        case 3: // QUIT

            break;
        case 4: // MSG

            break;
        case 5: // TOPIC

            break;
        case 6: // KICK
            client.getChannel()->kick(command, server, client);
            break;
        case 7: // INVITE

            break;
        case 8: // MODE

            break;
        case 9: // PING

            break;
        case 10: // PONG

            break;
        case 11: // PRIVMSG

            break;
        case 12: // MODE

            break;
        case 13: // HELP

            break;
        default:
            std::cout << "INVALID COMMAND" << std::endl;
            break;
    }

}