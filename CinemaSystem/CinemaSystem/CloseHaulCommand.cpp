#include "CloseHaulCommand.h"

void CloseHaulCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr || !currentUser->isAdminUser()) {
		std::cout << "You must be an admin to close a haul." << std::endl;
		return;
	}

	if (command.getSize() < 2) {
		std::cout << "Usage: close_haul <haul_id>" << std::endl;
		return;
	}

	size_t haulId = command[1].toSizeT();
	if (!sys.closeHaul(haulId)) {
		std::cout << "Failed to close haul with ID: " << haulId << std::endl;
	}
	else {
		std::cout << "Haul with ID: " << haulId << " has been successfully closed." << std::endl;
	}
}
