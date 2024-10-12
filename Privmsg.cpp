#include "Privmsg.hpp"

Privmsg::Privmsg()
{
}

void Privmsg::execute(int client_fd)
{
	std::string mes = "MESSAGE " + _users->getNickName() + " : ";
	for (size_t i = 2; i < _args.size(); i++)
	{
		mes += " ";
		mes += _args[i];
	}
	
	std::vector<User*> users = _server->getUsers();
	if(!_args[2].empty())
	{
		for (size_t i = 0; i < users.size(); i++)
		{
			if(users[i]->getNickName() == _args[1])
			{
				_server->sendMessage(users[i]->getClientfd(), mes);
				_server->sendMessage(users[i]->getClientfd(), "\n");
				return;
			}
			if(i == users.size() - 1)
				_server->sendMessage(client_fd, "Error : hata \n");
		}
	}
	else
		_server->sendMessage(client_fd, "Error : arguman eksik \n");
}

std::string Privmsg::getName() const
{
	return "PRIVMSG";
}

std::string Privmsg::description() const
{
	return  "PRIVMSG: Sends a message to a specific user or channel";
}
