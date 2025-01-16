# include "IRCCommandHandler.hpp"

/* 
INVITE: Parameters: <nickname> <channel>
- INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar

RPL_INVITING (341)
ERR_NEEDMOREPARAMS (461)v
ERR_NOSUCHCHANNEL (403)v
ERR_NOTONCHANNEL (442)
ERR_CHANOPRIVSNEEDED (482)v
ERR_USERONCHANNEL (443)
*/
void	IRCCommandHandler::invite(std::vector<std::string> command, Server &server, Client &client)
{
    int clientFd = client.getSocket();

    
	server.sendMessageToClient(INVITE_CLIENT_LOG((client.getNickname()), client.getUsername(), command[1], command[2]), server.getClient(command[1])->getSocket());
	server.sendMessageToClient(INVITE_OPERATOR_LOG((client.getNickname()), command[1], command[2]), clientFd);
	
	if (command.size() < 3)
		server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "INVITE"), clientFd);
    else if (!server.isValidClient(command[1]))
        server.sendMessageToClient(ERR_NOSUCHNICK(command[2], command[1]), clientFd);
    else if (!server.isValidChannel(command[2]))
        server.sendMessageToClient(ERR_NOSUCHCHANNEL(command[2], server.getChannel(command[2])->getName()), clientFd);
    else if (!server.getChannel(command[2])->isMember(clientFd))
        server.sendMessageToClient(ERR_NOTONCHANNEL(client.getNickname(), server.getChannel(command[2])->getName()), clientFd);
    else if (!server.getChannel(command[2])->isOperator(clientFd))
        server.sendMessageToClient(ERR_CHANOPRIVSNEEDED(client.getNickname(), server.getChannel(command[2])->getName()), clientFd);
    else if (server.getChannel(command[2])->isMember(server.getClient(command[1])->getSocket()))
        server.sendMessageToClient(ERR_USERONCHANNEL(client.getNickname(), server.getChannel(command[2])->getName()), clientFd);
    else
        server.getChannel(command[2])->invite(server, clientFd);
}
