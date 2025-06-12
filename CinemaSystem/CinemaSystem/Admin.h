#pragma once
#include "User.h"
#include "Movie.h"
class Admin : public User {
    bool isAdmin;

public:
	Admin(); // Default constructor
	Admin(const myString& name, const myString& password, double balance)
		: User(name, password, balance, true), isAdmin(true) {}
    void addHall(int rows, int cols);
    void updateMovieTitle(int movieId, const myString& newTitle);
    void printMenu() const override;
};


