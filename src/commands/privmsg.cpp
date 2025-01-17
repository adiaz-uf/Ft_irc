# include "IRCCommandHandler.hpp"


/*
Command: PRIVMSG -> Parameters: <target>{,<target>} <text to be sent>

- PRIVMSG Angel :yes I'm receiving it ! ; Command to send a message to Angel.

- PRIVMSG %#bunny :Hi! I have a problem! ; Command to send a message to halfops and chanops on #bunny.

- PRIVMSG @%#bunny :Hi! I have a problem! ; Command to send a message to halfops
    and chanops on #bunny. This command is functionally identical to the above command.
Message Examples:

:Angel PRIVMSG Wiz :Hello are you receiving this message ? ; Message from Angel to Wiz.
:dan!~h@localhost PRIVMSG #coolpeople :Hi everyone! ; Message from dan to the channel #coolpeople

ERR_NOSUCHNICK (401)			[x]
ERR_NOSUCHSERVER (402)			[]
ERR_CANNOTSENDTOCHAN (404)		[]
ERR_TOOMANYTARGETS (407)		[]
ERR_NORECIPIENT (411)			[]
ERR_NOTEXTTOSEND (412)			[]
ERR_NOTOPLEVEL (413)			[]
ERR_WILDTOPLEVEL (414)			[]
*/


void IRCCommandHandler::privmsg(std::vector<std::string> command, Server &server, Client &client)
{    
	std::string message;
	int clientFd = client.getSocket();

    if (command.size() < 3)
	{
		server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "PRIVMSG"), clientFd);
		return ;
	}
	for (size_t i = 2; i < command.size(); ++i)
	{
		if (i != 2)
			message += " ";
		message += command[i];
	}
	if (!message.empty() && message[0] == ':')
		message.erase(0, 1);
    if (server.isValidChannel(command[1]))
        server.getChannel(command[1])->broadcastMessage(PRIVMSG_LOG((client.getNickname()), client.getUsername(), command[1], message), clientFd);
    else if (!server.isValidClient(command[1]))
		server.sendMessageToClient(ERR_NOSUCHNICK(client.getNickname(), command[1]), clientFd);
    else
		server.sendMessageToClient(PRIVMSG_LOG((client.getNickname()), client.getUsername(), command[1], message), server.getClient(command[1])->getSocket());
}
