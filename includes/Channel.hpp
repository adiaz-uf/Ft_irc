#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include "Server.hpp"
# include "ErrorLogs.hpp"
# include <string>
# include <stdexcept>
# include <map>
# include <set>
# include <vector>



class Server;
class Client;
class Channel
{
	private:
		std::string						_name;
		std::string						_topic;
		std::string						_password;
		
		
		std::map<int, Client*> 			_members;
		std::map<int, Client*>			_operators;
		std::map<int, Client*>			_invited;

		std::set<char>					_modes;
		int								_userLimit;

	public:
		Channel();
		Channel(const std::string& name);
		Channel(const Channel& other);
		Channel&	operator=(const Channel& other);
		~Channel();
		

						//ADD REMOVE
		//IMPORTANT NOTE: FOR THESE YOU *MUST* DO APPROPRIATE CHECKS BEFORE CALLING
		//If fd is already in invited do not add to invited
		void						makeMember			(Server& server, int fd);
		void						removeMember		(int fd);

		void 						invite				(Server& server, int fd);
		void						uninvite			(int fd);

		void						makeOperator		(Server& server, int fd);
		void						removeOperator		(int fd);

		void 						deleteMember		(int fd);

						//"IS IN?" CHECKS
		bool						isInvited			(int fd)									const;
		bool						isMember			(int fd) 									const;
		bool						isOperator			(int fd) 									const;
	
						//TOPIC
		const std::string&			getTopic			() 											const;
		void						setTopic			(const std::string& topic);			
		
						//PASSWORD
		void						setPassword			(const std::string& password);			
		bool						checkPassword		(const std::string& password) 				const;

						//MODE
		bool						hasMode				(char mode) 								const;
		void						setMode				(char mode, bool enable);			
		
						//UserLimit
		void						setUsersLimit		(int limit);			
		int							getUsersLimit		() 											const;

};

#endif
