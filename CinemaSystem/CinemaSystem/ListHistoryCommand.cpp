#include "ListHistoryCommand.h"
#include "RegularUser.h"
void ListHistoryCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr) {
		std::cout << "You must be logged in to view your history." << std::endl;
		return;
	}
	RegularUser* regUser = dynamic_cast<RegularUser*>(currentUser);
	

	Vector<myString>& history = regUser->getHistory();
	if (history.isEmpty()) {
		std::cout << "You have no history." << std::endl;
		return;
	}

	std::cout << "Your history:" << std::endl;
	for (int i = 0;i<history.getSize();i++) {
		std::cout << history[i]<<" Rating: " << sys.getMovieByName(history[i])->getRating() << std::endl;
	}
}
