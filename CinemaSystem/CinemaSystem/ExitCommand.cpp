#include "ExitCommand.h"

void ExitCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	sys.saveToFile();
	std::cout << "Exiting the system. Goodbye!" << std::endl;
}
