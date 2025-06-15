#include "ListUsersCommand.h"

void ListUsersCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr) {
		std::cout << "You must be logged in to view the list of users." << std::endl;
		return;
	}

	if (!currentUser->isAdminUser()) {
		std::cout << "This command is only available for administrators." << std::endl;
		return;
	}

	Vector<User*> users = sys.getUsers();
	if (users.isEmpty()) {
		std::cout << "No users found." << std::endl;
		return;
	}

	std::cout << "List of users:" << std::endl;
	for (int i = 0; i < users.getSize(); i++) {
		std::cout << users[i]->getName() <<" Id: "<<users[i]->getId() << std::endl;
	}
}
