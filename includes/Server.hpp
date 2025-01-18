#ifndef SERVER_HPP
# define SERVER_HPP

# ifndef MAX_EVENTS
#  define MAX_EVENTS 64
# endif

# include <iostream>
# include <map>
# include <set>
# include <vector>
# include <algorithm>
# include <string>
# include <netinet/in.h>
# include <sys/epoll.h>
# include <cstring>
# include <cstdlib>
# include <string>
# include <unistd.h>
# include <fcntl.h>
# include <arpa/inet.h>
# include "Client.hpp"
# include "Channel.hpp"
# include "IRCCommandHandler.hpp"
# include "Utilities.hpp"

class Client;
class Channel;

class Server
{
	private:
		const std::string				_serverName;
		int								_serverSocket;
		int								_epollFd;
		std::string						_password;
		std::map<int, Client>			_clients;
		std::map<std::string, Channel>	_channels;

		//Suggest making these static non server functions
		void		_setupServerSocket(int port);
		void		_acceptNewClient();
		void		_handleClientMessage(int clientFd);

	public:
		//Suggest removing the constructors we dont need.
		Server();
		Server(int port, const std::string& password);
		Server(const Server& other);
		Server& operator=(const Server& other);
		~Server();

		void							disconnectClient(int clientFd);

		bool							isValidChannel(std::string channel);
		bool							isValidClient(int fd);
		bool							isValidClient(std::string client);
		bool							isClientAuthorized(int fd);

			
		std::map<std::string, Channel> 	*getChannels();
		Channel* 						getChannel(std::string channel);
		Client* 						getClient(std::string client);
		Client* 						getClient				(int fd);

		std::string						getPassword();
		void 							addChannel(std::string channel);
		void							run();

		//Utilities	
		void							deleteMemberAllChannels(int fd);
		int								nickValid(std::string name);
		int								userValid(std::string name);
		void							sendMessageToClient(const std::string& message, int clientFd);
		void							broadcastToEveryone(const std::string& message, const Server& server);
		std::set<int>					getContacts(int fd);

};

#endif
