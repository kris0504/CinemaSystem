#include "ListMoviesCommand.h"

void ListMoviesCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr ) {
		std::cout << "You must be logged in to list movies." << std::endl;
		return;
	}
	Vector<Movie*> movies = sys.getMovies();
	if (movies.isEmpty()) {
		std::cout << "No movies available." << std::endl;
		return;
	}

	for (int i = 0; i = movies.getSize();i++) {
		std::cout << movies[i]->getTitle() << " (" << movies[i]->getReleaseYear() << ")" << std::endl;
	}
}
