# include "Channel.hpp"


Channel::Channel()
{
}

Channel::~Channel()
{
}
void Channel::add(Client *client)
{
    this->_clients.push_back(client);
}

void Channel::remove(Client *client)
{
    client_iterator c_begin = _clients.begin();
    client_iterator c_end = _clients.end();

    while (c_begin != c_end)
    {
        if (*c_begin == client)
            _clients.erase(c_begin);
        c_begin++;
    }
    client->setChannel(NULL);
}

void Channel::kick(Client *client, Client *target, const std::string& reason)
{
    // TODO: authenticate ?
    this->remove(target);
    // TODO: print log message
}

void Channel::invite()
{

}

void Channel::topic()
{

}

void Channel::mode()
{
    /*
    · i: Set/remove Invite-only channel
    · t: Set/remove the restrictions of the TOPIC command to channel operators
    · k: Set/remove the channel key (password)
    · o: Give/take channel operator privilege
    · l: Set/remove the user limit to channel
    */
}

