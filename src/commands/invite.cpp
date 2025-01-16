# include "IRCCommandHandler.hpp"

/* 
INVITE: Parameters: <nickname> <channel>
- INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar

ERR_NEEDMOREPARAMS (461)        [x]
ERR_NOSUCHNICK                  [x]
ERR_NOSUCHCHANNEL (403)         [x]
ERR_USERONCHANNEL (443)         [x]
ERR_NOTONCHANNEL (442)          [x]
ERR_CHANOPRIVSNEEDED (482)      [x] << No es necesario que no podemos hacer toggle al modo necesario para tener que ser operador
*/

void	IRCCommandHandler::invite(std::vector<std::string> command, Server &server, Client &client)
{
    int             clientFd    = client.getSocket();
    int             invitedFd   = server.getClient(command[1])->getSocket();
    std::string     nick        = client.getNickname();

	if (command.size() < 3)
		server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, "INVITE"), clientFd);
    else if (!server.isValidClient(command[1]))
        server.sendMessageToClient(ERR_NOSUCHNICK(command[2], command[1]), clientFd);
    else if (!server.isValidChannel(command[2]))
        server.sendMessageToClient(ERR_NOSUCHCHANNEL(command[2], server.getChannel(command[2])->getName()), clientFd);
    else if (!server.getChannel(command[2])->isMember(clientFd))
        server.sendMessageToClient(ERR_NOTONCHANNEL(nick, server.getChannel(command[2])->getName()), clientFd);

    //TODO CAN REMOVE I THINK
    //else if (!server.getChannel(command[2])->isOperator(clientFd))
    //    server.sendMessageToClient(ERR_CHANOPRIVSNEEDED(nick, server.getChannel(command[2])->getName()), clientFd);
    
    else if (server.getChannel(command[2])->isMember(invitedFd))
        server.sendMessageToClient(ERR_USERONCHANNEL(nick, server.getChannel(command[2])->getName()), clientFd);
    else
    {
        server.getChannel(command[2])->invite(server, invitedFd);
        server.sendMessageToClient(INVITER_LOG(nick, command[1], command[2]), clientFd);
        server.sendMessageToClient(INVITEE_LOG(nick, client.getUsername(), command[1], command[2]), invitedFd);
    }
}
