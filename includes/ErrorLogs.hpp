#ifndef ERRORLOGS_HPP
# define ERRORLOGS_HPP

#include <iostream>
#include <string>

#include <cstdlib>
#include <cstdio>
#include <time.h>





//Comprobado

//@time=2025-01-16T06:38:04.592Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd +i
//@time=2025-01-16T07:03:18.199Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd -l
#define MODE_I_T_L_TOGGLE(op_nick, op_user, channel, operator, mode)            (std::string(":") + (op_nick) + "!~" + (op_user) + " MODE " + (channel) + " " + (operator) + (mode) + "\r\n")

//@time=2025-01-16T22:32:40.782Z :osmium.libera.chat 341 bmatos-d_ bmatos-d__ #asdasdasd
#define INVITER_LOG(client, target, channel) 		                            (std::string(":") + " 341 " + (client) + " " + (target) + " " + (channel) + "\r\n")

//>> @time=2025-01-16T22:32:40.782Z :bmatos-d_!~bmatos-d3@195.55.211.175 INVITE bmatos-d__ :#asdasdasd
#define INVITEE_LOG(cl_nick, cl_user, target, channel) 	                        (std::string(":") + (cl_nick) + "!~" + (cl_user) + " INVITE " + (target) + " :" + (channel) + "\r\n")

//@time=2025-01-16T06:52:26.564Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd +o bmatos-d_
#define MODE_O_TOGGLE(op_nick, op_user, channel, operator, target)              (std::string(":") + (op_nick) + "!~" + (op_user) + " MODE " + (channel) + " " + (operator) + "o " + (target) + "\r\n")

//@time=2025-01-16T06:58:37.908Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd +k asda
#define MODE_K_ON(op_nick, op_user, channel, keyword)                           (std::string(":") + (op_nick) + "!~" + (op_user) + " MODE " + (channel) + " +k " + (keyword) + "\r\n")

//@time=2025-01-16T07:00:04.376Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd -k *
#define MODE_K_OFF(op_nick, op_user, channel)                                   (std::string(":") + (op_nick) + "!~" + (op_user) + " MODE " + (channel) + " -k * " + "\r\n")

//@time=2025-01-16T07:03:18.199Z :bmatos-d3!~bmatos-d3@195.55.211.139 MODE #ajdsknasasdasdasd +l 50
#define MODE_L_ON(op_nick, op_user, channel, operator, mode, limit)             (std::string(":") + (op_nick) + "!~" + (op_user) + " MODE " + (channel) + " +l " + (limit) + "\r\n")

//TODO
#define MODE_RPL(channel, modes)														(std::string(":Operator ") + " MODE " + (channel) + " +" + (modes) +"\r\n")

//@time=2025-01-16T04:03:25.022Z :tantalum.libera.chat 433 bmatos-d3 bmatos-d_ :Nickname is already in use.
#define ERR_NICKNAMEINUSE(clientNick, badNick)                                  (std::string(": ") +  " 433 " + (clientNick) + (badNick) + " :Nickname is already in use\r\n")

//@time=2025-01-16T04:13:16.691Z :iridium.libera.chat 432 bmatos-d3 ? :Erroneous 
#define ERR_ERRONEUSNICKNAME(clientNick, badNick)                               (std::string(": ") +  " 432 " + (clientNick) + (badNick) + " :Erroneous\r\n")

//@time=2025-01-16T04:20:15.396Z :tantalum.libera.chat 462 bmatos-d3 :You are already connected and cannot handshake again
#define ERR_ALREADYREGISTERED(clientNick)                                       ("462 " + (clientNick) + " :You are already connected and cannot handshake again\r\n")

//@time=2025-01-16T06:56:05.876Z :tungsten.libera.chat 475 bmatos-d__ #ajdsknasasdasdasd :Cannot join channel (+k) - bad key
#define ERR_BADCHANNELKEY(clientNick, channel)                                  (std::string(": 475 ") + (clientNick) + " " + (channel) + " :Cannot join channel (+k) - bad key\r\n")

//@time=2025-01-16T07:36:55.731Z :copper.libera.chat 461 bmatos-d3 MODE :Not enough parameters
#define ERR_NEEDMOREPARAMS(clientNick, command)                                 (std::string(": 461 ") + (clientNick) + " " + (command) + " " + ":Not enough parameters" + "\r\n")

//>> @time=2025-01-17T03:43:00.969Z :iridium.libera.chat 471 three22 #asdaaaa :Cannot join channel (+l) - channel is full, try again later
#define ERR_CHANNELISFULL(clientNick, channel)                                  (std::string(": 471 ") + (clientNick) + " " + (channel) + " :Cannot join channel (+l) - channel is full, try again later\r\n")

//@time=2025-01-17T04:12:58.109Z :iridium.libera.chat 473 three22 #asdooooo :Cannot join channel (+i) - you must be invited
#define ERR_INVITEONLYCHAN(clientNick, channel)                                 (std::string(": 473 ") + (clientNick) + " " + (channel) + " :Cannot join channel (+i) - you must be invited\r\n")

//>> @time=2025-01-17T06:38:07.606Z :aafasaaa!~three@195.55.211.175 QUIT :Quit: Leaving
#define QUIT_LOG(nick, user, message)                                           (std::string(":") + (nick) + "!~" + (user) + " QUIT :Quit: "+ (message) + "\r\n")

//@time=2025-01-17T07:41:31.384Z :three223!~three223@195.55.211.139 PART #newchannn
#define PART_LOG(nick, user, channel)                                           (std::string(":") + (nick) + "!~" + (user) + " PART " + (channel) + "\r\n")

