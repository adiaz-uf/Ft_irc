# include "IRCCommandHandler.hpp"

/*
Command: PART: Parameters: <channel>{,<channel>} [<reason>]
The PART command removes the client from the given channel(s). On sending a 
successful PART command, the user will receive a PART message from the 
server for each channel they have been removed from. <reason> is the reason 
that the client has left the channel(s).

Command Examples:
- PART #twilight_zone             ; leave channel "#twilight_zone"
- PART #oz-ops,&group5            ; leave both channels "&group5" and "#oz-ops".
Message Examples:
- :dan-!d@localhost PART #test    ; dan- is leaving the channel #test

ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_NOTONCHANNEL (442)
*/
void IRCCommandHandler::part(std::vector<std::string> command, Server &server, Client &client)
{    
    (void)command;
    (void)server;
    (void)client;
    return ;
}