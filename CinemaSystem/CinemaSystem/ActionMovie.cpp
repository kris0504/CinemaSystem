#include "ActionMovie.h"

ActionMovie::ActionMovie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId, myString date, myString startTime, myString endTime, int actionIntensity) : Movie(title, durationMinutes, releaseYear, genre, hallId, date, startTime, endTime), actionIntensity(actionIntensity)
{

	if (actionIntensity < 0 || actionIntensity > 20) {
		throw std::invalid_argument("Action intensity must be between 0 and 20.");
	}
	if (durationMinutes <= 0) {
		throw std::invalid_argument("Duration must be a positive integer.");
	}
	if (rating < 0.0 || rating > 10.0) {
		throw std::invalid_argument("Rating must be between 0.0 and 10.0.");
	}
	if (releaseYear < 1888 || releaseYear > 2023) { // Assuming movies started in 1888
		throw std::invalid_argument("Release year must be between 1888 and 2023.");
	}
	if (hallId <= 0) {
		throw std::invalid_argument("Hall ID must be a positive integer.");
	}
	if (title.getSize()==0 || genre.getSize() == 0 || date.getSize() == 0 || startTime.getSize() == 0 || endTime.getSize() == 0) {
		throw std::invalid_argument("Title, genre, date, start time, and end time cannot be empty.");
	}
	price = 9 + (actionIntensity * 1.5);
}

myString ActionMovie::getType() const
{
	return "Action";
}

double ActionMovie::calculatePrice() const
{
    return 0.0;
}

void ActionMovie::printDetails() const
{
}
