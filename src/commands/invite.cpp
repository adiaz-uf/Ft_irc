# include "IRCCommandHandler.hpp"

/* 
INVITE: Parameters: <nickname> <channel>
- INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar

RPL_INVITING (341)
ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_NOTONCHANNEL (442)
ERR_CHANOPRIVSNEEDED (482)
ERR_USERONCHANNEL (443)
*/
void	IRCCommandHandler::invite(std::vector<std::string> command, Server &server, Client &client)
{
    (void)command;
    (void)server;
    (void)client;
	return ;
}