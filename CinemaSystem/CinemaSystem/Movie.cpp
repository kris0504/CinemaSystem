#include "Movie.h"
size_t Movie::nextid = 0;

Movie::Movie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId, myString date, myString startTime, myString endTime) : title(title), rating(0), durationMinutes(durationMinutes), releaseYear(releaseYear),
genre(genre), hallId(hallId), date(date), startTime(startTime), endTime(endTime) 
{
	
	passed = false;
	id++;
}

bool Movie::isSeatAvailable(int row, int col) const
{
	return hall.isSeatFree(row, col);
}

void Movie::addRating(double rate)
{
	if (rate < 0 || rate > 5) {
		throw std::invalid_argument("Rating must be between 0 and 5.");
	}
	rating = (rating * rateCount + rate) / (++rateCount);
}


