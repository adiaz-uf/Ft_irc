# include "IRCCommandHandler.hpp"


/* 
KICK:  Parameters: <channel> <user> *( "," <user> ) [<comment>]
- KICK #Finnish Matthew           ; Command to kick Matthew from #Finnish
- KICK #Finnish John :Speaking English 
Command to kick John from #Finnish using "Speaking English" as the reason (comment).

ERR_NEEDMOREPARAMS (461)v
ERR_NOSUCHCHANNEL (403)v
ERR_CHANOPRIVSNEEDED (482)v
ERR_USERNOTINCHANNEL (441)v
ERR_NOTONCHANNEL (442)v
*/
void	IRCCommandHandler::kick(std::vector<std::string> command, Server &server, Client &client)
{
/* 	Channel* channel = server.getChannel(command[1]);
	std::cerr << "Channel :" << channel << std::endl;
	if (!channel) {
		std::cerr << ERR_NOSUCHCHANNEL(client.getNickname(), command[1]) << std::endl;
		return;
	} 
	if (command.size() > 3)
		channel->broadcastMessage(KICK_LOG((client.getNickname()), command[2], command[1], command[3]), 0);
	else if (command.size() == 3)
		channel->broadcastMessage(KICK_LOG((client.getNickname()), command[2], command[1], command[2]), 0);
	return ;
	*/
	if (command.size() < 3)
		server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "KICK"), client.getSocket());
	else if (!server.isValidChannel(command[1]))
		server.sendMessageToClient(ERR_NOSUCHCHANNEL(client.getUsername() , command[1]), client.getSocket());
	else if (server.getChannel(command[1])->getMember(command[2])->getUsername() != command[1])
		server.sendMessageToClient(ERR_USERNOTINCHANNEL(client.getUsername(), client.getNickname(), "KICK"), client.getSocket());
	else if (!server.getChannel(command[2])->isMember(client.getSocket()))
        server.sendMessageToClient(ERR_NOTONCHANNEL(client.getNickname(), server.getChannel(command[2])->getName()), client.getSocket());
    else if (!server.getChannel(command[2])->isOperator(client.getSocket()))
        server.sendMessageToClient(ERR_CHANOPRIVSNEEDED(client.getNickname(), server.getChannel(command[2])->getName()), client.getSocket());
	else
	{
		int socket = server.getChannel(command[1])->getMember(command[2])->getSocket();
		server.getChannel(command[1])->deleteMember(socket);
		if (command.size() > 3)
			server.getChannel(command[1])->broadcastMessage(KICK_LOG((client.getNickname()), command[2], command[1], command[3]), 0);
		else if (command.size() == 3)
			server.getChannel(command[1])->broadcastMessage(KICK_LOG((client.getNickname()), command[2], command[1], "No reason"), 0);
	}
}
