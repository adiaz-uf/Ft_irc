#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <map>
# include <set>
# include <vector>

class Channel
{
    private:
        std::vector<std::string> _users;
    public:
        Channel();
        ~Channel();

        void kick();
        void invite();
        void topic();
        void mode();
};

#endif
