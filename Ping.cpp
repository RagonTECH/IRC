#include "Ping.hpp"
#include "Commands.hpp"

Ping::Ping()
{
}

void Ping::execute(int client_fd)
{
	// Commands *pongcommand = _server->getCommands();
	// pongcommand->commandFinder("PONG", _users);
}

std::string Ping::getName() const
{
	return "PING";
}

std::string Ping::description() const
{
	return  "PING: It pings the server and checks if the connection is live";
}
