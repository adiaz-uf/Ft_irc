#ifndef IRCCOMMANDHANDLER_HPP
# define IRCCOMMANDHANDLER_HPP

# include "Client.hpp"
# include "Server.hpp"
# include <ctime>
# include <ErrorLogs.hpp>
# include <sstream>
# include <queue>
# include <set>

class Server;
class Client;

class IRCCommandHandler
{
private:
    IRCCommandHandler();

public:
    static void handleCommand(Server &server, Client &client, std::string msg);
    static std::vector<std::string> split_istringstream(std::string str);

    // Commands
    static void pass    (std::vector<std::string> command, Server &server, Client &client);
    static void kick    (std::vector<std::string> command, Server &server, Client &client);
    static void invite  (std::vector<std::string> command, Server &server, Client &client);
    static void	topic   (std::vector<std::string> command, Server &server, Client &client);
    static void join    (std::vector<std::string> command, Server &server, Client &client);
    static void nick    (std::vector<std::string> command, Server &server, Client &client);
    static void user    (std::vector<std::string> command, Server &server, Client &client);
    static void mode    (std::vector<std::string> command, Server &server, Client &client);
    static void privmsg (std::vector<std::string> command, Server &server, Client &client);
    static void quit    (std::vector<std::string> command, Server &server, Client &client);
    static void part    (std::vector<std::string> command, Server &server, Client &client);
    static void who     (std::vector<std::string> command, Server &server, Client &client);
    static void bot     (std::vector<std::string> command, Server &server, Client &client);
};

#endif // IRCCOMMANDHANDLER_HPP
