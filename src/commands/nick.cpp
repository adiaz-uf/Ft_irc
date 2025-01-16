# include "IRCCommandHandler.hpp"

/*
Command: NICK: Parameters: <nickname>
Command Example:
NICK Wiz     ; Requesting the new nick "Wiz". Message Examples:
:WiZ NICK Kilroy   ; WiZ changed his nickname to Kilroy.



ERR_NONICKNAMEGIVEN (431)                                               [x]
ERR_ERRONEUSNICKNAME (432)                                              [x]
ERR_NICKNAMEINUSE (433)                                                 [x]
ERR_NICKCOLLISION (436)                                                 [x]
                - No hace falta manejar que es un 433 con otro servidor que este connectado
*/

void IRCCommandHandler::nick(std::vector<std::string> command, Server &server, Client &client)
{
    if (command.size() < 2)
    {
		server.sendMessageToClient(ERR_NONICKNAMEGIVEN(client.getUsername()), client.getSocket());
        return ; 
    }
    switch(server.nickValid(command[1], client.getSocket()))
    {
        case 1:
            // ERR_ERRONEUSNICKNAME (432)
            return (server.sendMessageToClient(ERR_ERRONEUSNICKNAME(client.getNickname(), command[1]), client.getSocket()));

        case 2:
            // ERR_NICKNAMEINUSE (433)
            return (server.sendMessageToClient(ERR_NICKNAMEINUSE(client.getNickname(), command[1]), client.getSocket()));
        
        default:
            if (client.isAuthenticated())
                server.sendMessageToClient(NICK_LOG(client.getNickname(), client.getUsername(), command[1]), client.getSocket());
            client.setNickname(command[1]);
    }
}