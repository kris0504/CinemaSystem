#pragma once
#include "Movie.h"
class DocumentaryMovie : public Movie {
private:
    myString theme;
    bool isBasedOnTrueEvents;

public:
	DocumentaryMovie() = default;
    DocumentaryMovie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId, myString date, myString startTime, myString endTime, myString theme,bool isBasedOnTrueEvents);
     myString getType() const override; // Returns the type of the movie (e.g., "Action", "Drama", etc.)

    double calculatePrice() const override;
    void printDetails() const override;
};


