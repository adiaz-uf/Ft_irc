# include "IRCCommandHandler.hpp"

/*
Command: NICK: Parameters: <nickname>
Command Example:
NICK Wiz     ; Requesting the new nick "Wiz". Message Examples:
:WiZ NICK Kilroy   ; WiZ changed his nickname to Kilroy.

ERR_NONICKNAMEGIVEN (431)     [x]
ERR_ERRONEUSNICKNAME (432)    [x]
ERR_NICKNAMEINUSE (433)       [x]
*/

void IRCCommandHandler::nick(std::vector<std::string> command, Server &server, Client &client)
{
    int clientFd = client.getSocket();
    if (command.size() < 2)
		return (server.sendMessageToClient(ERR_NONICKNAMEGIVEN(client.getUsername()), clientFd));

    std::string new_nick = command[1];
    switch(server.nickValid(new_nick))
    {
        case 1:
            // ERR_ERRONEUSNICKNAME (432)
            return (server.sendMessageToClient(ERR_ERRONEUSNICKNAME(client.getNickname(), new_nick), clientFd));

        case 2:
            // ERR_NICKNAMEINUSE (433)
            return (server.sendMessageToClient(ERR_NICKNAMEINUSE(client.getNickname(), new_nick), clientFd));
        
        default:
            if (client.isAuthenticated()) 
                {
                    server.sendMessageToClient(NICK_LOG(client.getNickname(), client.getUsername(), new_nick), clientFd);
                    client.setNickname(new_nick);
                }
    }
}