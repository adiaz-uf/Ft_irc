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

void IRCCommandHandler::user(std::vector<std::string> command, Server &server, Client &client)
{
    (void)server;
    client.setUsername(command[1]);
    //if (command.size() < 2)
    //{
	//	server.sendMessageToClient(ERR_NONICKNAMEGIVEN(client.getUsername()), client.getSocket());
    //    return ;
    //}
    //if (!server.nickValid(command[1], client.getSocket()))
    //    return ;
    //server.sendMessageToClient(NICK_LOG(client.getNickname(), client.getUsername(), command[1]), client.getSocket());
    //client.setNickname(command[1]);
}