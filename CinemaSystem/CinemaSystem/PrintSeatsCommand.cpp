#include "PrintSeatsCommand.h"

void PrintSeatsCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	Hall hall = sys.getHallById(command[1].toSizeT());
	if (hall.getId() == 0) {
		std::cout << "Hall not found." << std::endl;
		return;
	}
	std::cout << "Hall ID: " << hall.getId() << std::endl;
	hall.printLayout();
	

}
