# include "IRCCommandHandler.hpp"

/* 
TOPIC: Parameters: <channel> [<topic>]
- TOPIC #test :New topic    ; Setting the topic on "#test" to "New topic".
- TOPIC #test :             ; Clearing the topic on "#test"
- TOPIC #test               ; Checking the topic for "#test"

ERR_NEEDMOREPARAMS (461)        [x]
ERR_NOSUCHCHANNEL (403)         [x]
ERR_NOTONCHANNEL (442)          [x]
ERR_CHANOPRIVSNEEDED (482)      [x]

NOT ERRORS TO BE IMPLEMENTED IN JOIN
    RPL_NOTOPIC (331)               
    RPL_TOPIC (332)                 
 */
void	IRCCommandHandler::topic(std::vector<std::string> command, Server &server, Client &client)
{  
    int         fd      = client.getSocket();
    std::string nick    = client.getNickname();

    // ERR_NEEDMOREPARAMS (461)
    if (command.size() < 2) return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(nick, "TOPIC"), fd));

    // ERR_NOSUCHCHANNEL (403)
    if (!server.isValidChannel(command[1])) return (server.sendMessageToClient(ERR_NOSUCHCHANNEL(nick, command[1]), fd));


    Channel *channel = server.getChannel(command[1]);

    // ERR_NOTONCHANNEL (442)
     if (!channel->isMember(fd)) return (server.sendMessageToClient(ERR_NOTONCHANNEL(nick, channel->getName()), fd));

    // ERR_CHANOPRIVSNEEDED (482)
    // TODO MODE if (!channel->isOperator(fd)) return (server.sendMessageToClient(ERR_CHANOPRIVSNEEDED(nick, channel->getName()), fd));


    if (command.size() == 2) 
        return (server.sendMessageToClient(TOPIC_GET_LOG(nick, command[1], channel->getTopic()), fd));

    //Aqui hay que agregar todos los argumentos del mensaje enviado al servidor que estan despues del ":" primero
    std::string new_topic = aggregate(command, 2);


    if (new_topic.size() == 1)
    {
        std::cout << "Clearing the topic on \"" << channel->getName() << "\"" << std::endl;
        channel->setTopic(":No topic is set");
        server.sendMessageToClient(TOPIC_SET_LOG(nick, client.getUsername(), command[1], channel->getTopic()), fd);
    }

    else
    {
        std::cout << " Setting the topic on \"" << channel->getName() << "\" to " << command[2] << std::endl;
        channel->setTopic(new_topic);
        server.sendMessageToClient(TOPIC_SET_LOG(nick, client.getUsername(), command[1], new_topic), fd);
    }
}
