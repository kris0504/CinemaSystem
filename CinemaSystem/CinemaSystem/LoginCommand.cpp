#include "LoginCommand.h"

void LoginCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser != nullptr) {
		std::cout << "You are already logged in." << std::endl;
		return;
	}

	if (command.getSize() != 3) {
		std::cout << "Usage: login <username> <password>" << std::endl;
		return;
	}

	size_t username = command[1].toSizeT();
	myString password = command[2];

	User* user = sys.login(username,password);
	if (user == nullptr) {
		std::cout << "Invalid username or password." << std::endl;
		return;
	}

	currentUser = user;
	std::cout << "Login successful. Welcome, " << currentUser->getName() << "!" << std::endl;

}
