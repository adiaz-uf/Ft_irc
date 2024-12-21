#include "Client.hpp"

Client::Client()
	: _socket(-1), _nickname(""), _username(""), _authenticated(false) , _terminal_input(""){}

Client::Client(int socket)
	: _socket(socket), _nickname(""), _username(""), _authenticated(false),  _terminal_input(""){}

Client::Client(const Client& other)
	: _socket(other._socket),
	  _nickname(other._nickname),
	  _username(other._username),
	  _authenticated(other._authenticated),
	  _terminal_input(other._terminal_input)
	  {

	  }

Client&	Client::operator=(const Client& other)
{
	if (this != &other)
	{
		_socket = other._socket;
		_nickname = other._nickname;
		_username = other._username;
		_authenticated = other._authenticated;
		_terminal_input = other._terminal_input;
	}
	return *this;
}

Client::~Client() {}

const std::string &Client::getNickname() const
{
    return this->_nickname;
}

const std::string &Client::getUsername() const
{
	return _username;
}

std::string*	Client::getBuffer() 
{
	return &_terminal_input;
}

void	Client::setUsername(const std::string& username)
{
	_username = username;
}
