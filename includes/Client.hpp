#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Channel.hpp"
# include <string>

class Channel;
class Client
{
	private:
		int			_socket;
		std::string	_nickname;
		std::string	_username;
		bool		_authenticated;
	public:
		Client();
		Client(int socket);
		Client(const Client& other);
		Client&	operator=(const Client& other);
		~Client();

		int		getSocket() const;

		const	std::string&	getNickname() const;
		void	setNickname(const std::string& nickname);

		const	std::string& getUsername() const;
		void	setUsername(const std::string& username);

		bool	isAuthenticated() const;
		void	authenticate();
};

#endif
