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


//TODO CHANNEL INFO

 static void handle_i(std::vector<std::string> command, Server &server, Client &client, std::string oper, int *it)
{
    Channel* channel = server.getChannel(command[1]);
    (void)it;

    if (oper == "+" && !channel->hasMode(INVITE_ONLY))
    {
        channel->setMode(INVITE_ONLY, ON);
        channel->broadcastMessage(MODE_I_T_L_TOGGLE(client.getNickname(), client.getUsername(), channel->getName(), oper, std::string("i")), 0);
    }
    if (oper == "-" && channel->hasMode(INVITE_ONLY))
    {
        channel->setMode(INVITE_ONLY, OFF);
        channel->broadcastMessage(MODE_I_T_L_TOGGLE(client.getNickname(), client.getUsername(), channel->getName(), oper, std::string("i")), 0);
    }
}

static void handle_t(std::vector<std::string> command, Server &server, Client &client, std::string oper, int *it)
{
    Channel* channel = server.getChannel(command[1]);
    (void)it;

    if (oper == "+" && !channel->hasMode(TOPIC_PROTECTED))
    {
        channel->setMode(TOPIC_PROTECTED, ON);  
        channel->broadcastMessage(MODE_I_T_L_TOGGLE(client.getNickname(), client.getUsername(), channel->getName(), oper, std::string("t")), 0);
    }
    if (oper == "-" && channel->hasMode(TOPIC_PROTECTED))
    {
        channel->setMode(TOPIC_PROTECTED, OFF);
        channel->broadcastMessage(MODE_I_T_L_TOGGLE(client.getNickname(), client.getUsername(), channel->getName(), oper, std::string("t")), 0);
    }
}

static void handle_o(std::vector<std::string> command, Server &server, Client &client, std::string oper, int *it)
{
    Channel *channel = server.getChannel(command[1]);
    Client  *target;
    if (*it >= (int)command.size())                                         return ;
    target = server.getClient(command[*it]); (*it)++;
    
    if (target == NULL)                                                     return ;
    if (!channel->isMember(target->getSocket()))                            return ;

    if (oper == "+" &&  channel->isOperator(target->getSocket()))           return ;
    if (oper == "-" && !channel->isOperator(target->getSocket()))           return ;

    if (oper == "+") channel->  makeOperator(server, target->getSocket());
    if (oper == "-") channel->removeOperator(        target->getSocket());

    channel->broadcastMessage(MODE_O_TOGGLE(client.getNickname(), client.getUsername(), channel->getName(), oper, target->getNickname()), 0);
    
}

static void handle_l(std::vector<std::string> command, Server &server, Client &client, std::string oper, int *it)
{
    Channel* channel = server.getChannel(command[1]);
    if (oper == "+")
    {
        if (*it < (int)command.size() && command[*it].find_first_not_of("0123456789") == std::string::npos)
        {
            channel->setMode(SIZE_LIMIT, ON);  
            channel->setUsersLimit(atoi(command[*it].c_str()));
            channel->broadcastMessage(MODE_L_ON(client.getNickname(), client.getUsername(), channel->getName(), oper, std::string("l"), command[*it]), 0);
        }
        (*it)++;
    }
    if (oper == "-" && channel->hasMode(SIZE_LIMIT))
    {
        channel->setMode(SIZE_LIMIT, OFF);
        channel->broadcastMessage(MODE_I_T_L_TOGGLE(client.getNickname(), client.getUsername(), channel->getName(), oper, std::string("l")), 0);
    }
}

static void handle_k(std::vector<std::string> command, Server &server, Client &client, std::string oper, int *it)
{
    Channel* channel = server.getChannel(command[1]);
    if (oper == "+")
    {
        if (*it < (int)command.size())
        {
            channel->setMode(KEY_WORD, ON);  
            channel->setPassword(command[*it]);
            channel->broadcastMessage(MODE_K_ON(client.getNickname(), client.getUsername(), channel->getName(), command[*it]), 0);
        }
        (*it)++;
    }
    if (oper == "-" && channel->hasMode(KEY_WORD))
    {
        if (*it < (int)command.size() && channel->checkPassword(command[*it]))
        {
            channel->setMode(KEY_WORD, OFF);
            channel->broadcastMessage(MODE_K_OFF(client.getNickname(), client.getUsername(), channel->getName()), 0);
        }
        (*it)++;
    }
}

void IRCCommandHandler::mode(std::vector<std::string> command, Server &server, Client &client)
{
    std::string oper        = "+";
    int         char_it     = 0;
    int         command_it  = 3;


    if (command.size() < 3)                                                 return  (server.sendMessageToClient(ERR_NEEDMOREPARAMS  (client.getNickname(), "MODE"), client.getSocket()));
    if (!server.isValidChannel(command[1]))                                 return  (server.sendMessageToClient(ERR_NOSUCHCHANNEL   (command[1], server.getChannel(command[1])->getName()), client.getSocket()));
    if (!server.getChannel(command[1])->isOperator(client.getSocket()))     return  (server.sendMessageToClient(ERR_CHANOPRIVSNEEDED(client.getNickname(), server.getChannel(command[1])->getName()), client.getSocket()));
    if (command[2][0] == '-') oper = "-";
    
    while (char_it < (int)command[2].size())
    {
        switch (command[2][char_it])
        {
        case INVITE_ONLY:       handle_i(command, server, client, oper, &command_it); break;
        case OPERATOR_TOGGLE:   handle_o(command, server, client, oper, &command_it); break;
        case SIZE_LIMIT:        handle_l(command, server, client, oper, &command_it); break;
        case KEY_WORD:          handle_k(command, server, client, oper, &command_it); break;
        case TOPIC_PROTECTED:   handle_t(command, server, client, oper, &command_it); break;
        default:;                                                                    
        }
        char_it ++;
    }
}

    
/* 
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
                    channel->setPassword(command[3]);static void handle_i(std::vector<std::string> command, Server &server, Client &client, int it)
{
}


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

	//channel->broadcastMessage(MODE_LOG((client.getNickname()), client.getUsername(), command[1], command[2]), 0);
    */

