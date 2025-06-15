#pragma once
#include "Movie.h"
class DocumentaryMovie : public Movie {
private:
    myString theme;
    bool isBasedOnTrueEvents;

public:
	DocumentaryMovie() = default;
    DocumentaryMovie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId, myString date, myString startTime, myString endTime, myString theme,bool isBasedOnTrueEvents, int rows, int cols);
     myString getType() const override;
     void serialize(std::ofstream& out) const override;
     void deserialize(std::ifstream& in) override;

    double calculatePrice() const override;
    void printDetails() const override;
};


