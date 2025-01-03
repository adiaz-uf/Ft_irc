# include "IRCCommandHandler.hpp"


/* 
KICK:  Parameters: <channel> <user> *( "," <user> ) [<comment>]
- KICK #Finnish Matthew           ; Command to kick Matthew from #Finnish
- KICK #Finnish John :Speaking English 
Command to kick John from #Finnish using "Speaking English" as the reason (comment).

ERR_NEEDMOREPARAMS (461)v
ERR_NOSUCHCHANNEL (403)v
ERR_CHANOPRIVSNEEDED (482)
ERR_USERNOTINCHANNEL (441)v
ERR_NOTONCHANNEL (442)
*/
void	IRCCommandHandler::kick(std::vector<std::string> command, Server &server, Client &client)
{
	if (!server.isValidChannel(command[1]))
		std::cerr << ERR_NOSUCHCHANNEL(client.getUsername() , command[1]) << std::endl;
	else if (command.size() < 3)
		std::cerr << ERR_NEEDMOREPARAMS(client.getUsername(), "KICK") << std::endl;
	else if (server.getChannel(command[1])->getMember(command[2])->getUsername() != command[1])
		std::cerr << ERR_USERNOTINCHANNEL(client.getUsername(), client.getNickname(), "KICK") << std::endl;
	else
	{
		int socket = server.getChannel(command[1])->getMember(command[2])->getSocket();
		server.getChannel(command[1])->deleteMember(socket);
		// TODO: send kick log
	}
}