#ifndef IRCCOMMANDHANDLER_HPP
# define IRCCOMMANDHANDLER_HPP

# include "Client.hpp"
# include "Server.hpp"
# include <sstream>

class Server;
class Client;

class IRCCommandHandler
{
private:
    /* data */
public:
    IRCCommandHandler(/* args */);
    ~IRCCommandHandler();

    static void handleCommand(Server &server, Client &client, std::string msg);
    static std::vector<std::string> split_istringstream(std::string str);


};

#endif // IRCCOMMANDHANDLER_HPP
