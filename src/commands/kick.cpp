# include "IRCCommandHandler.hpp"

/* 
KICK:  Parameters: <channel> <user> *( "," <user> ) [<comment>]
- KICK #Finnish Matthew           ; Command to kick Matthew from #Finnish
- KICK #Finnish John :Speaking English 
Command to kick John from #Finnish using "Speaking English" as the reason (comment).

ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_CHANOPRIVSNEEDED (482)
ERR_USERNOTINCHANNEL (441)
ERR_NOTONCHANNEL (442)
*/
void	IRCCommandHandler::kick(std::vector<std::string> command, Server &server, Client &client)
{
	if (!server.isValidChannel(command[1]))
		std::cerr << ERR_NOSUCHCHANNEL(client.getUsername() , command[1]) << std::endl;
	else if (command.size() < 3)
		std::cerr << ERR_NEEDMOREPARAMS(client.getUsername(), "KICK") << std::endl;
/* 	else if (server.getChannel(command[1])->getUser().find(command[1]) != command[1])//TODO
		std::cerr << ERR_USERNOTINCHANNEL(client.getUsername(), client.getNickname(), "KICK") << std::endl; */
	else
		server.getChannel(command[1])->getUser().erase(command[2]);
}