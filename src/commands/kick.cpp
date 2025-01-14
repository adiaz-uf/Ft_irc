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
	std::cout << "bye bye 1" << std::endl;
	if (command.size() < 3)
		std::cout  << "bye bye 2" << std::endl;
		//server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "KICK"), client.getSocket());
	else if (!server.isValidChannel(command[1]))
		std::cout  << "bye bye 3" << std::endl;
		//server.sendMessageToClient(ERR_NOSUCHCHANNEL(client.getUsername() , command[1]), client.getSocket());
	else if (!server.getChannel(command[1])->isMember(client.getSocket()))
        std::cout  << "bye bye 5" << std::endl;
	else if (!server.getChannel(command[1])->isMember(server.getChannel(command[1])->getMember(command[2])->getSocket()))
		std::cout  << "bye bye 4" << std::endl;
		//server.sendMessageToClient(ERR_USERNOTINCHANNEL(client.getUsername(), client.getNickname(), "KICK"), client.getSocket());
		//server.sendMessageToClient(ERR_NOTONCHANNEL(client.getNickname(), server.getChannel(command[2])->getName()), client.getSocket());
    else if (!server.getChannel(command[1])->isOperator(client.getSocket()))
        std::cout  << "bye bye 6" << std::endl;
		//server.sendMessageToClient(ERR_CHANOPRIVSNEEDED(client.getNickname(), server.getChannel(command[2])->getName()), client.getSocket());
	else
	{
		std::cout << "bye bye " << std::endl;
		int socket = server.getChannel(command[1])->getMember(command[2])->getSocket();
		server.sendMessageToClient(KICK_LOG((client.getNickname()), command[2], command[1], "No reason"), socket);
		if (command.size() > 3)
			server.getChannel(command[1])->broadcastMessage(KICK_LOG((client.getNickname()), command[2], command[1], command[3]), 0);
		else if (command.size() == 3)
			server.getChannel(command[1])->broadcastMessage(KICK_LOG((client.getNickname()), command[2], command[1], "No reason"), 0);
		server.getChannel(command[1])->deleteMember(socket);	
	}
}
