#include "Server.hpp"

Server::Server()
	: _serverName("IRCSERVER"), _serverSocket(-1), _password("") {}

Server::Server(int port, const std::string& password)
	: _serverName("IRCSERVER"), _serverSocket(-1), _password(password)
{
	_setupServerSocket(port);
}

Server::Server(const Server& other)
	: _serverName("IRCSERVER"),
	  _serverSocket(-1),
	  _password(other._password),
	  _clients(other._clients),
	  _channels(other._channels)
{
	if (other._serverSocket >= 0)
		throw std::logic_error("Socket duplication not allowed");
}

Server&	Server::operator=(const Server& other)
{
	if (this != &other)
	{
		if (_serverSocket >= 0)
			close(_serverSocket);
		_serverSocket = -1;
		_password = other._password;
		_clients = other._clients;
		_channels = other._channels;
	}
	return *this;
}

Server::~Server()
{
	if (_serverSocket >= 0)
		close(_serverSocket);
	if (_epollFd >= 0)
		close(_epollFd);
}

bool 		Server::isValidChannel(std::string channel) 
{
    return (this->_channels.find(channel) != this->_channels.end());
}

bool 		Server::isValidClient(int fd)  
{
    return (this->_clients.find(fd) != this->_clients.end());
}

bool 		Server::isValidClient(std::string client) 
{
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if ((it->second).getNickname() == client)
			return (true);
	return (false);
}

bool		Server::isClientAuthorized(int fd)
{
    return (_clients.find(fd) != _clients.end());
}

Client*		Server::getClient(int fd)
{
	std::map<int, Client>::iterator it = _clients.find(fd);
	if (it != _clients.end())
		return &(it->second);
	return NULL;
//	return &(this->_clients.at(fd));
}

Client*		Server::getClient(std::string client)
{
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if ((it->second).getNickname() == client)
			return (&(it->second));
			
	/*shouldnt get to this line*/
	return(NULL); 	
}

std::map<std::string, Channel>*	Server::getChannels()
{
	return &_channels;
}

Channel*	Server::getChannel(std::string channel)
{
	if (this->_channels.find(channel) != this->_channels.end())
		return &(this->_channels.at(channel));
	return (NULL);
}

std::string	Server::getPassword()
{
	return _password;
}

void Server::addChannel(std::string channel)
{
	
	Channel newchannel = Channel(channel);
	this->_channels[channel] = newchannel;
}

void		Server::_setupServerSocket(int port)
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocket == -1)
		throw std::runtime_error("Failed to create socket");
	int	opt = 1;
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Failed to set socket options");
	struct sockaddr_in	serverAddr = {};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);
	if (bind(_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
		throw std::runtime_error("Failed to bind socket");
	if (listen(_serverSocket, 10) == -1)
		throw std::runtime_error("Failed to listen on socket");

	fcntl(_serverSocket, F_SETFL, O_NONBLOCK);
	
	_epollFd = epoll_create1(0);
	if (_epollFd == -1)
		throw std::runtime_error("Failed to create epoll instance");
	struct epoll_event	ev = {};
	ev.events = EPOLLIN;
	ev.data.fd = _serverSocket;
	if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, _serverSocket, &ev) == -1)
		throw std::runtime_error("Failed to add server socket to epoll");
	std::cout << "Server started on port " << port << std::endl;
}

void		Server::_acceptNewClient()
{
	struct sockaddr_in	clientAddr;
	socklen_t	clientLen = sizeof(clientAddr);
	int	clientSocket = accept(_serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
	if (clientSocket == -1)
		return ;
	
	fcntl(clientSocket, F_SETFL, O_NONBLOCK);

	struct epoll_event	ev = {};
	ev.events = EPOLLIN;
	ev.data.fd = clientSocket;
	if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, clientSocket, &ev) == -1)
	{
		close(clientSocket);
		return ;
	}
	_clients[clientSocket] = Client(clientSocket);
	std::cout << "New client connected but not authorized: " << clientSocket << std::endl;
}

