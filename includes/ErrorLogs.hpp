#ifndef ERRORLOGS_HPP
# define ERRORLOGS_HPP

#include <iostream>
#include <string>

#include <cstdlib>
#include <cstdio>
#include <time.h>


//hay que formatear esto bien
#define TOPIC_GET_LOG(nick, channel, topic)                     (std::string(": 331 ") + (nick) + " " + (channel) + " " + (topic) + "\r\n") 
#define TOPIC_SET_LOG(nick, user, channel, topic)               (std::string(":") + (nick) + "!~" + (user) + " TOPIC " + (channel) + " " + (topic) + "\r\n") 
#define JOIN_LOG(nick, user, channel) 		                    (std::string(":") + (nick) + "!~" + (user) + " JOIN " + (channel) + "\r\n")
#define KICK_LOG(operator, victim, channel, message) 		    (std::string(":") + (operator) + "!~" + (victim) + " KICK " + (channel) + " " + (victim) + " " + (message) + "\r\n")
#define INVITE_OPERATOR_LOG(operator, victim, channel) 		    (std::string(":") + " 341 " + (operator) + " " + (victim) + " " + (channel) + "\r\n")
#define INVITE_CLIENT_LOG(op_nick, op_user, victim, channel) 	(std::string(":") + (op_nick) + "!~" + (op_user) + " INVITE " + (victim) + " :" + (channel) + "\r\n")
#define PRIVMSG_LOG(nick, user, target, message) 		        (std::string(":") + (nick) + "!~" + (user) + " PRIVMSG " + (target) + " " + (message) + "\r\n")
#define QUIT_LOG(server, nick) 								    (std::string(":") + (server) + " ERROR " + "Closing Link: " + (nick) + " (Ping timeout)" + "\r\n")
#define PART_LOG(nick, user, channel)                           (":"(nick)"!~"(user)" PART #"(channel)"\r\n")
#define NICK_LOG(oldnick, user, newnick)                        (std::string(":") + (oldnick) + "!~" + (user) + " NICK :" + (newnick) + "\r\n")

//#define MODE_UNSET_LOG(nick, user, channel, mode)                (std::string(":") + (nick) + "!~" + (user) + " MODE " + (channel) + " -" + (mode) + "\r\n") 

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

//Comprobado

//@time=2025-01-16T06:38:04.592Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd +i
//@time=2025-01-16T07:03:18.199Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd -l
#define MODE_I_T_L_TOGGLE(op_nick, op_user, channel, operator, mode)  (std::string(":") + (op_nick) + "!~" + (op_user) + " MODE " + (channel) + " " + (operator) + (mode) + "\r\n")

//@time=2025-01-16T06:52:26.564Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd +o bmatos-d_
#define MODE_O_TOGGLE(op_nick, op_user, channel, operator, target)  (std::string(":") + (op_nick) + "!~" + (op_user) + " MODE " + (channel) + " " + (operator) + "o" + (target) + "\r\n")

//@time=2025-01-16T06:58:37.908Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd +k asda
#define MODE_K_ON(op_nick, op_user, channel, operator, keyword)     (std::string(":") + (op_nick) + "!~" + (op_user) + " MODE " + (channel) + " +k " + (keyword) + "\r\n")

//@time=2025-01-16T07:00:04.376Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd -k *
#define MODE_K_OFF(op_nick, op_user, channel, operator)             (std::string(":") + (op_nick) + "!~" + (op_user) + " MODE " + (channel) + " -k * " + "\r\n")

//@time=2025-01-16T07:03:18.199Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd +l 50
#define MODE_L_ON(op_nick, op_user, channel, operator, mode, limit)  (std::string(":") + (op_nick) + "!~" + (op_user) + " MODE " + (channel) + " +l " + (limit) + "\r\n")

//@time=2025-01-16T04:03:25.022Z :tantalum.libera.chat 433 bmatos-d3 bmatos-d_ :Nickname is already in use.
#define ERR_NICKNAMEINUSE(clientNick, badNick)                      (std::string(": ") +  " 433 " + (clientNick) + (badNick) + " :Nickname is already in use\r\n")

//@time=2025-01-16T04:13:16.691Z :iridium.libera.chat 432 bmatos-d3 ? :Erroneous 
#define ERR_ERRONEUSNICKNAME(clientNick, badNick)                   (std::string(": ") +  " 432 " + (clientNick) + (badNick) + " :Erroneous\r\n")

//@time=2025-01-16T04:20:15.396Z :tantalum.libera.chat 462 bmatos-d3 :You are already connected and cannot handshake again
#define ERR_ALREADYREGISTERED(clientNick)                           ("462 " + (clientNick) + " :You are already connected and cannot handshake again\r\n")

//@time=2025-01-16T06:56:05.876Z :tungsten.libera.chat 475 bmatos-d__ #ajdsknasasdasdasd :Cannot join channel (+k) - bad key
#define ERR_BADCHANNELKEY(clientNick, channel)                      (std::string(": 475 ") + (clientNick) + " " + (channel) + " :Cannot join channel (+k) - bad key\r\n")

//@time=2025-01-16T07:36:55.731Z :copper.libera.chat 461 bmatos-d3 MODE :Not enough parameters
#define ERR_NEEDMOREPARAMS(clientNick, command)                 (std::string(": 461 ") + (clientNick) + " " + (command) + " " + ":Not enough parameters" + "\r\n")




//No Comprobado
#define ERR_NOTREGISTERED(clientNick, channel)                  (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 451 " + (channel) + " :You have not registered\r\n")
#define ERR_PASSWDMISMATCH(clientNick)                          ("464 " + (clientNick) + " :Password is incorrect\r\n")
#define ERR_NONICKNAMEGIVEN(clientNick)                         ("431 " + (clientNick) + " :Nickname not given\r\n")
#define ERR_UNKNOWNCOMMAND(clientNick, command, channel)        (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 421 " + (command) + " :Unknown command\r\n")
#define ERR_TOOMANYCHANNELS(clientNick, channel)                (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 405 " + (channel) + " :You have joined too many channels\r\n")
#define ERR_NOTONCHANNEL(clientNick, channel)                   (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 442 " + (channel) + " :You're not on that channel\r\n")
#define ERR_USERONCHANNEL(clientNick, channel)                  (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 443 " + (channel) + " :is already on channel\r\n")
#define ERR_NOSUCHCHANNEL(clientNick, channel)                  (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 403 " + (channel) + " :No such channel\r\n")
#define ERR_CHANNELISFULL(clientNick, channel)                  (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 471 " + (channel) + " :Cannot join channel (+l)\r\n")
#define ERR_CANNOTSENDTOCHAN(clientNick, channel)               (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 404 " + (channel) + " :Cannot send to channel\r\n")
#define ERR_CHANOPRIVSNEEDED(clientNick, channel)               (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 482 " + (channel) + " :You must be a channel operator to perform this action\r\n")
#define ERR_INVITEONLYCHAN(clientNick, channel)                 (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 473 " + (channel) + " :Cannot join channel (+i)\r\n")

#define ERR_NOSUCHNICK(clientNick, targetNick)                    ("401 " + (clientNick) + " " + (targetNick) + " :No such nick\r\n")
#define ERR_USERNOTINCHANNEL(clientNick, targetNick)              ("441 "+ (clientNick) + (targetNick) + " :They aren't on that channel\r\n")

#define ERR_INVALIDMODEPARAM(clientNick)                        ("696 " + (clientNick) + " :Invalid mode parameter\r\n")

#endif // ERRORLOGS_HPP
