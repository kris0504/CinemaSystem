#pragma once
#include "User.h"
#include "Ticket.h"
class RegularUser : public User {
private:
    Vector<Ticket> tickets;
    Vector<int> ratedMovies;
    Vector<myString> history;
public:
	RegularUser() = default;
    RegularUser(const myString& name, const myString& password, double balance);
	Vector<Ticket>& getTickets() { return tickets; }
	Vector <myString> getHistory() { return history; }
    void buyTicket(int movieId, int row, int col);
    void rateMovie(int movieId, int rating);
    void printMenu() const override;
};


