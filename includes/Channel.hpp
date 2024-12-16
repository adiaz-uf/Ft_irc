#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <stdexcept>
# include <map>
# include <set>
# include <vector>

class Channel
{
	private:
		std::string	_name;
		std::string	_topic;
		std::string	_password;
		std::map<std::string, int> _users;
		std::set<std::string>	_invitedUsers;
		std::set<char>	_modes;
		int	_userLimit;

	public:
		Channel();
		Channel(const std::string& name);
		Channel(const Channel& other);
		Channel&	operator=(const Channel& other);
		~Channel();

		void	addUser(const std::string& username, int role);
		void	removeUser(const std::string& username);
		bool	isUserInChannel(const std::string& username) const;
		bool	isOperator(const std::string& username) const;
		std::vector<std::string>	getUsers() const;

		void	invite(const std::string& username);
		bool	isInvited(const std::string& username) const;

		void	setTopic(const std::string& topic);
		const std::string&	getTopic() const;

		void	setMode(char mode, bool enable);
		bool	hasMode(char mode) const;

		void	setUsersLimit(int limit);
		int		getUsersLimit() const;

		void	setPassword(const std::string& password);
		bool	checkPassword(const std::string& password) const;

		void	kick(const std::string& username);
		void	promoteToOperator(const std::string& username);
		void	demoteFromOperator(const std::string& username);
};

#endif
