#include "Hall.h"
size_t Hall::nextid = 1;

//void Hall::reserveSeat(int row, int col)
//{
//	if (row < 0 || row >= rows || col < 0 || col >= cols) {
//		throw std::out_of_range("Invalid seat position");
//	}
//	seats[row][col] = true; // Mark the seat as reserved
//}
//
//void Hall::releaseSeat(int row, int col)
//{
//	if (row < 0 || row >= rows || col < 0 || col >= cols) {
//		throw std::out_of_range("Invalid seat position");
//	}
//	seats[row][col] = false; // Mark the seat as free
//}
//
//bool Hall::isSeatFree(int row, int col) const
//{
//    return !seats[row][col];
//}

//void Hall::printLayout() const
//{
//	for (int i = 0; i < rows; ++i) {
//		for (int j = 0; j < cols; ++j) {
//			std::cout << (seats[i][j] ? "X" : "O") << " "; // X for reserved, O for free
//		}
//		std::cout << std::endl;
//	}
//}
// Hall.cpp
void Hall::serialize(std::ofstream& out) const {
    out.write((char*)&id, sizeof(id));
    out.write((char*)&rows, sizeof(rows));
    out.write((char*)&cols, sizeof(cols));

    size_t count = movieIds.getSize();
    out.write((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; i++) {
        out.write((char*)&movieIds[i], sizeof(int));
    }
}

void Hall::deserialize(std::ifstream& in) {
    in.read((char*)&id, sizeof(id));
    in.read((char*)&rows, sizeof(rows));
    in.read((char*)&cols, sizeof(cols));

    size_t count;
    in.read((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; i++) {
        int movieId;
        in.read((char*)&movieId, sizeof(int));
        movieIds.push_back(movieId);
    }
}
