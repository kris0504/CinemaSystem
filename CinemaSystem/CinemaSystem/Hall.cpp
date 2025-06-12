#include "Hall.h"
size_t Hall::id = 0;

void Hall::reserveSeat(int row, int col)
{
	if (row < 0 || row >= rows || col < 0 || col >= cols) {
		throw std::out_of_range("Invalid seat position");
	}
	seats[row][col] = true; // Mark the seat as reserved
}

void Hall::releaseSeat(int row, int col)
{
	if (row < 0 || row >= rows || col < 0 || col >= cols) {
		throw std::out_of_range("Invalid seat position");
	}
	seats[row][col] = false; // Mark the seat as free
}

bool Hall::isSeatFree(int row, int col) const
{
    return seats[row][col];
}

void Hall::printLayout() const
{
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << (seats[i][j] ? "X" : "O") << " "; // X for reserved, O for free
		}
		std::cout << std::endl;
	}
}
