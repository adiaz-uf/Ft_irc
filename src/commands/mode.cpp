# include "IRCCommandHandler.hpp"

/*
Command: MODE: Parameters: <target> [<modestring> [<mode arguments>...]]

Command Examples:
MODE #foobar +mb *@127.0.0.1    ; Setting the "moderated" channel mode and
    adding the "*@127.0.0.1" mask to the ban
    list of the #foobar channel.

Message Examples:
:irc.example.com MODE #foobar +o bunny ; The irc.example.com server gave channel
    operator privileges to bunny on #foobar.

· i: Set/remove Invite-only channel
· t: Set/remove the restrictions of the TOPIC command to channel operators
· k: Set/remove the channel key (password)
· o: Give/take channel operator privilege
· l: Set/remove the user limit to channel
*/
void IRCCommandHandler::mode(std::vector<std::string> command, Server &server, Client &client)
{
	Channel* channel = server.getChannel(command[1]);
	channel->broadcastMessage(MODE_LOG((client.getNickname()), client.getUsername(), command[1], command[2]), 0);
    return ;
}
