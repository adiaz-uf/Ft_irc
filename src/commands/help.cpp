# include "IRCCommandHandler.hpp"

/*
CUSTOM HELP 
idea: print all commands help


 HELP                                                     ; request generic help
  :server 704 val * :** Help System **                     ; first line
  :server 705 val * :
  :server 705 val * :Try /HELP <command> for specific help,
  :server 705 val * :/HELP USERCMDS to list available
  :server 706 val * :commands, or join the #help channel   ; last line

  HELP PRIVMSG                                             ; request help on PRIVMSG
  :server 704 val PRIVMSG :** The PRIVMSG command **
  :server 705 val PRIVMSG :
  :server 705 val PRIVMSG :The /PRIVMSG command is the main way
  :server 706 val PRIVMSG :to send messages to other users.

  HELP :unknown subject                                    ; request help on "unknown subject"
  :server 524 val * :I do not know anything about this

  HELP :unknown subject
  :server 704 val * :** Help System **
  :server 705 val * :
  :server 705 val * :I do not know anything about this.
  :server 705 val * :
  :server 705 val * :Try /HELP USERCMDS to list available
  :server 706 val * :commands, or join the #help channel

ERR_HELPNOTFOUND (524)
RPL_HELPSTART (704)
RPL_HELPTXT (705)
RPL_ENDOFHELP (706)
*/
void    IRCCommandHandler::help(std::vector<std::string> command, Server &server, Client &client)
{
    (void)command;
    (void)server;
    (void)client;
    return ;
}