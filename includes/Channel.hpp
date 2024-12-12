# include <string>
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
