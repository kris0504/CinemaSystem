#include "ListUserHistoryCommand.h"
#include "RegularUser.h"
void ListUserHistoryCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	
	if (currentUser == nullptr) {
		std::cout << "You must be logged in to view your history." << std::endl;
		return;
	}
	
	RegularUser* regUser = dynamic_cast<RegularUser*>(sys.getUserById(command[1].toSizeT()));
	if (!regUser) {
		std::cout << "User not found." << std::endl;
		return;
	}
	/*if (!regUser) {
		std::cout << "This command is only available for regular users." << std::endl;
		return;
	}*/
	if (regUser->getHistory().isEmpty()) throw std::runtime_error("User has no history.");
	Vector<myString>& history = regUser->getHistory();
	if (history.isEmpty()) {
		std::cout << "User has no tickets." << std::endl;
		return;
	}

	std::cout << "Your ticket history:" << std::endl;
	for (int i = 0; i < history.getSize(); i++) {
		std::cout<<history[i]<<std::endl;
	}
}
