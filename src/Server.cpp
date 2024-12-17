#include "Server.hpp"

Server::Server()
	: _serverSocket(-1), _password("") {}

Server::Server(int port, const std::string& password)
	: _serverSocket(-1), _password(password)
{
	_setupServerSocket(port);
}

Server::Server(const Server& other)
	: _serverSocket(-1),
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

void	Server::_setupServerSocket(int port)
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

void	Server::_acceptNewClient()
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
	std::cout << "New client connected: " << clientSocket << std::endl;
}

void	Server::_handleClientMessage(int clientFd)
{
	char	buffer[512];
	std::memset(buffer, 0, sizeof(buffer));

	int	bytesReceived = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
	if (bytesReceived <= 0)
	{
		_disconnectClient(clientFd);
		return ;
	}
	std::string	message(buffer);
	std::cout << "Received message from client " << clientFd << ": " <<  message << std::endl;
//	IRCCommandHandler::handleCommand(*this, _clients[clientFd], message);
}

void	Server::_disconnectClient(int clientFd)
{
	std::cout << "Client disconnected: " << clientFd << std::endl;
	if (epoll_ctl(_epollFd, EPOLL_CTL_DEL, clientFd, NULL) == -1)
		std::cerr << "Failed to remove client FD from epoll: " << clientFd << std::endl;
	close(clientFd);
	_clients.erase(clientFd);
}

void	Server::run()
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
				_disconnectClient(events[i].data.fd);
			else if (events[i].events & EPOLLIN)
				_handleClientMessage(events[i].data.fd);
		}
	}
}
