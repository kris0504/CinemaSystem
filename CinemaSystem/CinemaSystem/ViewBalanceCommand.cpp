#include "ViewBalanceCommand.h"

void ViewBalanceCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	
		std::cout << "Your current balance is: " << currentUser->getBalance() << " units." << std::endl;
	
}
