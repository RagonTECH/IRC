#include "Privmsg.hpp"

Privmsg::Privmsg()
{
}

void Privmsg::execute(int client_fd)
{
    std::string mes = ":" + _users->getNickName() + " PRIVMSG " + _args[1] + " : ";
    for (size_t i = 2; i < _args.size(); i++)
    {
        mes += " ";
        mes += _args[i];
    }

    std::vector<User*> users = _server->getUsers();
	std::vector<Channel*> channel = _server->getChannel();
    if (_args.size() > 2)
    {
        if (_args[1][0] == '#')
        {
            std::string channelName = _args[1];
			std::vector<std::string> nemo = _users->getChannelName();
			int d = 0;
			for(std::vector<std::string>::iterator it = nemo.begin(); it != nemo.end(); ++it)
			{
				if((*it).data() != _args[1])
					d++;
			}
			if(d == nemo.size())
			{
				_server->sendError(client_fd, " You cannot send messages to this channel\n");
				return;
			}
 			for (std::vector<User*>::iterator it = users.begin(); it != users.end(); ++it)
 			{
 			    std::vector<std::string> userChannels = (*it)->getChannelName();

 			    for (size_t k = 0; k < userChannels.size(); k++) 
 			    {
 			        if (userChannels[k] == channelName && (*it)->getClientfd() != client_fd) 
 			        {
						std::string userName = (*it)->getNickName();
 			            _server->sendMessage((*it)->getClientfd(), mes + "\n");
 			        }
 			    }
 			}
        }
        else
        {
            for (size_t i = 0; i < users.size(); i++)
            {
                if (users[i]->getNickName() == _args[1])
                {
                    _server->sendMessage(users[i]->getClientfd(), mes + "\n");
                    return;
                }
                if (i == users.size() - 1)
                {
                    _server->sendError(client_fd,  " User not found\n");
                }
            }
        }
    }
    else
    {
        _server->sendError(client_fd, " Argument error \n");
    }
	_args.clear();
}


std::string Privmsg::getName() const
{
	return "PRIVMSG";
}

std::string Privmsg::description() const
{
	return  "PRIVMSG: Sends a message to a specific user or channel";
}
