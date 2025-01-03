# include "IRCCommandHandler.hpp"

/*
Command: NICK: Parameters: <nickname>
Command Example:
NICK Wiz     ; Requesting the new nick "Wiz". Message Examples:
:WiZ NICK Kilroy   ; WiZ changed his nickname to Kilroy.

ERR_NONICKNAMEGIVEN (431)v
ERR_ERRONEUSNICKNAME (432)v
ERR_NICKNAMEINUSE (433)
ERR_NICKCOLLISION (436)
*/

void IRCCommandHandler::nick(std::vector<std::string> command, Server &server, Client &client)
{
    if (command.size() < 2)
    {
		std::cerr << ERR_NONICKNAMEGIVEN(client.getUsername()) << std::endl;
        return ;
    }
    if (!server.nickValid(command[1], client.getSocket()))
        return ;
    
    client.setNickname(command[1]);
}