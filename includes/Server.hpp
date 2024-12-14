#ifndef SERVER_HPP
# define SERVER_HPP

# ifndef MAX_EVENTS
#  define MAX_EVENTS 64
# endif

# include <iostream>
# include <map>
# include <vector>
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
//# include "IRCCommandHandler.hpp"
//# include "Channel.hpp"

class Server
{
	private:
		int								_serverSocket;
		int								_epollFd;
		std::string						_password;
		std::map<int, Client>			_clients;
//		std::map<std:string, Channel>	_channels;

		void	_setupServerSocket(int port);
		void	_acceptNewClient();
		void	_handleClientMessage(int clientFd);
		void	_disconnectClient(int clientFd);

	public:
		Server();
		Server(int port, const std::string& password);
		Server(const Server& other);
		Server& operator=(const Server& other);
		~Server();

		void	run();
};

#endif
