#pragma once
#include "Movie.h"
class DramaMovie : public Movie {
private:
    bool hasComedyElements;

public:
	DramaMovie() = default; // Default constructor
    DramaMovie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId, myString date, myString startTime, myString endTime, bool hasComedyElements);
    double calculatePrice() const override;
    void printDetails() const override;
     myString getType() const override; // Returns the type of the movie (e.g., "Action", "Drama", etc.)

};
