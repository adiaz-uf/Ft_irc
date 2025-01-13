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
    std::string ircCommands[10] = { "+i", "+t", "+k", "+o", "+l", "-i", "-t", "-k", "-o", "-l" };
    int         n = -1;

    if (command.size() < 3)
		server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "MODE"), client.getSocket());
    else if (!server.isValidChannel(command[1]))
        server.sendMessageToClient(ERR_NOSUCHCHANNEL(command[1], server.getChannel(command[1])->getName()), client.getSocket());
    else if (!server.getChannel(command[1])->isMember(client.getSocket()))
        server.sendMessageToClient(ERR_NOTONCHANNEL(client.getNickname(), server.getChannel(command[1])->getName()), client.getSocket());
    else if (!server.getChannel(command[1])->isOperator(client.getSocket()))
        server.sendMessageToClient(ERR_CHANOPRIVSNEEDED(client.getNickname(), server.getChannel(command[1])->getName()), client.getSocket());
    do
        n++;
    while (n < 10 && command[2] != ircCommands[n]);  
    Channel *channel = server.getChannel(command[1]);
    switch (n)
    {
        case 1:
            channel->setMode(ircCommands[n][1], true);
            break;
        case 2:
            channel->setMode(ircCommands[n][1], true);
            break;
        case 3:
            if (command.size() < 4)
                server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "MODE"), client.getSocket());
            else
                {
                    channel->setMode(ircCommands[n][1], true);
                    channel->setPassword(command[3]);
                }
            break;
        case 4:
            if (command.size() < 4)
                server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "MODE"), client.getSocket());
            else
                {
                    if (!server.isValidClient(command[3]))
                        server.sendMessageToClient(ERR_NOSUCHNICK(command[2], command[1]), client.getSocket());
                    else
                    {
                        channel->setMode(ircCommands[n][1], true);
                        channel->makeOperator(server, channel->getMember(command[3])->getSocket());
                    }
                }
            break;
        case 5:
            if (command.size() < 4)
                server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "MODE"), client.getSocket());
            else
            {
                channel->setMode(ircCommands[n][1], true);
                channel->setUsersLimit(std::atoi(command[3].c_str()));
            }
            break;
        case 6:
            channel->setMode(ircCommands[n][1], false);
            break;
        case 7:
            channel->setMode(ircCommands[n][1], false);
            // TODO
            break;
        case 8:
            channel->setMode(ircCommands[n][1], false);
            channel->setPassword("");
            break;
        case 9:
            if (command.size() < 4)
                server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), "MODE"), client.getSocket());
            else
            {
                channel->setMode(ircCommands[n][1], false);
                channel->removeOperator(channel->getMember(command[3])->getSocket());
            }
            break;
        case 10:
            channel->setMode(ircCommands[n][1], false);
            channel->setUsersLimit(0);
            break;
        default:
            server.sendMessageToClient(ERR_INVALIDMODEPARAM(ircCommands[n]), client.getSocket());
    }
	channel->broadcastMessage(MODE_LOG((client.getNickname()), client.getUsername(), command[1], command[2]), 0);
}
