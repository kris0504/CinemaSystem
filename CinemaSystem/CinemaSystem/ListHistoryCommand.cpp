#include "ListHistoryCommand.h"

void ListHistoryCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr) {
		std::cout << "You must be logged in to view your history." << std::endl;
		return;
	}
	Vector<myString> history = currentUser->getHistory();
	if (history.isEmpty()) {
		std::cout << "You have no history." << std::endl;
		return;
	}

	std::cout << "Your history:" << std::endl;
	for (int i = 0;history.getSize();i++) {
		std::cout << history[i] << std::endl;
	}
}
