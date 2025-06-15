#include "ListMoviesCommand.h"

void ListMoviesCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr) {
		std::cout << "You must be logged in to list movies." << std::endl;
		return;
	}
	Vector<Movie*>& movies = sys.getMovies();
	if (movies.isEmpty()) {
		std::cout << "No movies available." << std::endl;
		return;
	}

	for (int i = 0; i < movies.getSize();i++) {
		if (movies[i]->isPassed())continue;
		std::cout << movies[i]->getTitle() << " (" << movies[i]->getReleaseYear() << ")" << " Haul: " << movies[i]->getHallId() <<
			" date: " << movies[i]->getDate()<< " start time: " << movies[i]->getStartTime() << std::endl;
	}
}
