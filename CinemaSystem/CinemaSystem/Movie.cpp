#include "Movie.h"
size_t Movie::nextid = 1;

Movie::Movie(myString title, int durationMinutes, int releaseYear, myString genre, int hallId, myString date, myString startTime, myString endTime, int rows, int cols) : title(title), rating(0), durationMinutes(durationMinutes), releaseYear(releaseYear),
genre(genre), hallId(hallId), date(date), startTime(startTime), endTime(endTime) 
{
	this->rows = rows;
	this->cols = cols;
    hall.clear();
    for (size_t i = 0; i < rows; ++i) {
        Vector<bool> row;
        for (int j = 0; j < cols; j++)
            row.push_back(false);
        hall.push_back(row);
    }

	passed = false;
	id = nextid++;

}

bool Movie::isSeatAvailable(int row, int col) const
{
	if (row < 1 || row > rows || col < 1 || col > cols) {
		throw std::out_of_range("Invalid seat position");
	}
	return !hall[row-1][col-1];
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
	if (row < 1 || row > rows || col < 1 || col > cols) {
		throw std::out_of_range("Invalid seat position");
	}
	hall[row-1][col-1] = true;
}

void Movie::releaseSeat(int row, int col)
{
	if (row < 1 || row > rows || col < 1 || col > cols) {

		throw std::out_of_range("Invalid seat position");
	}
	hall[row-1][col-1] = false; 
}



void Movie::printLayout() const
{
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << (hall[i][j] ? "X" : "O") << " ";
		}
		std::cout << std::endl;
	}
}
void Movie::serializeBase(std::ofstream& out) const {
    out.write((char*)&id, sizeof(id));
    title.serialize(out);
    out.write((char*)&rating, sizeof(rating));
    out.write((char*)&rateCount, sizeof(rateCount));
    out.write((char*)&durationMinutes, sizeof(durationMinutes));
    out.write((char*)&releaseYear, sizeof(releaseYear));
    genre.serialize(out);
    out.write((char*)&hallId, sizeof(hallId));
    out.write((char*)&rows, sizeof(rows));
    out.write((char*)&cols, sizeof(cols));
    date.serialize(out);
    startTime.serialize(out);
    endTime.serialize(out);
    out.write((char*)&price, sizeof(price));
    out.write((char*)&passed, sizeof(passed));
   
    for (size_t i = 0; i < rows; i++) {

        for (size_t j = 0; j < cols; j++) {
            out.write((char*)&hall[i][j], sizeof(bool));
        }
    }
    
}

void Movie::deserializeBase(std::ifstream& in) {
    in.read((char*)&id, sizeof(id));
    title.deserialize(in);
    in.read((char*)&rating, sizeof(rating));
    in.read((char*)&rateCount, sizeof(rateCount));
    in.read((char*)&durationMinutes, sizeof(durationMinutes));
    in.read((char*)&releaseYear, sizeof(releaseYear));
    genre.deserialize(in);
    in.read((char*)&hallId, sizeof(hallId));
    in.read((char*)&rows, sizeof(rows));
    in.read((char*)&cols, sizeof(cols));
    date.deserialize(in);
    startTime.deserialize(in);
    endTime.deserialize(in);
    in.read((char*)&price, sizeof(price));
    in.read((char*)&passed, sizeof(passed));

    hall.clear(); 
    for (size_t i = 0; i < rows; i++) {
 
        Vector<bool> row;
        for (size_t j = 0; j < cols; j++) {
            bool value;
            in.read((char*)&value, sizeof(value));
            row.push_back(value);
        }

        hall.push_back(row); 
    }


    
}
