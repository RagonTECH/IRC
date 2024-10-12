#ifndef HELP_HPP
#define HELP_HPP

#include "Command.hpp"  // Ensure this includes Commands

class Help : public Command // Inherit from Commands
{
public:
	Help();
	void execute(int client_fd);
	std::string getName() const;
	std::string description() const;
};

#endif
