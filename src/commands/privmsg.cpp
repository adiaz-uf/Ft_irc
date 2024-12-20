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

ERR_NOSUCHNICK (401)
ERR_NOSUCHSERVER (402)
ERR_CANNOTSENDTOCHAN (404)
ERR_TOOMANYTARGETS (407)
ERR_NORECIPIENT (411)
ERR_NOTEXTTOSEND (412)
ERR_NOTOPLEVEL (413)
ERR_WILDTOPLEVEL (414)
RPL_AWAY (301)
*/
void IRCCommandHandler::privmsg(std::vector<std::string> command, Server &server, Client &client)
{    
    (void)command;
    (void)server;
    (void)client;
    return ;
}