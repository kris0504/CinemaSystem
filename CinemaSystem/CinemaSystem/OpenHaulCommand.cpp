#include "OpenHaulCommand.h"

void OpenHaulCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	Vector<Hall> halls = sys.getHalls();
	halls.push_back(Hall(command[1].toSizeT(),command[2].toSizeT()));

}
