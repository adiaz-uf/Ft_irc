# include "IRCCommandHandler.hpp"

/*
Command: PONG: Parameters: [<server>] <token>

The PONG command is used as a reply to PING commands, by both clients and servers.
The <token> should be the same as the one in the PING message that triggered this PONG.

Servers MUST send a <server> parameter, and clients SHOULD ignore it.
It exists for historical reasons, and indicates the name of the server sending the PONG.
Clients MUST NOT send a <server> parameter.
*/
void IRCCommandHandler::pong(std::vector<std::string> command, Server &server, Client &client)
{   
    (void)command;
    (void)server;
    (void)client;
    return ;
}