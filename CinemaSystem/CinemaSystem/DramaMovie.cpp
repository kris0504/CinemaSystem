#include "DramaMovie.h"

DramaMovie::DramaMovie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId, myString date, myString startTime, myString endTime, bool hasComedyElements, int rows, int cols) :
	Movie(title, durationMinutes, releaseYear, genre, hallId, date, startTime, endTime, rows, cols), hasComedyElements(hasComedyElements)

{

	if (durationMinutes <= 0) {
		throw std::invalid_argument("Duration must be a positive integer.");
	}
	if (rating < 0.0 || rating > 10.0) {
		throw std::invalid_argument("Rating must be between 0.0 and 10.0.");
	}
	if (releaseYear < 1888 || releaseYear > 2025) { 
		throw std::invalid_argument("Release year must be between 1888 and 2025.");
	}
	if (hallId <= 0) {
		throw std::invalid_argument("Hall ID must be a positive integer.");
	}
	if (title.getSize() == 0 || genre.getSize() == 0 || date.getSize() == 0 || startTime.getSize() == 0 || endTime.getSize() == 0) {
		throw std::invalid_argument("Title, genre, date, start time, and end time cannot be empty.");
	}
	price = 7 + (hasComedyElements * 2);
}

double DramaMovie::calculatePrice() const
{
	return 0.0;
}

void DramaMovie::printDetails() const
{
}

myString DramaMovie::getType() const
{
	return "Drama";
}
void DramaMovie::serialize(std::ofstream& out) const {
	serializeBase(out);
	out.write((char*)&hasComedyElements, sizeof(hasComedyElements));
}

void DramaMovie::deserialize(std::ifstream& in) {
	deserializeBase(in);
	in.read((char*)&hasComedyElements, sizeof(hasComedyElements));
}
