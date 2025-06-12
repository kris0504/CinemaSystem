#include "RegularUser.h"

RegularUser::RegularUser(const myString& name, const myString& password, double balance) {
	isAdmin = false;
	this->name = name;
	this->password = password;
	this->balance = balance;
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

