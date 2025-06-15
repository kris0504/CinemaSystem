#pragma once
#include "myString.h"
#include "Vector.hpp"
#include "Hall.h"
class Movie {
protected:
	size_t id;
    myString title;
    double rating;
    int rateCount;
    int durationMinutes;
    int releaseYear;
    myString genre;
	Vector<Vector<bool>> hall;
	int hallId; 
	int rows;
	int cols;
    myString date;
    myString startTime;
    myString endTime;
    double price;
	bool passed;
	void serializeBase(std::ofstream& out) const;
	void deserializeBase(std::ifstream& in);
public:
	static size_t nextid;

	Movie() = default; 
    Movie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId,
        myString date, myString startTime, myString endTime,int rows,int cols);
	myString getTitle() const { return title; }
	Vector<Vector<bool>>& getHall() { return hall; }
	double getRating() const { return rating; }
	int getDurationMinutes() const { return durationMinutes; }
	int getReleaseYear() const { return releaseYear; }
	myString getGenre() const { return genre; }
	int getHallId() const { return hallId; }
	int getId() const { return id; } 
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
	virtual myString getType() const = 0; 
    virtual double calculatePrice() const = 0;
    virtual void printDetails() const = 0;
	void reserveSeat(int row, int col);
	void releaseSeat(int row, int col);
	void printLayout() const;
	virtual void serialize(std::ofstream& out) const = 0;
	virtual void deserialize(std::ifstream& in) = 0;
	virtual ~Movie() = default;


	

};


