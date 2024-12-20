# include "User.hpp"

User::User(int auth, std::string nickName, std::string userName):
_authenticate(auth), _nickName(nickName), _userName(userName)
{
}
User::~User()
{

}

void User::setNickname(std::string newNickname)
{
    this->_nickName = newNickname;
}
void User::setUsername(std::string newUsername)
{
    this->_userName = newUsername;
}

void User::setAuthenticate(int authenticate)
{
    this->_authenticate = authenticate;
}

std::string User::getNickname()
{
    return this->_nickName;
}
std::string User::getUsername()
{
    return this->_userName;
}

int User::getAuthenticate()
{
    return this->_authenticate;
}
