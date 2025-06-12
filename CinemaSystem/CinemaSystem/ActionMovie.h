#pragma once
#include "Movie.h"
class ActionMovie : public Movie {
private:
    int actionIntensity; // 0 до 20

public:
	ActionMovie() = default;
    ActionMovie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId, myString date, myString startTime, myString endTime, int actionIntensity);
     myString getType() const override; // Returns the type of the movie (e.g., "Action", "Drama", etc.)

    double calculatePrice() const override;
    void printDetails() const override;
};

