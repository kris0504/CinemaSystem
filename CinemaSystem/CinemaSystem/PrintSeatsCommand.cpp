#include "PrintSeatsCommand.h"

void PrintSeatsCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	Movie* movie = sys.getMovieById(command[1].toSizeT());
	if  (movie == nullptr) {
		std::cout << "Movie not found." << std::endl;
		return;
	}
	movie->printLayout();
	
}
