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
    int fd = client.getSocket();
    if (command.size() < 2)
    {
		server.sendMessageToClient(ERR_NONICKNAMEGIVEN(client.getUsername()), fd);
        return ; 
    }
    std::string new_nick = command[1];
    switch(server.nickValid(new_nick, fd))
    {
        case 1:
            // ERR_ERRONEUSNICKNAME (432)
            return (server.sendMessageToClient(ERR_ERRONEUSNICKNAME(client.getNickname(), new_nick), fd));

        case 2:
            // ERR_NICKNAMEINUSE (433)
            return (server.sendMessageToClient(ERR_NICKNAMEINUSE(client.getNickname(), new_nick), fd));
        
        default:
            if (client.isAuthenticated()) server.sendMessageToClient(NICK_LOG(client.getNickname(), client.getUsername(), new_nick), fd);
            client.setNickname(new_nick);
    }
}