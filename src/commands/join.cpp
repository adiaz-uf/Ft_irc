# include "IRCCommandHandler.hpp"

/*
Command: JOIN: Parameters: <channel>{,<channel>} [<key>{,<key>}]

Command Examples:
- JOIN #foobar                    ; join channel #foobar.
- JOIN &foo fubar                 ; join channel &foo using key "fubar".
- JOIN #foo,&bar fubar            ; join channel #foo using key "fubar" and &bar using no key.
- JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar". and channel #bar using key "foobar".
- JOIN #foo,#bar                  ; join channels #foo and #bar.
Message Examples:
- :WiZ JOIN #Twilight_zone        ; WiZ is joining the channel #Twilight_zone
- :dan-!d@localhost JOIN #test    ; dan- is joining the channel #test

ERR_NEEDMOREPARAMS (461)v
ERR_NOSUCHCHANNEL (403)v
ERR_TOOMANYCHANNELS (405)
ERR_BADCHANNELKEY (475)v
ERR_INVITEONLYCHAN (473)v
ERR_BADCHANMASK (476)
RPL_TOPIC (332)
RPL_TOPICWHOTIME (333)
RPL_NAMREPLY (353)
RPL_ENDOFNAMES (366)
*/
void    IRCCommandHandler::join(std::vector<std::string> command, Server &server, Client &client)
{
    std::queue<std::string> channels;
    std::queue<std::string> keys;
	std::string split;                                                                                                                                                                

    if (command.size() < 2)
		std::cerr << ERR_NEEDMOREPARAMS(client.getUsername(), "JOIN") << std::endl;
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
			if (server.getChannel(channels.front())->isMember(client.getSocket()) == false)
			{
				if (!keys.empty())
					{
						if (server.getChannel(channels.front())->checkPassword(keys.front()))
							server.getChannel(channels.front())->makeMember(server, client.getSocket());
						else	
						{
							std::cerr << ERR_BADCHANNELKEY(keys.front(), channels.front()) << std::endl;
							return ;
						}
					}
				else
					server.getChannel(channels.front())->makeMember(server, client.getSocket());
			}
		}
		else
		{
			server.addChannel(channels.front());
			server.getChannel(channels.front())->makeMember(server, client.getSocket());
		}
		std::cout << "join channel " << channels.front() << " ";
		if (!keys.empty())
		{
			std::cout << "using key \"" << keys.front() << "\" ";
			keys.pop();
		}
		channels.pop();
		if (!channels.empty())
			std::cout << "and ";
	}
	std::cout << std::endl;
    return ;
}