# include "IRCCommandHandler.hpp"

IRCCommandHandler::IRCCommandHandler(/* args */)
{
}

IRCCommandHandler::~IRCCommandHandler()
{
}

std::vector<std::string> IRCCommandHandler::split_istringstream(std::string str) {
    std::vector<std::string> split;
    std::istringstream isstream(str);
    std::string word;

    while(isstream >> word){
        split.push_back(word);
    }

    return split;
}

void IRCCommandHandler::handleCommand(Server &server, Client &client, std::string input)
{
    (void)server;
    (void)client;
    int         n = -1;
    std::string ircCommands[15] = { "JOIN", "PART", "NICK", "QUIT", "MSG", "TOPIC", \
    "KICK", "INVITE", "MODE", "PING", "PONG", "PRIVMSG", "MODE", "HELP", "NOTICE" };
    
    std::vector<std::string> command = IRCCommandHandler::split_istringstream(input);
    do
        n++;
    while (n < 15 && command[0] != ircCommands[n]);  
    switch (n)
    {
        case 0:  // JOIN
            break;
        case 1: // PART

            break;
        case 2: // NICK

            break;
        case 3: // QUIT

            break;
        case 4: // MSG

            break;
        case 5: // TOPIC

            break;
        case 6: // KICK
            kick(command, server, client);//client.getChannel()->
            break;
        case 7: // INVITE

            break;
        case 8: // MODE

            break;
        case 9: // PING

            break;
        case 10: // PONG

            break;
        case 11: // PRIVMSG

            break;
        case 12: // MODE

            break;
        case 13: // HELP

            break;
        default:
            std::cout << "INVALID COMMAND" << std::endl;
            break;
    }
}

/* 
KICK:  Parameters: <channel> <user> *( "," <user> ) [<comment>]
- KICK #Finnish Matthew           ; Command to kick Matthew from #Finnish
- KICK #Finnish John :Speaking English 
Command to kick John from #Finnish using "Speaking English" as the reason (comment).

ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_CHANOPRIVSNEEDED (482)
ERR_USERNOTINCHANNEL (441)
ERR_NOTONCHANNEL (442)
*/
void	IRCCommandHandler::kick(std::vector<std::string> command, Server &server, Client &client)
{
	if (!server.isValidChannel(command[1]))
		std::cerr << ERR_NOSUCHCHANNEL(client.getUsername() , command[1]) << std::endl;
	else if (command.size() < 3)
		std::cerr << ERR_NEEDMOREPARAMS(client.getUsername(), "KICK") << std::endl;
/* 	else if (server.getChannel(command[1])->getUser().find(command[1]) != command[1])//TODO
		std::cerr << ERR_USERNOTINCHANNEL(client.getUsername(), client.getNickname(), "KICK") << std::endl; */
	else
		server.getChannel(command[1])->getUser().erase(command[2]);
}

/* 
INVITE: Parameters: <nickname> <channel>
- INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar
*/
void	Channel::invite(const std::string& username)
{
	_invitedUsers.insert(username);
}

/* 
TOPIC: Parameters: <channel> [<topic>]
- TOPIC #test :New topic    ; Setting the topic on "#test" to "New topic".
- TOPIC #test :             ; Clearing the topic on "#test"
- TOPIC #test               ; Checking the topic for "#test"
 */
void	Channel::setTopic(const std::string& topic)
{
	_topic = topic;
}