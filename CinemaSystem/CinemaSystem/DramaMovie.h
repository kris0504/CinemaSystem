#pragma once
#include "Movie.h"
class DramaMovie : public Movie {
private:
    bool hasComedyElements;

public:
	DramaMovie() = default; 
    DramaMovie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId, myString date, myString startTime, myString endTime, bool hasComedyElements, int rows, int cols);
    double calculatePrice() const override;
    void printDetails() const override;
     myString getType() const override; 
     void serialize(std::ofstream& out) const override;
     void deserialize(std::ifstream& in) override;

};
