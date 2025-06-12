#include "RemoveMovieCommand.h"

void RemoveMovieCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr || !currentUser->isAdminUser()) {
		std::cout << "You must be logged in as an admin to remove a movie." << std::endl;
		return;
	}

	if (command.getSize() != 2) {
		std::cout << "Usage: remove_movie <id>" << std::endl;
		return;
	}

	int movieId = command[1].toSizeT();
	if (sys.removeMovie(movieId)) {
		std::cout << "Movie removed successfully." << std::endl;
	}
	else {
		std::cout << "Movie not found." << std::endl;
	}
}
