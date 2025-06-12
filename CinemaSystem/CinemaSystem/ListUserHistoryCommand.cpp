#include "ListUserHistoryCommand.h"
#include "RegularUser.h"
void ListUserHistoryCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr) {
		std::cout << "You must be logged in to view your history." << std::endl;
		return;
	}

	RegularUser* regUser = dynamic_cast<RegularUser*>(currentUser);
	if (!regUser) {
		std::cout << "This command is only available for regular users." << std::endl;
		return;
	}

	Vector<myString> history = regUser->getHistory();
	if (history.isEmpty()) {
		std::cout << "You have no tickets." << std::endl;
		return;
	}

	std::cout << "Your ticket history:" << std::endl;
	for (int i = 0; i < history.getSize(); i++) {
		std::cout<<history[i]<<std::endl;
	}
}
