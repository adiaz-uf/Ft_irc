/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiaz-uf <adiaz-uf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:26 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/21 11:42:56 by adiaz-uf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}

Client*		Server::getClient(std::string client)
{
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if ((it->second).getNickname() == client)
			return (&(it->second));
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
	std::cout << "Client connected: " << clientSocket << std::endl;
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
	sendMessageToClient("Please set username (USER), nickname (NICK) and enter the server password (PASS).\n", clientSocket);
}

int Server::getClientsCount()
{
    return this->_clients.size();
}

std::set<int> Server::getContacts(int fd)
{
	std::set<int> ret;
	for (std::map<std::string, Channel>::iterator ch = _channels.begin(); ch != _channels.end(); ch++)
	{
		if ((*ch).second.isMember(fd))
			for (std::map<int, Client*>::iterator cl = (*ch).second.getMembers()->begin(); cl != (*ch).second.getMembers()->end(); cl++)
				ret.insert(cl->first);
	}
	return (ret);
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
		if (_clients.count(clientFd) == 0)
			return ;
		cbuffer->erase(0, cbuffer->find("\n") + 1);
	}
}

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
	}
}

void		Server::deleteMemberAllChannels(int fd)
{
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it!=_channels.end(); it++)
		it->second.deleteMember(fd);
}

int		Server::nickValid(std::string name)
{
	if (name.find_first_not_of("1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`|^_-{}[]\\") != std::string::npos || name.find_first_of("1234567890-") == 0)
		return (1);
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if (it->second.getNickname() == name)
			return (2);
	return (3);
}

int		Server::userValid(std::string name)
{

	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if (it->second.getUsername() == name)
			return (1);
	return (0);
}

void	Server::sendMessageToClient(const std::string& message, int clientFd)
{
	if (send(clientFd, message.c_str(), message.length(), 0) == -1)
		std::cerr << "Error sending message to Client FD : " << clientFd << std::endl;
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
