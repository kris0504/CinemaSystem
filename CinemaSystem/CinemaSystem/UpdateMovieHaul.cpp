#include "UpdateMovieHaul.h"

void UpdateMovieHaul::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr || !currentUser->isAdminUser()) {
		std::cout << "You must be logged in as an admin to update the movie haul." << std::endl;
		return;
	}

	if (command.getSize() < 2) {
		std::cout << "Usage: update_movie_haul <movieId> <newHaul>" << std::endl;
		return;
	}

	int movieId = command[1].toSizeT();
	int newHaul = command[2].toSizeT();
	if (sys.updateMovieHaul(movieId,newHaul)) {
		std::cout << "Movie haul updated successfully "<< std::endl;
	}
	else {
		std::cout << "Failed to update movie haul for: "<< std::endl;
	}
}
