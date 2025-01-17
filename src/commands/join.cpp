# include "IRCCommandHandler.hpp"

/*
Command: JOIN: Parameters: <channel>{,<channel>} [<key>{,<key>}]

Command Examples:
- JOIN #foobar                    ; join channel #foobar.
- JOIN #foo,&bar fubar            ; join channel #foo using key "fubar" and &bar using no key.
- JOIN #foo,#bar                  ; join channels #foo and #bar.
Message Examples:
- :WiZ JOIN #Twilight_zone        ; WiZ is joining the channel #Twilight_zone
- :dan-!d@localhost JOIN #test    ; dan- is joining the channel #test

ERR_NEEDMOREPARAMS (461)			[x]
ERR_BADCHANNELKEY (475)				[x]
ERR_INVITEONLYCHAN (473)			[x]
*/

//TODO USER LIMIT CANT JOIN

void    IRCCommandHandler::join(std::vector<std::string> command, Server &server, Client &client)
{
    std::queue<std::string> channels;
    std::queue<std::string> keys;
	std::string split;              
	int clientFd = client.getSocket();

	if (command.size() < 2)
		server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "JOIN"), clientFd);
	std::istringstream ss1(command[1]);
	while (std::getline(ss1, split, ',')) // Separate channels into queue                                                                                                                                                                              
		channels.push(split);
	if (command.size() > 2)
	{
		std::istringstream ss2(command[2]); 
		while (std::getline(ss2, split, ',')) // Separate keys into queue                                                                                                                                                                                  
			keys.push(split);
	}
	while (!channels.empty())
	{
		
		if (server.isValidChannel(channels.front()))
		{
			if (server.getChannel(channels.front())->isMember(clientFd) == false)
			{
				if (!keys.empty())
					{
						if (server.getChannel(channels.front())->checkPassword(keys.front()))
							server.getChannel(channels.front())->makeMember(server, clientFd);
						else	
							return server.sendMessageToClient(ERR_BADCHANNELKEY(keys.front(), channels.front()), clientFd);
					}
				else
					server.getChannel(channels.front())->makeMember(server, clientFd);
			}
		}
		else
		{
			server.addChannel(channels.front());
			server.getChannel(channels.front())->makeMember(server, clientFd);
		}
		server.getChannel(channels.front())->broadcastMessage(JOIN_LOG((client.getNickname()), client.getUsername(), channels.front()), 0);
		if (!keys.empty())
			keys.pop();
		channels.pop();
	}
}
