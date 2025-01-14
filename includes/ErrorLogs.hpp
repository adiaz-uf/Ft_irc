#ifndef ERRORLOGS_HPP
# define ERRORLOGS_HPP

#include <iostream>
#include <string>

#include <cstdlib>
#include <cstdio>
#include <time.h>


//hay que formatear esto bien
#define TOPIC_GET_LOG(nick, channel, topic)                (std::string(": 331 ") + (nick) + " " + (channel) + " :" + (topic) + "\r\n") 

#define TOPIC_SET_LOG(nick, user, channel, topic)                (std::string(":") + (nick) + "!~" + (user) + " TOPIC " + (channel) + " :" + (topic) + "\r\n") 

//#define VTOPIC_SET(nick, channel, topic)              (": 331 " nick  " #"  (channel)  " :" topic "\r\n")

//#define JOIN_LOG(nick, user, channel)                       ":" nick "!~" user " JOIN #" (channel) "\r\n"
#define JOIN_LOG(nick, user, channel) 		(std::string(":") + (nick) + "!~" + (user) + " JOIN " + (channel) + "\r\n")

#define KICK_LOG(operator, victim, channel, message) 		(std::string(":") + (operator) + "!~" + (victim) + " KICK " + (channel) + " " + (victim) + (message) + "\r\n")

#define INVITE_OPERATOR_LOG(operator, victim, channel) 		(std::string(":") + " 341 " + (operator) + " " + (victim) + " " + (channel) + "\r\n")

#define INVITE_CLIENT_LOG(op_nick, op_user, victim, channel) 		(std::string(":") + (op_nick) + "!~" + (op_user) + " INVITE " + (victim) + " :" + (channel) + "\r\n")

#define PRIVMSG_LOG(nick, user, target, message) 		(std::string(":") + (nick) + "!~" + (user) + " PRIVMSG " + (target) + " " + (message) + "\r\n")

#define MODE_LOG(nick, user, channel, mode)                (std::string(":") + (nick) + "!~" + (user) + " MODE " + (channel) + " " + (mode) + "\r\n") 

//#define MODE_UNSET_LOG(nick, user, channel, mode)                (std::string(":") + (nick) + "!~" + (user) + " MODE " + (channel) + " -" + (mode) + "\r\n") 

#define QUIT_LOG(server, nick) 								(std::string(":") + (server) + " ERROR " + "Closing Link: " + (nick) + " (Ping timeout)" + "\r\n")

#define PART_LOG(nick, user, channel)                      (":"(nick)"!~"(user)" PART #"(channel)"\r\n")
#define NICK_LOG(oldnick, user, newnick)                    (":"(oldnick)"!~"(user)" NICK :"(newnick)"\r\n")


#define ERR_NOTREGISTERED(source)                           "451 " + (source) + " :You have not registered"
#define ERR_ALREADYREGISTERED(source)                       "462 " + (source) + " :You may not register"
#define ERR_PASSWDMISMATCH(source)                          "464 " + (source) + " :Password is incorrect"
#define ERR_NONICKNAMEGIVEN(source)                         "431 " + (source) + " :Nickname not given"
#define ERR_ERRONEUSNICKNAME(source, command)               "432 " + (source) + " " + (command) + " :Erroneus nickname"
#define ERR_NICKNAMEINUSE(source)                           "433 " + (source) + " :Nickname is already in use"

#define ERR_UNKNOWNCOMMAND(source, command)                 "421 " + (source) + " " + (command) + " :Unknown (command)"
#define ERR_NEEDMOREPARAMS(source, command)                 "461 " + (source) + " " + (command) + " :Not enough parameters"

#define ERR_TOOMANYCHANNELS(source, channel)                "405 " + (source) + " " + (channel) + " :You have joined too many channels"
#define ERR_NOTONCHANNEL(source, channel)                   "442 " + (source) + " " + (channel) + " :You're not on that channel"
#define ERR_USERONCHANNEL(source, channel)                  "443 " + (source) + " " + (channel) + " :is already on channel"
#define ERR_NOSUCHCHANNEL(source, channel)					"403 " + (source) + " " + (channel) + " :No such channel"
#define ERR_BADCHANNELKEY(source, channel)					"475 " + (source) + " " + (channel) + " :Cannot join channel (+k)"
#define ERR_CHANNELISFULL(source, channel)                  "471 " + (source) + " " + (channel) + " :Cannot join channel (+l)"
#define ERR_CANNOTSENDTOCHAN(source, channel)               "404 " + (source) + " " + (channel) + " :Cannot send to channel"
#define ERR_CHANOPRIVSNEEDED(source, channel)               "482 " + (source) + " " + (channel) + " :You're not channel operator"
#define ERR_INVITEONLYCHAN(channel)                         "473 " + (channel) + " :Cannot join channel (+i)"

#define ERR_NOSUCHNICK(source, nickname)                    "401 " + (source) + " " + (nickname) + " :No such nick/channel"
#define ERR_USERNOTINCHANNEL(source, nickname, channel)     "441 " + (source) + " " + (nickname) + " " + (channel) + " :They aren't on that channel"

#define ERR_INVALIDMODEPARAM(source)                        "696 " + (source) + " :Invalid mode parameter"

#endif // ERRORLOGS_HPP
