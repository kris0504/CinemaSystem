#pragma once
#include "myString.h"
class Hall {
private:

    size_t id;
    int rows;
    int cols;
	Vector<int> movieIds; 

public:
    static size_t nextid;

	Hall() = default; 
	Hall(int rows, int cols) : rows(rows), cols(cols) {
        /*for (size_t i = 0; i < rows; ++i) {
            seats[i] = Vector<bool>(cols);
        }*/
        id=nextid++;
	}

	size_t getId() const { return id; }
	int getRows() const { return rows; }
	int getCols() const { return cols; }
	Vector<int>& getMovieIds() { return movieIds; }
 
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);

};