//TODO //@time=2025-01-17T10:49:18.142Z :silver.libera.chat 332 three12 #newchan :a
#define TOPIC_GET_LOG(nick, channel, topic)                                     (std::string(": 332 ") + (nick) + " " + (channel) + " " + (topic) + "\r\n") 

//@time=2025-01-17T10:51:11.672Z :three12!~three12@195.55.211.139 TOPIC #newchan :a
#define TOPIC_SET_LOG(nick, user, channel, topic)                               (std::string(":") + (nick) + "!~" + (user) + " TOPIC " + (channel) + " " + (topic) + "\r\n") 

//@time=2025-01-17T11:12:06.091Z :bmatos-d_!~three121@195.55.211.76 JOIN #asd * :realname
#define JOIN_LOG(nick, user, channel) 		                                    (std::string(":") + (nick) + "!~" + (user) + " JOIN " + (channel) + "\r\n")

//@time=2025-01-17T11:13:49.801Z :bmatos-d_!~three121@195.55.211.76 KICK #asdasdasda three121 :three121
#define KICK_LOG(operator, victim, channel, message) 		                    (std::string(":") + (operator) + "!~" + (victim) + " KICK " + (channel) + " " + (victim) + " " + (message) + "\r\n")

//@time=2025-01-17T11:15:19.723Z :three121!~three121@195.55.211.76 PRIVMSG #asdasdasda :asd
#define PRIVMSG_LOG(nick, user, target, message) 		                        (std::string(":") + (nick) + "!~" + (user) + " PRIVMSG " + (target) + " " + (message) + "\r\n")

//@time=2025-01-17T11:15:59.465Z :bmatos-d_!~three121@195.55.211.76 NICK :asswhole
#define NICK_LOG(oldnick, user, newnick)                                        (std::string(":") + (oldnick) + "!~" + (user) + " NICK :" + (newnick) + "\r\n")

//TODO//
#define ERR_PASSWDMISMATCH(clientNick)                                          (": 464 " + (clientNick) + " :ERRONEOUS_PASS Password is incorrect\r\n")

//TODO//
#define ERR_NONICKNAMEGIVEN(clientNick)                                         (": 431 " + (clientNick) + " :Nickname not given\r\n")

//@time=2025-01-17T11:36:03.395Z :tungsten.libera.chat 441 three121 asswhole #asdasdasdaa :They aren't on that channel
#define ERR_USERNOTINCHANNEL(clientNick, targetNick, channel)                   (": 441 "+ (clientNick) + " " + (targetNick) + " " + (channel) + " :They aren't on that channel\r\n")

//TODO//
#define ERR_NOTONCHANNEL(clientNick, channel)                                   (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 442 " + (channel) + " :You're not on that channel\r\n")

//@time=2025-01-17T11:43:55.640Z :tungsten.libera.chat 403 asswhole Libera.Chat :No such channel
#define ERR_NOSUCHCHANNEL(clientNick, channel)                                  (std::string(": 403 ") + (clientNick) + " IRC :No such channel\r\n")

//@time=2025-01-17T11:46:51.651Z :tungsten.libera.chat 482 three121 #asdasdasda :You're not a channel operator
#define ERR_CHANOPRIVSNEEDED(clientNick, channel)                               (std::string(": 482 ") + (clientNick) + " " + (channel) + " :You must be a channel operator to perform this action\r\n")

//@time=2025-01-17T11:52:27.468Z :tungsten.libera.chat 401 asswhole a :No such nick/channel
#define ERR_NOSUCHNICK(clientNick, target)                                      (": 401 " + (clientNick) + " " + (target) + " :No such nick/channel\r\n")

//@time=2025-01-17T11:59:42.002Z :tungsten.libera.chat 443 asswhole three121 #asdasdasda :is already on channel
#define ERR_USERONCHANNEL(clientNick, target, channel)                          (std::string(": 443 ") + (clientNick) + " " + (target) + " " + (channel) + " :is already on channel\r\n")

//TODO
//La ultima cosa que hacer me parece 
//@time=2025-01-17T22:36:22.449Z :copper.libera.chat 352 bmatos-d_ #what ~two21 195.55.211.164 copper.libera.chat bmatos-d_ H :0 realname
//(client) + " " + (channel) + " " + (username) + " " + (host) + " " + (server) + " " + (nick) + " " + (flags) + " " + :(hopcount) + " " + (realname)
#define WHO_ARE_YOU(client, channel, username, host, server, nick, flags, hopcount, realname) (std::string(": 352 ") + (client) + " " + (channel) + " " + (username) + " " + (host) + " " + (server) + " " + (nick) + " H" + (flags) + " :" + (hopcount) + " " + (realname) + "\r\n")

//>> @time=2025-01-17T22:38:07.989Z :copper.libera.chat 315 two21 #ubuntu :End of /WHO list.
#define WHO_END(nick, channel)                                                  (std::string(": 315 ") + (nick) + " " + (channel) + "  :End of /WHO list.\r\n")

#endif // ERRORLOGS_HPP


//-----------------------NO USADOS-------------------------//
/*
#define ERR_TOOMANYCHANNELS(clientNick, channel)                (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 405 " + (channel) + " :You have joined too many channels\r\n")
#define ERR_CANNOTSENDTOCHAN(clientNick, channel)               (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 404 " + (channel) + " :Cannot send to channel\r\n")
#define ERR_INVALIDMODEPARAM(clientNick)                        ("696 " + (clientNick) + " :Invalid mode parameter\r\n")
#define ERR_NOTREGISTERED(clientNick, channel)                  (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 451 " + (channel) + " :You have not registered\r\n")
#define ERR_UNKNOWNCOMMAND(clientNick, command, channel)        (std::string(":") + (clientNick) + " PRIVMSG " + (channel) + " 421 " + (command) + " :Unknown command\r\n")
*/
