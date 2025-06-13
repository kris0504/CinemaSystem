#include "addBalanceCommand.h"

void AddBalanceCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	currentUser->addBalance(command[1].toDouble());
	std::cout << "Balance added successfully. New balance: " << currentUser->getBalance() << std::endl;
}
