#include "OpenHaulCommand.h"

void OpenHaulCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{

	if (command.getSize() != 3) {
		std::cout << "Invalid command format. Usage: openhaul <rows> <cols>" << std::endl;
		return;
	}

	//Vector<Hall> halls =sys.getHalls();
	Hall newHall(command[1].toSizeT(), command[2].toSizeT());
	int id = newHall.getId();
	sys.getHalls().push_back(newHall);
	std::cout << "Successfully opened a new haul with ID: "<< id << std::endl;

}
