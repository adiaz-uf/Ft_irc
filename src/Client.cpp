#include "Client.hpp"

Client::Client()
	: _socket(-1), _nickname(""), _username(""), _authenticated(false) {}

Client::Client(int socket)
	: _socket(socket), _nickname(""), _username(""), _authenticated(false) {}

Client::Client(const Client& other)
	: _socket(other._socket),
	  _nickname(other._nickname),
	  _username(other._username),
	  _authenticated(other._authenticated) {}

Client&	Client::operator=(const Client& other)
{
	if (this != &other)
	{
		_socket = other._socket;
		_nickname = other._nickname;
		_username = other._username;
		_authenticated = other._authenticated;
	}
	return *this;
}

Client::~Client() {}

const std::string&	Client::getUsername() const
{
	return _username;
}

void	Client::setUsername(const std::string& username)
{
	_username = username;
}
