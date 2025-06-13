#include "Ticket.h"

void Ticket::printTicket() const
{
	std::cout << "Ticket for movie: " << movieName << std::endl;
	std::cout << "Row: " << row << ", Column: " << col << std::endl;
	std::cout << "Hall: " <<hallId<< std::endl;
	std::cout << "Price: $" << price << std::endl;
	std::cout << "-------------------------" << std::endl;
}
