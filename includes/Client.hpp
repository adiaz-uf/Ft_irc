#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Channel.hpp"
# include <string>
# include <map>

class Channel;
class Client
{
	private:
		int			_socket;
		std::string	_nickname;
		std::string	_username;
		bool		_authenticated;
		std::string _terminal_input;
		std::map<std::string, Channel> _channels;

	public:
		Client();
		Client(int socket);
		Client(const Client& other);
		Client&	operator=(const Client& other);
		~Client();

		int						getSocket() const;
		std::string*			getBuffer();

		const	std::string&	getNickname() const;
		void					setNickname(const std::string& nickname);

		const	std::string&	getUsername() const;
		void					setUsername(const std::string& username);

		bool					isAuthenticated() const;
		void					authenticate();
};

#endif
