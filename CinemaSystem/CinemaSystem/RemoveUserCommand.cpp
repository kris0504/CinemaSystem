#include "RemoveUserCommand.h"

void RemoveUserCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr || !currentUser->isAdminUser()) {
		std::cout << "You must be logged in as an admin to remove a user." << std::endl;
		return;
	}

	if (command.getSize() != 2) {
		std::cout << "Usage: remove_user <id>" << std::endl;
		return;	
	}

	size_t id = command[1].toSizeT();
	User* userToRemove = sys.getUserById(id);

	if (userToRemove == nullptr) {
		std::cout << "User not found." << std::endl;
		return;
	}

	sys.removeUser(userToRemove);
	std::cout << "User '" << userToRemove->getName() << "' has been removed successfully." << std::endl;
}
