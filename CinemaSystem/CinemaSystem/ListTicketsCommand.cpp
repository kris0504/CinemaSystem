#include "ListTicketsCommand.h"
#include "RegularUser.h"
class Ticket;
void ListTicketsCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr) {
		std::cout << "You must be logged in to view your tickets." << std::endl;
		return;
	}
	RegularUser* regUser = static_cast<RegularUser*>(currentUser);
	Vector <Ticket>& tickets = regUser->getTickets();
	//Vector<Ticket> tickets = static_cast<RegularUser*>(currentUser)->getTickets();
	if (tickets.isEmpty()) {
		std::cout << "You have no tickets." << std::endl;
		return;
	}

	std::cout << "Your tickets:" << std::endl;
	for (int i = 0; i < tickets.getSize(); i++) {
		tickets[i].printTicket();
	}
}
