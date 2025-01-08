# include "Channel.hpp"

Channel::Channel()
	: _name(""), _topic("No topic is set"), _members(), _operators(), _invited(), _modes(), _userLimit(-1) {}

Channel::Channel(const std::string& name)
	: _name(name), _topic("No topic is set"), _members(), _operators(), _invited(), _modes(), _userLimit(-1) {}

Channel::Channel(const Channel& other)
	: _name(other._name),
	  _topic(other._topic),
	  _members(other._members),
	  _operators(other._operators),
	  _invited(other._invited),
	  _modes(other._modes),
	  _userLimit(other._userLimit) {}

Channel&	Channel::operator=(const Channel& other)
{
	if (this != &other)
	{
		_name = other._name;
		_topic = other._topic;
		_members = other._members;
		_operators = other._operators;
		_invited = other._invited;
		_modes = other._modes;
		_userLimit = other._userLimit;
	}
	return *this;
}

Channel::~Channel() {}

bool				Channel::isMember  				(int fd)                      	const
{
	if (_members.find(fd) != _members.end())
		return (true);
	return (false);
}
bool				Channel::isOperator				(int fd)                      	const
{
	if (_operators.find(fd) != _operators.end())
		return (true);
	return (false);
}
bool				Channel::isInvited 				(int fd)                      	const
{
	if (_invited.find(fd) == _invited.end())
		return (false);
	return	(true);
}
	
void				Channel::makeOperator			(Server& server, int fd)
{
	Client* client = server.getClient(fd);
	_operators[fd] = client;
}
void	 			Channel::invite					(Server& server, int fd)
{
	Client* client = server.getClient(fd);
	_invited[fd] = client;
}
void				Channel::makeMember				(Server& server, int fd)
{
	Client* client = server.getClient(fd);
	/* if (true) // TODO: channel mode is invite-only
	{
		std::cout << ERR_INVITEONLYCHAN(this->_name) << std::endl;
		return ;
	} */
	_members[fd] = client;
}
	
void				Channel::removeMember			(int fd)
{
	_members.erase(fd);
}
void				Channel::uninvite				(int fd)
{
	_invited.erase(fd);
}
void				Channel::removeOperator			(int fd)
{
	_operators.erase(fd);
}
	
void 				Channel::deleteMember			(int fd)
{
	if (isMember  (fd))	removeMember  (fd);
	if (isInvited (fd))	uninvite      (fd);
	if (isOperator(fd))	removeOperator(fd);
}
	
const std::string&	Channel::getTopic				() 								const
{
	return (_topic);
}
void 				Channel::setTopic				(const std::string& topic)
{
	_topic = topic;
}
	
void				Channel::setPassword			(const std::string& password)
{
	_password = password;
}
bool				Channel::checkPassword			(const std::string& password) 	const
{
	return _password == password;
}
	
bool				Channel::hasMode				(char mode) 					const
{
	return _modes.find(mode) != _modes.end();
}
void				Channel::setMode   				(char mode, bool enable)
{
	if (enable)
		_modes.insert(mode);
	else
		_modes.erase(mode);
}
	
void				Channel::setUsersLimit			(int limit)
{
	_userLimit = limit;
}
	
int					Channel::getUsersLimit			() 								const
{
	return _userLimit;
}

Client* Channel::getMember(std::string username)
{
	for (std::map<int, Client*>::const_iterator it = _members.begin(); it != _members.end(); it++)
		if ((it->second)->getNickname() == username)
			return (it->second);
			
	/*shouldnt get to this line*/
	return(NULL); 	
}

std::string Channel::getName()
{
    return (this->_name);
}

void				Channel::copyMemberToInvite		()
{
	_invited = _members;
}

void				Channel::deleteInviteElements	()
{
	for (std::map<int, Client*>::iterator it = _invited.begin(); it != _invited.end(); it++)
		_invited.erase(it->first);
}

void	Channel::broadcastMessage(const std::string& message, const Channel& channel, int senderFd)
{
	std::cerr << ">>>>>>1<<<<<<" << std::endl;
	for (std::map<int, Client*>::const_iterator it = channel._members.begin();
			it != channel._members.end(); ++it)
	{
		std::cerr << ">>>>>>2<<<<<<" << std::endl;
		int	fd = it->first;
		std::cerr << "fd : " << fd <<std::endl;
		if (fd != senderFd)
		{
			if (send(fd, message.c_str(), message.length(), 0) == -1)
				std::cerr << "Error broadcasting to FD : " << fd << std::endl;
		}
	}
}
