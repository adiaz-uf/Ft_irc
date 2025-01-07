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
    if (command.size() < 3)
		std::cerr << ERR_NEEDMOREPARAMS(client.getUsername(), "INVITE") << std::endl;
    else if (!server.isValidClient(command[1]))
        std::cerr << "TODO: error" << std::endl;
    else if (!server.isValidChannel(command[2]))
        std::cerr << ERR_NOSUCHCHANNEL(command[2], server.getChannel(command[2])->getName()) << std::endl;
    else if (!server.getChannel(command[2])->isMember(client.getSocket()))
        std::cerr << ERR_NOTONCHANNEL(client.getNickname(), server.getChannel(command[2])->getName()) << std::endl;
    else if (!server.getChannel(command[2])->isOperator(client.getSocket()))
        std::cerr << ERR_CHANOPRIVSNEEDED(client.getNickname(), server.getChannel(command[2])->getName()) << std::endl;
    else if (server.getChannel(command[2])->isMember(server.getClient(command[1])->getSocket()))
        std::cerr << ERR_USERONCHANNEL(client.getNickname(), server.getChannel(command[2])->getName()) << std::endl;
    else
        server.getChannel(command[2])->invite(server, client.getSocket());
}