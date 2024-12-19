# include "Channel.hpp"

/*
   · i: Set/remove Invite-only channel
   · t: Set/remove the restrictions of the TOPIC command to channel operators
   · k: Set/remove the channel key (password)
   · o: Give/take channel operator privilege
   · l: Set/remove the user limit to channel
*/


Channel::Channel()
	: _name(""), _topic(""), _users(), _invitedUsers(), _modes(), _userLimit(-1) {}

Channel::Channel(const std::string& name)
	: _name(name), _topic(""), _users(), _invitedUsers(), _modes(), _userLimit(-1) {}

Channel::Channel(const Channel& other)
	: _name(other._name),
	  _topic(other._topic),
	  _users(other._users),
	  _invitedUsers(other._invitedUsers),
	  _modes(other._modes),
	  _userLimit(other._userLimit) {}

Channel&	Channel::operator=(const Channel& other)
{
	if (this != &other)
	{
		_name = other._name;
		_topic = other._topic;
		_users = other._users;
		_invitedUsers = other._invitedUsers;
		_modes = other._modes;
		_userLimit = other._userLimit;
	}
	return *this;
}

Channel::~Channel() {}

/* 
KICK:  Parameters: <channel> <user> *( "," <user> ) [<comment>]
- KICK #Finnish Matthew           ; Command to kick Matthew from #Finnish
- KICK #Finnish John :Speaking English 
Command to kick John from #Finnish using "Speaking English" as the reason (comment).

ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_CHANOPRIVSNEEDED (482)
ERR_USERNOTINCHANNEL (441)
ERR_NOTONCHANNEL (442)
*/
void	Channel::kick(std::vector<std::string> command, Server &server, Client &client)
{
	if (!server.isValidChannel(command[1]))
		std::cerr << ERR_NOSUCHCHANNEL(client.getUsername() , command[1]) << std::endl;
	else if (command.size() < 3)
		std::cerr << ERR_NEEDMOREPARAMS(client.getUsername(), "KICK") << std::endl;
	else if (client.getChannel()->_name != command[1])
		std::cerr << ERR_USERNOTINCHANNEL(client.getUsername(), client.getNickname(), "KICK") << std::endl;
	else
		_users.erase(command[2]);
}

/* 
INVITE: Parameters: <nickname> <channel>
- INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar
*/
void	Channel::invite(const std::string& username)
{
	_invitedUsers.insert(username);
}

/* 
TOPIC: Parameters: <channel> [<topic>]
- TOPIC #test :New topic    ; Setting the topic on "#test" to "New topic".
- TOPIC #test :             ; Clearing the topic on "#test"
- TOPIC #test               ; Checking the topic for "#test"
 */
void	Channel::setTopic(const std::string& topic)
{
	_topic = topic;
}

/* MODE */
void	Channel::setMode(char mode, bool enable)
{
	if (enable)
		_modes.insert(mode);
	else
		_modes.erase(mode);
}

void	Channel::addUser(const std::string& username, int role)
{
	if (hasMode('i') && _invitedUsers.find(username) == _invitedUsers.end())
		throw std::runtime_error("User must be invited to join this channel.");
	else if (_userLimit != -1 && static_cast<int>(_users.size()) >= _userLimit)
        throw std::runtime_error("User limit exceeded for this channel.");
	_users[username] = role;
}

void	Channel::removeUser(const std::string& username)
{
	_users.erase(username);
}

bool	Channel::isUserInChannel(const std::string& username) const
{
	return _users.find(username) != _users.end();
}

bool	Channel::isOperator(const std::string& username) const
{
	std::map<std::string, int>::const_iterator it = _users.find(username);
	return it != _users.end() && it->second == 1;
}

std::vector<std::string> Channel::getUsers() const
{
	std::vector<std::string>	userList;
	for (std::map<std::string, int>::const_iterator it
			= _users.begin(); it != _users.end(); ++it)
		userList.push_back(it->first);
	return userList;
}

bool	Channel::isInvited(const std::string& username) const
{
	return _invitedUsers.find(username) != _invitedUsers.end();
}

const std::string&	Channel::getTopic() const
{
	return _topic;
}

bool	Channel::hasMode(char mode) const
{
	return _modes.find(mode) != _modes.end();
}

void	Channel::setUsersLimit(int limit)
{
	_userLimit = limit;
}

int		Channel::getUsersLimit() const
{
	return _userLimit;
}

void	Channel::setPassword(const std::string& password)
{
	_password = password;
}

bool	Channel::checkPassword(const std::string& password) const
{
	return _password == password;
}

void	Channel::promoteToOperator(const std::string& username)
{
	if (_users.find(username) != _users.end())
		_users[username] = 1;
}

void	Channel::demoteFromOperator(const std::string& username)
{
	if (_users.find(username) != _users.end())
		_users[username] = 0;
}
