#pragma once
#include "User.h"
#include "Movie.h"
class Admin : public User {
    

public:
	Admin(); 
	Admin(const myString& name, const myString& password, double balance)
		: User(name, password, balance, true){}
    void addHall(int rows, int cols);
    void updateMovieTitle(int movieId, const myString& newTitle);
    void printMenu() const override;
    
    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;

};


