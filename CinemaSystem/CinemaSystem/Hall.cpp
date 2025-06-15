#include "Hall.h"
size_t Hall::nextid = 1;


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
