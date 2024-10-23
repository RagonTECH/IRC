#include "Nick.hpp"

Nick::Nick()
{
}

void Nick::execute(int client_fd)
{
	std::vector<User*> users = _server->getUsers();
	if(_args.size() == 2)
	{
		for (std::vector<User*>::iterator it = users.begin(); it != users.end(); ++it)
		{
		    if ((*it)->getNickName() == _args[1])
		    {
		        _server->sendMessage(client_fd, "Error : Nickname is already in use \n");
		        return;
		    }
		}

		for (std::vector<User*>::iterator it = users.begin(); it != users.end(); ++it)
		{
		    if ((*it)->getClientfd() == client_fd && !_args[1].empty())
		    {
		        (*it)->setNickName(_args[1]);
		        _server->sendMessage(client_fd, "INFO  New Nickname : ");
		        _server->sendMessage(client_fd, (*it)->getNickName() + "\n");
		        break;
		    }
		}
	}
	else
		_server->sendError(client_fd, " Argument is missing\n");
}

std::string Nick::getName() const
{
	return "NICK";
}

std::string Nick::description() const
{
	return   "NICK: Sets or changes the user's nickname.";
}
