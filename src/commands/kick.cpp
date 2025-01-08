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

//	if (command.size() > 3)
	std::cerr << "Hello" << std::endl;
		server.getChannel(command[1])->broadcastMessage(KICK_LOG((client.getNickname()), command[2], command[1], command[3]), command[1], 0);
//		return ;
//	else if (command.size() == 3)
//		server.sendMessageToClient(KICK_LOG((client.getNickname()), command[2], command[1], command[2]), client.getSocket());
	return ;
	if (command.size() < 3)
		std::cerr << ERR_NEEDMOREPARAMS(client.getUsername(), "KICK") << std::endl;
	else if (!server.isValidChannel(command[1]))
		std::cerr << ERR_NOSUCHCHANNEL(client.getUsername() , command[1]) << std::endl;
	else if (server.getChannel(command[1])->getMember(command[2])->getUsername() != command[1])
		std::cerr << ERR_USERNOTINCHANNEL(client.getUsername(), client.getNickname(), "KICK") << std::endl;
	else if (!server.getChannel(command[2])->isMember(client.getSocket()))
        std::cerr << ERR_NOTONCHANNEL(client.getNickname(), server.getChannel(command[2])->getName()) << std::endl;
    else if (!server.getChannel(command[2])->isOperator(client.getSocket()))
        std::cerr << ERR_CHANOPRIVSNEEDED(client.getNickname(), server.getChannel(command[2])->getName()) << std::endl;
	else
	{
		int socket = server.getChannel(command[1])->getMember(command[2])->getSocket();
		server.getChannel(command[1])->deleteMember(socket);
		// TODO: send kick log
	}
}
