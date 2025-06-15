#include "ListUserTicketsCommand.h"
#include "RegularUser.h"
void ListUserTicketsCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	
	User* us = sys.getUserById(command[1].toSizeT());
	RegularUser* regUser = static_cast<RegularUser*>(us);
	if (regUser == nullptr) {
		throw std::invalid_argument("User does not have any tickets.");
		return;
	}
	Vector <Ticket>& tickets = regUser->getTickets();
	//Vector<Ticket> tickets = static_cast<RegularUser*>(currentUser)->getTickets();
	if (tickets.isEmpty()) {
		std::cout << "User has no tickets." << std::endl;
		return;
	}

	std::cout << "Tickets:" << std::endl;
	for (int i = 0; i < tickets.getSize(); i++) {
		tickets[i].printTicket();
	}
}
