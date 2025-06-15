#include "Ticket.h"

void Ticket::printTicket() const
{
	std::cout << "Ticket for movie: " << movieName << std::endl;
	std::cout << "Row: " << row << ", Column: " << col << std::endl;
	std::cout << "Hall: " <<hallId<< std::endl;
	std::cout << "Price: $" << price << std::endl;
	std::cout << "-------------------------" << std::endl;
}

void Ticket::serialize(std::ofstream& out) const {
    out.write((char*)&movieId, sizeof(movieId));
    movieName.serialize(out);
    out.write((char*)&row, sizeof(row));
    out.write((char*)&col, sizeof(col));
    out.write((char*)&price, sizeof(price));
    out.write((char*)&hallId, sizeof(hallId));
    date.serialize(out);
    time.serialize(out);
    out.write((char*)&passed, sizeof(passed));
}

void Ticket::deserialize(std::ifstream& in) {
    in.read((char*)&movieId, sizeof(movieId));
    movieName.deserialize(in);
    in.read((char*)&row, sizeof(row));
    in.read((char*)&col, sizeof(col));
    in.read((char*)&price, sizeof(price));
    in.read((char*)&hallId, sizeof(hallId));
    date.deserialize(in);
    time.deserialize(in);
    in.read((char*)&passed, sizeof(passed));

}
