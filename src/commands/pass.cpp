#include "IRCCommandHandler.hpp"

void IRCCommandHandler::pass(std::vector<std::string> command, Server &server, Client &client)
{    
    if (command.size() < 2)
	{
		server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getNickname(), "PASS") + "\r\n", client.getSocket());
		return ;
	}
	if (client.isAuthenticated())
	{
		server.sendMessageToClient(ERR_ALREADYREGISTERED(client.getNickname()) + "\r\n", client.getSocket());
		return ;
	}
	std::string	passwordClient = command[1];
	if (passwordClient != server.getPassword())
	{
		server.sendMessageToClient(ERR_PASSWDMISMATCH(client.getNickname()) + "\r\n", client.getSocket());
		server.disconnectClient(client.getSocket());
		return ;
	}
	client.authenticate();
	server.sendMessageToClient(("Your client has been successfully connected\r\n"), client.getSocket());
	server.sendMessageToClient("Welcome on myIRC !\r\n", client.getSocket());
}
