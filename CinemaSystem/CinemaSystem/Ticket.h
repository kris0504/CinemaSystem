#pragma once
#include "myString.h"
class Ticket {
private:
    int movieId;
	myString movieName; 
    int row, col;
    double price;
	int hallId;
    myString date, time;
    bool passed;
public:
	Ticket() = default;
	Ticket(int movieId, int row, int col, double price, const myString& date, const myString& time,myString movieName,int hallId)
		: movieId(movieId), row(row), col(col), price(price), date(date), time(time),hallId(hallId),movieName(movieName) {
		passed = false; 
    }
	void setPassed(bool status) { passed = status; }
	bool isPassed() const { return passed; }
	int getRow() const { return row; }
	int getCol() const { return col; }
	double getPrice() const { return price; }
	myString getDate() const { return date; }
	myString getTime() const { return time; }
	int getMovieId() const { return movieId; }
    void printTicket() const;
	
	void serialize(std::ofstream& out) const;
	void deserialize(std::ifstream& in);

};

