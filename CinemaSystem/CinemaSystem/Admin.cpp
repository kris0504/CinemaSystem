#include "Admin.h"


Admin::Admin() : User("Admin","0000",0,true)
{
	id = 0;
}

void Admin::addHall(int rows, int cols)
{
}

void Admin::updateMovieTitle(int movieId, const myString& newTitle)
{
}

void Admin::printMenu() const
{
}

void Admin::serialize(std::ofstream& out) const {
    serializeBase(out); 
}

void Admin::deserialize(std::ifstream& in) {
    deserializeBase(in);
}
