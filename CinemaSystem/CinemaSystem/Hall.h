#pragma once
#include "myString.h"
class Hall {
private:
    static size_t nextid;
    size_t id;
    int rows;
    int cols;
    Vector<Vector<bool>> seats;
	Vector<int> movieIds; 

public:
	Hall() = default; // Default constructor
	Hall(int rows, int cols) : rows(rows), cols(cols) {
        for (size_t i = 0; i < rows; ++i) {
            seats[i] = Vector<bool>(cols);
        }
        id=nextid++;
	}

	size_t getId() const { return id; }
	int getRows() const { return rows; }
	int getCols() const { return cols; }
	Vector<int>& getMovieIds() { return movieIds; }
    void reserveSeat(int row, int col);
    void releaseSeat(int row, int col);
    bool isSeatFree(int row, int col) const;
    void printLayout() const;
    
};
