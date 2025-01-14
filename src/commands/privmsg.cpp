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
    if (command.size() < 3)
        std::cerr << ERR_NEEDMOREPARAMS(client.getUsername(), "PRIVMSG") << std::endl;
    else if (server.isValidChannel(command[1]))
        server.getChannel(command[1])->broadcastMessage(PRIVMSG_LOG((client.getNickname()), client.getUsername(), command[1], command[2]), client.getSocket());
    else if (!server.isValidClient(command[1]))
        std::cerr << ERR_NOSUCHNICK(client.getNickname(), command[1]) << std::endl;
    else
        server.sendMessageToClient(PRIVMSG_LOG((client.getNickname()), client.getUsername(), command[1], command[2]), server.getClient(command[1])->getSocket());
}
