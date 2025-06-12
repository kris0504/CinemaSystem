#include "LogoutCommand.h"

void LogoutCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	currentUser = nullptr;
	
	std::cout << "Logged out.\n";
}
