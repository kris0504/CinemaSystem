#pragma once
#include "Vector.hpp"
#include "User.h"
#include "Movie.h"
#include "Hall.h"
#include "CommandFactory.h"
class System {
private:
    Vector<User*> users;
    Vector<Movie*> movies;
    Vector<Hall> halls;
    int loggedInUserId;

public:
    System();
    User* login(int id, myString password);
    void addMovie(Movie* movie);
	Hall& getHallById(size_t id) ;
	Vector<Movie*>& getMovies() ;
	Vector<User*>& getUsers() ;
	Vector<Hall>& getHalls() ;
    User* getUserById(size_t Id) const;
	bool rateMovie(int id, double rating);
    bool removeMovie(size_t movieId);
    myString getMovieNameById(int id)const;
    bool closeHaul(size_t id);
    void removeUser(User* userToRemove);
    bool buyTicket(int movieId, int row, int col, User* currentUser);
    void checkTickets(User* user);
    bool updateMovieHaul(int movieId, int newHallId);
    bool isHallFree(int hallId, const myString& date, const myString& startTime, const myString& endTime, int movieId);
    bool updateMovieTitle(size_t id, myString newTitle);
    void run();
    void saveToFile();
    void loadFromFile();
};


