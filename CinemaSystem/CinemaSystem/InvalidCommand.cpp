#include "InvalidCommand.h"

void InvalidCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	throw std::invalid_argument("Invalid command: Please try again.");
}
