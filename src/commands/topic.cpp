# include "IRCCommandHandler.hpp"

/* 
TOPIC: Parameters: <channel> [<topic>]
- TOPIC #test :New topic    ; Setting the topic on "#test" to "New topic".
- TOPIC #test :             ; Clearing the topic on "#test"
- TOPIC #test               ; Checking the topic for "#test"

ERR_NEEDMOREPARAMS (461)v
ERR_NOSUCHCHANNEL (403)v
ERR_NOTONCHANNEL (442)v
ERR_CHANOPRIVSNEEDED (482)v
RPL_NOTOPIC (331)
RPL_TOPIC (332)
RPL_TOPICWHOTIME (333)
 */
void	IRCCommandHandler::topic(std::vector<std::string> command, Server &server, Client &client)
{    
    if (command.size() < 2)
		std::cerr << ERR_NEEDMOREPARAMS(client.getUsername(), "TOPIC") << std::endl;
    else if (!server.isValidChannel(command[1]))
        std::cerr << ERR_NOSUCHCHANNEL(command[1], server.getChannel(command[1])->getName()) << std::endl;
    else if (!server.getChannel(command[1])->isMember(client.getSocket()))
        std::cerr << ERR_NOTONCHANNEL(client.getNickname(), server.getChannel(command[1])->getName()) << std::endl;
    else if (!server.getChannel(command[1])->isOperator(client.getSocket()))
        std::cerr << ERR_CHANOPRIVSNEEDED(client.getNickname(), server.getChannel(command[1])->getName()) << std::endl;
    else
    {
        if (command.size() == 2)
        {
            std::cout << "Checking the topic for \"" << server.getChannel(command[1])->getName() << "\"" << std::endl;
            std::cout << "Topic: " << server.getChannel(command[1])->getTopic() << std::endl;
        }
        else
        {
            if (command[2].compare(":") == 0)
            {
                std::cout << "Clearing the topic on \"" << server.getChannel(command[1])->getName() << "\"" << std::endl;
                server.getChannel(command[1])->setTopic("");
            }
            else
            {
                command[2].erase(0, 1);
                std::cout << " Setting the topic on \"" << server.getChannel(command[1])->getName()
                << "\" to " << command[2] << std::endl;
                server.getChannel(command[1])->setTopic(command[2]);
            }
        }
    }
	return ;
}