#include "RegularUser.h"

RegularUser::RegularUser(const myString& name, const myString& password, double balance):User(name,password,balance) {
	
	
}

void RegularUser::buyTicket(int movieId, int row, int col)
{
}

void RegularUser::rateMovie(int movieId, int rating)
{
}

void RegularUser::printMenu() const
{
}

void RegularUser::serialize(std::ofstream& out) const {
    serializeBase(out);

    size_t ticketCount = tickets.getSize();
    out.write((char*)&ticketCount, sizeof(ticketCount));
    for (size_t i = 0; i < ticketCount; i++) {
        tickets[i].serialize(out);
    }

    size_t ratedCount = ratedMovies.getSize();
    out.write((char*)&ratedCount, sizeof(ratedCount));
    for (size_t i = 0; i < ratedCount; i++) {
        out.write((char*)&ratedMovies[i], sizeof(int));
    }
}

void RegularUser::deserialize(std::ifstream& in) {
    deserializeBase(in);

    size_t ticketCount;
    in.read((char*)&ticketCount, sizeof(ticketCount));
    for (size_t i = 0; i < ticketCount; i++) {
        Ticket t;
        t.deserialize(in);
        tickets.push_back(t);
    }

    size_t ratedCount;
    in.read((char*)&ratedCount, sizeof(ratedCount));
    for (size_t i = 0; i < ratedCount; i++) {
        int movieId;
        in.read((char*)&movieId, sizeof(int));
        ratedMovies.push_back(movieId);
    }
}
