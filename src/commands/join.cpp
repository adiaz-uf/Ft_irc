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
ERR_BADCHANNELKEY (475)
ERR_BANNEDFROMCHAN (474)
ERR_CHANNELISFULL (471)
ERR_INVITEONLYCHAN (473)
ERR_BADCHANMASK (476)
RPL_TOPIC (332)
RPL_TOPICWHOTIME (333)
RPL_NAMREPLY (353)
RPL_ENDOFNAMES (366)
*/
void    IRCCommandHandler::join(std::vector<std::string> command, Server &server, Client &client)
{
    int i = 1;
    std::vector<std::string> channels;
    std::vector<std::string> keys;
    while (server.isValidChannel(command[i]))//TODO: separate channels and keys
    {
        channels.push_back(command[i]);
        if (command[i + 1].compare(","))
            i += 2; 
    }
    if (command.size() < 2)
		std::cerr << ERR_NEEDMOREPARAMS(client.getUsername(), "JOIN") << std::endl;
    else if (!server.isValidChannel(command[1]))
		std::cerr << ERR_NOSUCHCHANNEL(client.getUsername() , command[1]) << std::endl;
    (void)server;
    return ;
}