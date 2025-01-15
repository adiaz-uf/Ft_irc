#include "IRCCommandHandler.hpp"

void IRCCommandHandler::pass(std::vector<std::string> command, Server &server, Client &client)
{    
	if (client.isAuthenticated())
	{
		server.sendMessageToClient(ERR_ALREADYREGISTERED(client.getNickname()) + "\r\n", client.getSocket());
		return ;
	}
    if (command.size() < 2)
	{
		server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getNickname(), "PASS") + "\r\n", client.getSocket());
		return ;
	}
	std::string	passwordClient = command[1];
	if (passwordClient != server.getPassword())
	{ 
		server.sendMessageToClient(ERR_PASSWDMISMATCH(client.getNickname()), client.getSocket());
		server.disconnectClient(client.getSocket());
		return ;
	}
	client.setPassPos();
}
