#include "RateMovieCommand.h"

void RateMovieCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{

	if (command.getSize() < 3) {
		std::cout << "Usage: rate <movie_name> <rating>" << std::endl;
		return;
	}

	int id=command[1].toSizeT();
	double rating = command[2].toDouble();

	if (rating < 1 || rating > 5) {
		std::cout << "Rating must be between 1 and 5." << std::endl;
		return;
	}
	myString movieName = sys.getMovieNameById(id);
	if (!sys.rateMovie(id, rating)) {
		std::cout << "Failed to rate the movie. Please check the movie name or your rating." << std::endl;
	}
	else {
		std::cout << "Successfully rated the movie '" << movieName << "' with a rating of " << rating << "." << std::endl;
	}
}
