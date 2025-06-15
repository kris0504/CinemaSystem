#pragma once
#include "Movie.h"
class ActionMovie : public Movie {
private:
    int actionIntensity; 

public:
	ActionMovie() = default;
    ActionMovie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId, myString date, myString startTime, myString endTime, int actionIntensity, int rows, int cols);
     myString getType() const override; 
     void serialize(std::ofstream& out) const override;
     void deserialize(std::ifstream& in) override;

    double calculatePrice() const override;
    void printDetails() const override;
};

