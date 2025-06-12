#pragma once
#include "myString.h"
#include "Vector.hpp"
#include "Hall.h"
class Movie {
protected:
	static size_t nextid; // Unique identifier for the movie
	size_t id;
    myString title;
    double rating;
    int rateCount;
    int durationMinutes;
    int releaseYear;
    myString genre;
	Hall hall; 
	int hallId; 
    myString date;
    myString startTime;
    myString endTime;
    double price;
	bool passed;
public:
	Movie() = default; // Default constructor
    Movie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId,
        myString date, myString startTime, myString endTime);
	myString getTitle() const { return title; }
	Hall& getHall() { return hall; }
	double getRating() const { return rating; }
	int getDurationMinutes() const { return durationMinutes; }
	int getReleaseYear() const { return releaseYear; }
	myString getGenre() const { return genre; }
	int getHallId() const { return hallId; }
	int getId() const { return id; } // Returns the unique identifier for the movie
	myString getDate() const { return date; }
	myString getStartTime() const { return startTime; }
	myString getEndTime() const { return endTime; }
	bool isPassed() const { return passed; }
	void setPassed(bool status) { passed = status; }
	double getPrice() const { return price; }
	bool isSeatAvailable(int row, int col) const ;
	void setTitle(myString newTitle) { title = newTitle; }
	void setPrice(double newPrice) { price = newPrice; }
	void setHallId(int newHallId) { hallId = newHallId; }
    void addRating(double rate);
	virtual myString getType() const = 0; // Returns the type of the movie (e.g., "Action", "Drama", etc.)
    virtual double calculatePrice() const = 0;
    virtual void printDetails() const = 0;
    virtual ~Movie() = default;
};


