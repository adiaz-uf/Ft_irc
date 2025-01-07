#ifndef IRCCOMMANDHANDLER_HPP
# define IRCCOMMANDHANDLER_HPP

# include "Client.hpp"
# include "Server.hpp"
# include <ErrorLogs.hpp>
# include <sstream>
# include <queue>

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

    // Commands
    static void kick(std::vector<std::string> command, Server &server, Client &client);
    static void invite(std::vector<std::string> command, Server &server, Client &client);
    static void	topic(std::vector<std::string> command, Server &server, Client &client);
    static void join(std::vector<std::string> command, Server &server, Client &client);
    static void part(std::vector<std::string> command, Server &server, Client &client);
    static void nick(std::vector<std::string> command, Server &server, Client &client);
    static void quit(std::vector<std::string> command, Server &server, Client &client);
    static void ping(std::vector<std::string> command, Server &server, Client &client);
    static void pong(std::vector<std::string> command, Server &server, Client &client);
    static void privmsg(std::vector<std::string> command, Server &server, Client &client);
    static void mode(std::vector<std::string> command, Server &server, Client &client);
    static void help(std::vector<std::string> command, Server &server, Client &client);
    static void notice(std::vector<std::string> command, Server &server, Client &client);
};

#endif // IRCCOMMANDHANDLER_HPP
