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
	if (command.size() < 3)
		server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getNickname(), "KICK"), client.getSocket());
	else if (!server.isValidChannel(command[1]))
		server.sendMessageToClient(ERR_NOSUCHCHANNEL(client.getUsername() , command[1]), client.getSocket());
	else if (!server.getChannel(command[1])->isMember(client.getSocket()))
		server.sendMessageToClient(ERR_NOTONCHANNEL(client.getNickname(), server.getChannel(command[1])->getName()), client.getSocket());
	else if (server.getChannel(command[1])->getMember(command[2]) == NULL || !server.getChannel(command[1])->isMember(server.getChannel(command[1])->getMember(command[2])->getSocket()))
		server.sendMessageToClient(ERR_USERNOTINCHANNEL(client.getUsername(), client.getNickname()), client.getSocket());
    else if (!server.getChannel(command[1])->isOperator(client.getSocket()))
	{
		std::cout << "no operator " << std::endl;
		server.sendMessageToClient(ERR_CHANOPRIVSNEEDED(client.getNickname(), server.getChannel(command[1])->getName()), client.getSocket());
	}
	else
	{
		int socket = server.getChannel(command[1])->getMember(command[2])->getSocket();
		if (command.size() > 3)
		{
			std::string message;
			for (size_t i = 3; i < command.size(); ++i)
			{
				if (i != 1)
					message += " ";
				message += command[i];
			}
			if (!message.empty() && message[0] == ':')
				message.erase(0, 1);
			server.getChannel(command[1])->broadcastMessage(KICK_LOG((client.getNickname()), command[2], command[1], message), 0);
		}
		else if (command.size() == 3)
			server.getChannel(command[1])->broadcastMessage(KICK_LOG((client.getNickname()), command[2], command[1], ""), 0);
		server.getChannel(command[1])->deleteMember(socket);
	}
}
