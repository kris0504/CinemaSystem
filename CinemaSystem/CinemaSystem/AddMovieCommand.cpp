#include "AddMovieCommand.h"
#include "ActionMovie.h"
#include "DramaMovie.h"
#include "DocumentaryMovie.h"
void AddMovieCommand::execute(System& sys, User*& currentUser, const Vector<myString>& command) const
{
	if (currentUser == nullptr || !currentUser->isAdminUser()) {
		std::cout << "You must be logged in as an admin to add a movie." << std::endl;
		return;
	}

	/*if (command.getSize() < 2) {
		std::cout << "Usage: addmovie <title> <duration>" << std::endl;
		return;
	}*/

	myString genre = command[1];

	if (genre == "Action")
	{
		if (command.getSize() != 10) {
			std::cout << "Usage: add_movie Action <title> <duration> <releaseYear> <hallId> <date> <startTime> <endTime> <actionIntensity>" << std::endl;
			return;
		}
		myString title = command[2];
		size_t duration = command[3].toSizeT();
		size_t releaseYear = command[4].toSizeT();
		size_t hallId = command[5].toSizeT();
		myString date = command[6];
		myString startTime = command[7];
		myString endTime = command[8];
		int actionIntensity = command[9].toSizeT();
		if (sys.checkMovieExists(date, startTime, endTime, hallId)) {
			std::cout << "A movie already exists at this time. Please choose a different time." << std::endl;
			return;
		}
		Hall& hall = sys.getHallById(hallId);
		int rows = hall.getRows();
		int cols = hall.getCols();
		ActionMovie* newMovie = new ActionMovie(title, duration, releaseYear, genre, hallId, date, startTime, endTime, actionIntensity,rows,cols);
		Vector <Movie*>& movies = sys.getMovies();
		movies.push_back(newMovie);
		hall.getMovieIds().push_back(newMovie->getId());
		std::cout << "Action movie added successfully: " << title << " (" << duration << " minutes) Id: " << newMovie->getId() << std::endl;
		return;
	}
	else if (genre == "Drama") {
		if (command.getSize() != 10) {
			std::cout << "Usage: add_movie Drama <title> <duration> <releaseYear> <hallId> <date> <startTime> <endTime> <hasComedyElement>" << std::endl;
			return;
		}
		myString title = command[2];
		size_t duration = command[3].toSizeT();
		size_t releaseYear = command[4].toSizeT();
		size_t hallId = command[5].toSizeT();
		myString date = command[6];
		myString startTime = command[7];
		myString endTime = command[8];
		bool hasComedyElement = command[10].toSizeT();
		if (sys.checkMovieExists(date, startTime, endTime, hallId)) {
			std::cout << "A movie already exists at this time. Please choose a different time." << std::endl;
			return;
		}
		Hall& hall = sys.getHallById(hallId);
		int rows = hall.getRows();
		int cols = hall.getCols();
		Movie* newMovie = new DramaMovie(title, duration, releaseYear, genre, hallId, date, startTime, endTime, hasComedyElement,rows,cols);
		Vector <Movie*>& movies = sys.getMovies();
		movies.push_back(newMovie);
		
		hall.getMovieIds().push_back(newMovie->getId());
		std::cout << "Drama movie added successfully: " << title << " (" << duration << " minutes) Id: " << newMovie->getId() << std::endl;
		return;

	}
	else if (genre == "Documentary") {
		if (command.getSize() != 11) {
			std::cout << "Usage: add_movie Documentary <title> <duration> <releaseYear> <hallId> <date> <startTime> <endTime> <theme> <isBasedOnTrueEvents>" << std::endl;
			return;
		}
		myString title = command[2];
		size_t duration = command[3].toSizeT();
		size_t releaseYear = command[4].toSizeT();
		size_t hallId = command[5].toSizeT();
		myString date = command[6];
		myString startTime = command[7];
		myString endTime = command[8];
		myString theme = command[9];
		bool isBasedOnTrueEvents = command[10].toSizeT();
		if (sys.checkMovieExists(date, startTime, endTime, hallId)) {
			std::cout << "A movie already exists at this time. Please choose a different time." << std::endl;
			return;
		}
		Hall& hall = sys.getHallById(hallId);
		int rows = hall.getRows();
		int cols = hall.getCols();
		DocumentaryMovie* newMovie = new DocumentaryMovie(title, duration, releaseYear, genre, hallId, date, startTime, endTime, theme, isBasedOnTrueEvents,rows,cols);
		Vector <Movie*>& movies = sys.getMovies();
		movies.push_back(newMovie);
	
		hall.getMovieIds().push_back(newMovie->getId());
		std::cout << "Documentary movie added successfully: " << title << " (" << duration << " minutes) Id: " << newMovie->getId() << std::endl;
		return;
	}
	else {
		std::cout << "Invalid genre. Supported genres are: Action, Drama, Documentary." << std::endl;
		return;

	}
}