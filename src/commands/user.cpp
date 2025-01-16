    # include "IRCCommandHandler.hpp"

/*
3.1.3 User message

      Command: USER
   Parameters: <user> <mode> <unused> <realname>

   The USER command is used at the beginning of connection to specify
   the username, hostname and realname of a new user.

 >>> The <realname> may contain space characters<<<

   Numeric Replies:

           ERR_NEEDMOREPARAMS              [x]
           ERR_ALREADYREGISTRED            [x]

   Example:

   USER guest 0 * :Ronnie Reagan   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan".

   USER guest 8 * :Ronnie Reagan   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan", and asking to be set
                                   invisible.
*/





void IRCCommandHandler::user(std::vector<std::string> command, Server &server, Client &client)
{

    //ERR_ALREADYREGISTRED
    if (client.isAuthenticated() == true)
        return (server.sendMessageToClient(ERR_ALREADYREGISTERED(client.getUsername()), client.getSocket()));

    //ERR_NEEDMOREPARAMS
    //>>> The <realname> may contain space characters<<<
    if (command.size() < 5)
		return (server.sendMessageToClient(ERR_NEEDMOREPARAMS(client.getUsername(), command[0]),client.getSocket()));
    
    client.setUsername(command[1]);
}