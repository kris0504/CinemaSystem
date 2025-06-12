#include "BuyTicketCommand.h"

void BuyTicketCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr) {
		std::cout << "You must be logged in to buy a ticket." << std::endl;
		return;
	}

	if (command.getSize() < 4) {
		std::cout << "Usage: buy_ticket <movieId> <row> <col>" << std::endl;
		return;
	}

	int movieId = command[1].toSizeT();
	int row = command[2].toSizeT();
	int col = command[3].toSizeT();
	if (sys.buyTicket(movieId, row, col, currentUser)) {
		std::cout << "Ticket purchased successfully." << std::endl;
	}
	else {
		std::cout << "Failed to purchase ticket. Please check the movie ID and seat availability." << std::endl;
	}

}
