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

void IRCCommandHandler::handleCommand(Server server, Client client, std::string input)
{
    (void)server;
    (void)client;
    int                         n = -1;
    std::vector<std::string>    command;
    std::string                 ircCommands[26] = {"JOIN", "PART", "NICK", "QUIT", "MSG", "WHOIS", "AWAY", \
    "BACK", "TOPIC", "LIST", "KICK", "BAN", "INVITE", "MODE", "ME", "SERVER", "PING", "PRIVMSG", \
    "NOTICE", "WHO", "OP", "DEOP", "VOICE", "DEVOICE", "MODE", "HELP"};
    
    command = IRCCommandHandler::split_istringstream(input);
    do
        n++;
    while (n < 26 && command[n] != ircCommands[n]);  
    std::cout << n << std::endl;
    switch (n)
    {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
    }

}