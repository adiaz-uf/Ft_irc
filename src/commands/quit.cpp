# include "IRCCommandHandler.hpp"


/*
Command: QUIT -> Parameters: [<reason>]

Command Example:
- QUIT :Gone to have lunch    ; Client exiting from the network
Message Example:

:dan-!d@localhost QUIT :Quit: Bye for now! ; dan- is exiting the network with the message: "Quit: Bye for now!"
*/
void IRCCommandHandler::quit(std::vector<std::string> command, Server &server, Client &client)
{   
    (void)command;
    (void)server;
    (void)client;
    return ;
}