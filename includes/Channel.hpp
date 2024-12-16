#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include <string>
# include <map>
# include <set>
# include <vector>

class Channel
{
    private:
        std::vector<Client *>   _clients;
        std::string             _name;
        std::string             _topic;
    public:
        Channel();
        ~Channel();

        void add(Client *lient);
        void remove(Client *client);
        void kick(Client *client, Client *target, const std::string& reason);
        void invite();
        void topic();
        void mode();

        typedef std::vector<Client *>::iterator client_iterator;
};

/*

*/

#endif
