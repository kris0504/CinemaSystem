#include "UpdateMovieTitleCommand.h"

void UpdateMovieTitleCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr || !currentUser->isAdminUser()) {
		std::cout << "You must be logged in as an admin to update movie titles." << std::endl;
		return;
	}

	if (command.getSize() != 3) {
		std::cout << "Usage: updateMovieTitle <movieId> <newTitle>" << std::endl;
		return;
	}

	size_t movieId = command[1].toSizeT();
	myString newTitle = command[2];

	if (sys.updateMovieTitle(movieId, newTitle)) {
		std::cout << "Movie title updated successfully." << std::endl;
	}
	else {
		std::cout << "Failed to update movie title. Movie not found." << std::endl;
	}
}
