/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:25:19 by bmatos-d          #+#    #+#             */
/*   Updated: 2025/01/17 07:25:22 by bmatos-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
	: _socket(-1), _nickname(""), _username(""), _time(std::time(0)), _passProvided(false), _authenticated(false) , _terminal_input("") {}

Client::Client(int socket)
	: _socket(socket), _nickname(""), _username(""), _time(std::time(0)), _passProvided(false), _authenticated(false),  _terminal_input("") {}

Client::Client(const Client& other)
	: _socket(other._socket),
	  _nickname(other._nickname),
	  _username(other._username),
	  _time(other._time),
	  _authenticated(other._authenticated),
	  _terminal_input(other._terminal_input) {}

Client&	Client::operator=(const Client& other)
{
	if (this != &other)
	{
		_socket = other._socket;
		_nickname = other._nickname;
		_username = other._username;
		_time = other._time;
		_authenticated = other._authenticated;
		_terminal_input = other._terminal_input;
	}
	return *this;
}

Client::~Client() {}




int					Client::getSocket() const
{
	return (_socket);
}

const std::string &	Client::getNickname		() const
{
    return this->_nickname;
}

void Client::setNickname(const std::string &nickname)
{
	this->_nickname = nickname;
}

const std::string &	Client::getUsername		() const
{
	return _username;
}

std::string*		Client::getBuffer		() 
{
	return &_terminal_input;
}

void				Client::setUsername		(const std::string& username)
{
	_username = username;
}

std::time_t			Client::getTime()
{
	return _time;
}

bool				Client::isAuthenticated	() const
{
	return (this->_authenticated);
}

void				Client::authenticate	(Server& server)
{
	if (this->getPassProv() && this->getNickname() != "" && this->getUsername() != "")
	{
		_authenticated = true;
		server.sendMessageToClient(("Your client has been successfully connected\r\n"), this->getSocket());
		server.sendMessageToClient("Welcome to myIRC !\r\n", this->getSocket());
	}
	
}

bool	Client::getPassProv() 
{
	return _passProvided;
}
void	Client::setPassPos() 
{
	_passProvided = true;
}