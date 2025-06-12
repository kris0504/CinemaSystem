#include "User.h"
size_t User::nextid = 1;

Vector<myString>& User::getHistory()
{
	return history;
}

void User::addBalance(double m)
{
	balance += m;
	
}

bool User::isAdminUser() const
{
	return isAdmin;
}
