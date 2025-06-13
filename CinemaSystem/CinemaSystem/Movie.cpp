#include "Movie.h"
size_t Movie::nextid = 1;

Movie::Movie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId, myString date, myString startTime, myString endTime, int rows, int cols) : title(title), rating(0), durationMinutes(durationMinutes), releaseYear(releaseYear),
genre(genre), hallId(hallId), date(date), startTime(startTime), endTime(endTime) 
{
	this->rows = rows;
	this->cols = cols;
	for (size_t i = 0; i < rows; ++i) {
		hall[i] = Vector<bool>(cols);
	}
	passed = false;
	id = nextid++;

}

bool Movie::isSeatAvailable(int row, int col) const
{
	return !hall[row][col];
}

void Movie::addRating(double rate)
{
	if (rate < 0 || rate > 5) {
		throw std::invalid_argument("Rating must be between 0 and 5.");
	}
	rating = (rating * rateCount + rate) / (++rateCount);
}


void Movie::reserveSeat(int row, int col)
{
	if (row < 0 || row >= rows || col < 0 || col >= cols) {
		throw std::out_of_range("Invalid seat position");
	}
	hall[row][col] = true; // Mark the seat as reserved
}

void Movie::releaseSeat(int row, int col)
{
	if (row < 0 || row >= rows || col < 0 || col >= cols) {
		throw std::out_of_range("Invalid seat position");
	}
	hall[row][col] = false; // Mark the seat as free
}



void Movie::printLayout() const
{
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << (hall[i][j] ? "X" : "O") << " "; // X for reserved, O for free
		}
		std::cout << std::endl;
	}
}