void		Server::_handleClientMessage(int clientFd)
{
	char	buffer[512];
	std::string*	cbuffer = getClient(clientFd)->getBuffer();
	std::memset(buffer, 0, sizeof(buffer));

	int	bytesReceived = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
	if (bytesReceived <= 0)
		return disconnectClient(clientFd);
	if (strcmp(buffer, "\n") || strcmp(buffer, ""))
	{
		std::string	message(buffer);
		cbuffer->append(message);
	}	
	while (cbuffer->find("\n") != std::string::npos)
	{
 		if (cbuffer->find("\n") != 0)
			IRCCommandHandler::handleCommand(*this, _clients[clientFd], cbuffer->substr(0,cbuffer->find("\n")));
		cbuffer->erase(0, cbuffer->find("\n") + 1);
	}
}


// Logic Question? when is client removed from all channel maps?
void		Server::disconnectClient(int clientFd)
{
	std::cout << "Client disconnected: " << clientFd << std::endl;
	
	if (epoll_ctl(_epollFd, EPOLL_CTL_DEL, clientFd, NULL) == -1)
		std::cerr << "Failed to remove client FD from epoll: " << clientFd << std::endl;
	close(clientFd);
	deleteMemberAllChannels(clientFd);
	_clients.erase(clientFd);
}

void Server::run()
{
	struct epoll_event	events[MAX_EVENTS];

	while (true)
	{
		int	numEvents = epoll_wait(_epollFd, events, MAX_EVENTS, -1);
		if (numEvents == -1)
			throw std::runtime_error("epoll_wait failed");
		for (int i = 0; i < numEvents; ++i)
		{
			if (events[i].data.fd == _serverSocket)
				_acceptNewClient();
			else if (events[i].events & (EPOLLERR | EPOLLRDHUP | EPOLLHUP))
				disconnectClient(events[i].data.fd);
			else if (events[i].events & EPOLLIN)
				_handleClientMessage(events[i].data.fd);
		}
		/* for (std::map<int, Client>::iterator it = _clients.begin();
				it != _clients.end(); ++it)
			if (static_cast<long int>(std::time(0) - it->second.getTime()) > 5)
			{
				sendMessageToClient(QUIT_LOG(_serverName, it->second.getNickname()), it->second.getSocket());
				_disconnectClient(it->first);
			} */
	}
}


void		Server::deleteMemberAllChannels(int fd)
{
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it!=_channels.end(); it++)
		it->second.deleteMember(fd);
}

bool		Server::nickValid(std::string name, int fd)
{
	(void)fd;
	//Reglas de documentacion de IRC
		//They MUST NOT contain any of the following characters: space (' ', 0x20), comma (',', 0x2C), asterisk ('*', 0x2A), question mark ('?', 0x3F), exclamation mark ('!', 0x21), at sign ('@', 0x40).
		//They MUST NOT start with any of the following characters: dollar ('$', 0x24), colon (':', 0x3A).
		//They MUST NOT start with a character listed as a channel type, channel membership prefix, or prefix listed in the IRCv3 multi-prefix Extension.
		//They SHOULD NOT contain any dot character ('.', 0x2E).
	//Creo que hexchat tiene reglas distintas
	if (name.find_first_not_of("1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`|^_-{}[]\\") != std::string::npos)
	{
		//SEND MESSAGE TO CLIENT
		// @time=2024-12-21T08:25:19.065Z :osmium.libera.chat 432 bmatos-d 2asdasd :Erroneous Nickname
		return (false);
	}
	
	if (name.find_first_of("1234567890-") == 0)
	{
		//SEND MESSAGE TO CLIENT
		// @time=2024-12-21T08:25:19.065Z :osmium.libera.chat 432 bmatos-d 2asdasd :Erroneous Nickname
		return (false);
	}
	
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if (it->second.getNickname() == name)
		{
			//MESSAGE TO CLIENT
			//@time=2024-12-21T08:22:56.797Z :osmium.libera.chat 433 bmatos-d asdasd :Nickname is already in use.
			return (false);
		}

	return (true);
}

void	Server::sendMessageToClient(const std::string& message, int clientFd)
{
	if (send(clientFd, message.c_str(), message.length(), 0) == -1)
		std::cerr <<"Error sending message to Client FD : " << clientFd << std::endl;
}

void	Server::broadcastToEveryone(const std::string& message, const Server& server)
{
	for (std::map<int, Client>::const_iterator it = server._clients.begin();
			it != server._clients.end(); ++it)
	{
		int	fd = it->first;
		if (send(fd, message.c_str(), message.length(), 0) == -1)
			std::cerr << "Error broadcasting to FD : " << fd << std::endl;
	}
}
