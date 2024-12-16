# include <string>

class User
{
    private:
        int         _authenticate;
        std::string _nickName;
        std::string _userName;
    public:
        User(int auth, std::string nickName, std::string userName);
        ~User();

        // Setters
        void setNickname(std::string newNickname);
        void setUsername(std::string newUsername);
        void setAuthenticate(int authenticate);

        // Getters
        std::string getNickname();
        std::string getUsername();
        int         getAuthenticate();
};
