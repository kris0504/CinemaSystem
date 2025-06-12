#include "RegisterCommand.h"
#include "RegularUser.h"
void RegisterCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser != nullptr) {
		std::cout << "You are already logged in as " << currentUser->getName() << ". Please log out first." << std::endl;
		return;
	}

	if (command.getSize() < 3) {
		std::cout << "Usage: register <username> <password>" << std::endl;
		return;
	}

	myString name = command[1];
	myString password = command[2];

	
	User* newUser = new RegularUser(name,password,0);
	sys.getUsers().push_back(newUser);
	currentUser = newUser;

	std::cout << "Registration successful! Welcome, " << name << "!" << std::endl;
}
