# include "IRCCommandHandler.hpp"

/*
Command: PING: Parameters: <token>

The PING command is sent by either clients or servers to check the other 
side of the connection is still connected and/or to check for connection latency,
at the application layer.

The <token> may be any non-empty string.

When receiving a PING message, clients or servers must reply to it with a PONG 
message with the same <token> value. This allows either to match PONG with 
the PING they reply to, for example to compute latency.

Clients should not send PING during connection registration, though servers 
may accept it. Servers may send PING during connection registration and clients
must reply to them.

ERR_NEEDMOREPARAMS (461)
ERR_NOORIGIN (409)
ERR_NOSUCHSERVER (402)
*/
void IRCCommandHandler::ping(std::vector<std::string> command, Server &server, Client &client)
{    (void)command;
    (void)server;
    (void)client;
    return ;
}