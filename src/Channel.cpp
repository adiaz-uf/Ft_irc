# include "Channel.hpp"

/*
   · i: Set/remove Invite-only channel
   · t: Set/remove the restrictions of the TOPIC command to channel operators
   · k: Set/remove the channel key (password)
   · o: Give/take channel operator privilege
   · l: Set/remove the user limit to channel
*/


Channel::Channel()
	: _name(""), _topic(""), _members(), _invited(), _modes(), _userLimit(-1) {}

Channel::Channel(const std::string& name)
	: _name(name), _topic(""), _members(), _invited(), _modes(), _userLimit(-1) {}

Channel::Channel(const Channel& other)
	: _name(other._name),
	  _topic(other._topic),
	  _members(other._members),
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
		_invited = other._invited;
		_modes = other._modes;
		_userLimit = other._userLimit;
	}
	return *this;
}

Channel::~Channel() {}

bool				Channel::isMember  (int fd)                      const
{
	if (_members.find(fd) != _members.end())
		return (true);
	return (false);
}
bool				Channel::isOperator(int fd)                      const
{
	if (_operators.find(fd) != _operators.end())
		return (true);
	return (false);
}
bool				Channel::isInvited (int fd)                      const
{
	if (_invited.find(fd) == _invited.end())
		return (false);
	return	(true);
}

void				Channel::makeOperator		(Server& server, int fd)
{
	Client* client = server.findClient(fd);
	_operators[fd] = client;
}
void	 			Channel::invite				(Server& server, int fd)
{
	Client* client = server.findClient(fd);
	_invited[fd] = client;
}
void				Channel::makeMember			(Server& server, int fd)
{
	Client* client = server.findClient(fd);
	_members[fd] = client;
}

void				Channel::removeMember		(Server& server, int fd)
{
	_members.erase(fd);
}
void				Channel::uninvite			(Server& server, int fd)
{
	_invited.erase(fd);
}
void				Channel::removeOperator		(Server& server, int fd)
{
	_operators.erase(fd);
}

const std::string&	Channel::getTopic			() 								const
{
	return (_topic);
}
void 				Channel::setTopic			(const std::string& topic)
{
	_topic = topic;
}

void				Channel::setPassword		(const std::string& password)
{
	_password = password;
}
bool				Channel::checkPassword		(const std::string& password) 	const
{
	return _password == password;
}

bool				Channel::hasMode	(char mode) 								const
{
	return _modes.find(mode) != _modes.end();
}
void				Channel::setMode   	(char mode, bool enable)
{
	if (enable)
		_modes.insert(mode);
	else
		_modes.erase(mode);
}

void				Channel::setUsersLimit(int limit)
{
	_userLimit = limit;
}

int					Channel::getUsersLimit() const
{
	return _userLimit;
}
