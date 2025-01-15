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
#define NICK_LOG(oldnick, user, newnick)                    (std::string(":") + (oldnick) + "!~" + (user) + " NICK :" + (newnick) + "\r\n")

/*
#define ERR_NOTREGISTERED(source)                           "451 " + (source) + " " + std::string(":") + "You have not registered" + "\r\n"
#define ERR_ALREADYREGISTERED(source)                       "462 " + (source) + " " + std::string(":") + "You may not register" + "\r\n"
#define ERR_PASSWDMISMATCH(source)                          "464 " + (source) + " " + std::string(":") + "Password is incorrect" + "\r\n"
#define ERR_NONICKNAMEGIVEN(source)                         "431 " + (source) + " " + std::string(":") + "Nickname not given" + "\r\n"
#define ERR_ERRONEUSNICKNAME(source, command)               "432 " + (source) + " " + (command) + " " + std::string(":") + "Erroneus nickname" + "\r\n"
#define ERR_NICKNAMEINUSE(source)                           "433 " + (source) + " " + std::string(":") + "Nickname is already in use" + "\r\n"

#define ERR_UNKNOWNCOMMAND(source, command)                 "421 " + (source) + " " + (command) + " " + std::string(":") + "Unknown (command)" + "\r\n"
#define ERR_NEEDMOREPARAMS(source, command)                 "461 " + (source) + " " + (command) + " " + std::string(":") + "Not enough parameters" + "\r\n"

#define ERR_TOOMANYCHANNELS(source, channel)                "405 " + (source) + " " + (channel) + " " + std::string(":") + "You have joined too many channels" + "\r\n"
#define ERR_NOTONCHANNEL(source, channel)                   "442 " + (source) + " " + (channel) + " " + std::string(":") + "You're not on that channel" + "\r\n"
#define ERR_USERONCHANNEL(source, channel)                  "443 " + (source) + " " + (channel) + " " + std::string(":") + "is already on channel" + "\r\n"
#define ERR_NOSUCHCHANNEL(source, channel)					"403 " + (source) + " " + (channel) + " " + std::string(":") + "No such channel" + "\r\n"
#define ERR_BADCHANNELKEY(source, channel)					"475 " + (source) + " " + (channel) + " " + std::string(":") + "Cannot join channel (+k)" + "\r\n"
#define ERR_CHANNELISFULL(source, channel)                  "471 " + (source) + " " + (channel) + " " + std::string(":") + "Cannot join channel (+l)" + "\r\n"
#define ERR_CANNOTSENDTOCHAN(source, channel)               "404 " + (source) + " " + (channel) + " " + std::string(":") + "Cannot send to channel" + "\r\n"
#define ERR_CHANOPRIVSNEEDED(source, channel)               (std::string(":") + (source) + " PRIVMSG " + (channel) + " 482 "  + (channel) + " :You must be a channel operator to perform this action\r\n")
#define ERR_INVITEONLYCHAN(channel)                         "473 " + (channel) + " " + std::string(":") + "Cannot join channel (+i)" + "\r\n"

#define ERR_NOSUCHNICK(source, nickname)                    "401 " + (source) + " " + (nickname) + " " + std::string(":") + "No such nick/channel" + "\r\n"
#define ERR_USERNOTINCHANNEL(source, nickname, channel)     "441 " + (source) + " " + (nickname) + " " + (channel) + " " + std::string(":") + "They aren't on that channel" + "\r\n"

#define ERR_INVALIDMODEPARAM(source)                        "696 " + (source) + " " + std::string(":") + "Invalid mode parameter" + "\r\n"
*/

#define ERR_NOTREGISTERED(source, channel)                  (std::string(":") + (source) + " PRIVMSG " + (channel) + " 451 " + (channel) + " :You have not registered\r\n")
#define ERR_ALREADYREGISTERED(source)                       ("462 " + (source) + " :You may not register\r\n")
#define ERR_PASSWDMISMATCH(source)                          ("464 " + (source) + " :Password is incorrect\r\n")
#define ERR_NONICKNAMEGIVEN(source)                         ("431 " + (source) + " :Nickname not given\r\n")
#define ERR_ERRONEUSNICKNAME(source, command, channel)      (std::string(":") + (source) + " PRIVMSG " + (channel) + " 432 " + (command) + " :Erroneous nickname\r\n")
#define ERR_NICKNAMEINUSE(source, channel)                  (std::string(":") + (source) + " PRIVMSG " + (channel) + " 433 " + (channel) + " :Nickname is already in use\r\n")

#define ERR_UNKNOWNCOMMAND(source, command, channel)        (std::string(":") + (source) + " PRIVMSG " + (channel) + " 421 " + (command) + " :Unknown command\r\n")
#define ERR_NEEDMOREPARAMS(source, command)                 ("461 " + (source) + " " + (command) + " " + std::string(":") + "Not enough parameters" + "\r\n")
#define ERR_TOOMANYCHANNELS(source, channel)                (std::string(":") + (source) + " PRIVMSG " + (channel) + " 405 " + (channel) + " :You have joined too many channels\r\n")
#define ERR_NOTONCHANNEL(source, channel)                   (std::string(":") + (source) + " PRIVMSG " + (channel) + " 442 " + (channel) + " :You're not on that channel\r\n")
#define ERR_USERONCHANNEL(source, channel)                  (std::string(":") + (source) + " PRIVMSG " + (channel) + " 443 " + (channel) + " :is already on channel\r\n")
#define ERR_NOSUCHCHANNEL(source, channel)                  (std::string(":") + (source) + " PRIVMSG " + (channel) + " 403 " + (channel) + " :No such channel\r\n")
#define ERR_BADCHANNELKEY(source, channel)                  (std::string(":") + (source) + " PRIVMSG " + (channel) + " 475 " + (channel) + " :Cannot join channel (+k)\r\n")
#define ERR_CHANNELISFULL(source, channel)                  (std::string(":") + (source) + " PRIVMSG " + (channel) + " 471 " + (channel) + " :Cannot join channel (+l)\r\n")
#define ERR_CANNOTSENDTOCHAN(source, channel)               (std::string(":") + (source) + " PRIVMSG " + (channel) + " 404 " + (channel) + " :Cannot send to channel\r\n")
#define ERR_CHANOPRIVSNEEDED(source, channel)               (std::string(":") + (source) + " PRIVMSG " + (channel) + " 482 " + (channel) + " :You must be a channel operator to perform this action\r\n")
#define ERR_INVITEONLYCHAN(source, channel)                 (std::string(":") + (source) + " PRIVMSG " + (channel) + " 473 " + (channel) + " :Cannot join channel (+i)\r\n")

#define ERR_NOSUCHNICK(source, nickname)                    ("401 " + (source) + " " + (nickname) + " :No such nick\r\n")
#define ERR_USERNOTINCHANNEL(source, nickname)              ("441 "+ (source) + (nickname) + " :They aren't on that channel\r\n")

#define ERR_INVALIDMODEPARAM(source)                        ("696 " + (source) + " :Invalid mode parameter\r\n")

#endif // ERRORLOGS_HPP
