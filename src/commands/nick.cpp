# include "IRCCommandHandler.hpp"

/*
Command: NICK: Parameters: <nickname>

Command Example:

NICK Wiz     ; Requesting the new nick "Wiz". Message Examples:

:WiZ NICK Kilroy   ; WiZ changed his nickname to Kilroy.

ERR_NONICKNAMEGIVEN (431)
ERR_ERRONEUSNICKNAME (432)
ERR_NICKNAMEINUSE (433)
ERR_NICKCOLLISION (436)
*/

void IRCCommandHandler::nick(std::vector<std::string> command, Server &server, Client &client)
{
    (void)command;
    (void)server;
    (void)client;
    return ;
}