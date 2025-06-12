#include "System.h"
#include "RegularUser.h"
#include "Admin.h"
#include <ctime>
#include <iomanip>
#include <sstream>

myString getCurrentDate() {
	time_t now = time(nullptr);
	tm localTime;
	// Използваме localtime_s вместо deprecated localtime
#ifdef _MSC_VER
	localtime_s(&localTime, &now);
#else
	localtime_r(&now, &localTime);
#endif

	std::ostringstream oss;
	oss << std::setfill('0')
		<< std::setw(4) << (1900 + localTime.tm_year) << '-'
		<< std::setw(2) << (localTime.tm_mon + 1) << '-'
		<< std::setw(2) << localTime.tm_mday;

	return myString(oss.str().c_str());
}

// Връща текущото време във формат "HH:MM"
myString getCurrentTime() {
	time_t now = time(nullptr);
	tm localTime;
#ifdef _MSC_VER
	localtime_s(&localTime, &now);
#else
	localtime_r(&now, &localTime);
#endif

	std::ostringstream oss;
	oss << std::setfill('0')
		<< std::setw(2) << localTime.tm_hour << ':'
		<< std::setw(2) << localTime.tm_min;

	return myString(oss.str().c_str());
}
User* System::login(int id, myString password)
{
	User* currentUser = getUserById(id);
	if (!currentUser) {
		std::cout << "User with ID " << id << " does not exist." << std::endl;
		return nullptr;
	}
	if (id == 0 && currentUser->isAdminUser() && password == currentUser->getPassword()) {
		return currentUser;
	}


	if (currentUser->getPassword() == password)
		return currentUser;
	std::cout << "Invalid password for user with ID " << id << "." << std::endl;
	return nullptr;
}
bool System::buyTicket(int movieId, int row, int col, User* currentUser)
{
	if (currentUser == nullptr) {
		std::cout << "You must be logged in to buy a ticket." << std::endl;
		return false;
	}

	for (size_t i = 0; i < movies.getSize(); ++i) {
		if (movies[i]->getId() == movieId) {
			if (movies[i]->isPassed()) {
				std::cout << "Movie has already passed. Cannot buy ticket." << std::endl;
				return false;
			}
			Hall* h = nullptr;
			for (size_t j = 0; j < halls.getSize(); j++)
			{
				if (movies[i]->getHallId() == halls[j].getId())
				{
					h = &halls[j];
					break;
				}
			}
			if (!movies[i]->isSeatAvailable(row, col)) {
				std::cout << "Seat is not available." << std::endl;
				return false;
			}
			Ticket ticket(movies[i]->getId(), row, col,movies[i]->getPrice(), getCurrentDate(), getCurrentTime());
			static_cast<RegularUser*>(currentUser)->getTickets().push_back(ticket);
			movies[i]->getHall().reserveSeat(row, col);
			std::cout << "Ticket purchased successfully." << std::endl;
			return true;
		}
	}
	std::cout << "Movie with ID " << movieId << " not found." << std::endl;
	return false;
}
User* System::getUserById(size_t Id)const {
	size_t size = users.getSize();
	for (size_t i = 0; i < size; i++) {
		if (users[i]->getId() == Id) {
			return users[i];
		}
	}
	return nullptr;
}
bool System::rateMovie(int id, double rating)
{
	for (size_t i = 0; i < movies.getSize(); ++i) {
		if (movies[i]->getId() == id) {
			movies[i]->addRating(rating);
			return true;
		}
	}
	return false;
}
bool System::removeMovie(size_t movieId)
{
	Movie* movie = nullptr;
	for (size_t i = 0; i < movies.getSize(); ++i) {
		if (movies[i]->getId() == movieId) {
			
			movie = movies[i];
			break;
		}
	}
	if (!movie) return false;
	for (size_t i = 0; i < users.getSize(); ++i) {
		User* user = users[i];
		if (user->isAdminUser()) continue;
		RegularUser* regularUser = static_cast<RegularUser*>(user);

		for (size_t j = 0; j < regularUser->getHistory().getSize(); j++) {
			if (regularUser->getHistory()[j] == movie->getTitle()) {
				regularUser->getHistory().remove(j);
			}
		}
		for (size_t j = 0; j < regularUser->getTickets().getSize(); j++) {
			if (regularUser->getTickets()[j].getMovieId() == movieId) {
				regularUser->addBalance(movie->getPrice());
			}
		}
	}
	for (size_t i = 0; i < movies.getSize(); ++i) {
		if (movies[i]->getId() == movieId) {
			movies.remove(i);
			
			break;
		}
	}
	delete movie;
	return true;

}
myString System::getMovieNameById(int id) const
{
	for (size_t i = 0; i < movies.getSize(); ++i) {
		if (movies[i]->getId() == id) {
			return movies[i]->getTitle();\
		}
	}

}
void System::addMovie(Movie* movie)
{
}

Hall& System::getHallById(size_t id)
{
	for (size_t i = 0; i < halls.getSize(); ++i) {
		if (halls[i].getId() == id) {
			return halls[i];
		}
	}
	throw std::invalid_argument("Hall with the given ID does not exist.");
}

Vector<Movie*>& System::getMovies()
{
	return movies;
}

Vector<User*>& System::getUsers()
{
	return users;
}

Vector<Hall>& System::getHalls()
{
	return halls;
}

bool System::closeHaul(size_t id)
{
	Hall* hall = nullptr;

	for (size_t i = 0; i < halls.getSize(); ++i) {
		if (halls[i].getId() == id) {
			hall = &halls[i];
		}
	}
	if (!hall)return false;
	Vector<Movie*> moviesInHall;
	for (size_t i = 0; i < movies.getSize(); i++)
	{
		if (movies[i]->getHallId() == hall->getId()) moviesInHall.push_back(movies[i]);
	}

	for (size_t i = 0; i < users.getSize(); i++)
	{
		User* user = users[i];
		if (user->isAdminUser()) continue;
		RegularUser* regularUser = static_cast<RegularUser*>(user);

		for (size_t j = 0; j < regularUser->getHistory().getSize(); j++)
		{
			for (size_t k = 0; k < moviesInHall.getSize(); k++)
			{
				if (regularUser->getHistory()[j] == moviesInHall[k]->getTitle()) {

					regularUser->getHistory()[j] == "unknown";
				}
			}
		}
		for (size_t j = 0; j < regularUser->getTickets().getSize(); j++)
		{
			for (size_t k = 0; k < moviesInHall.getSize(); k++)
			{
				if (regularUser->getTickets()[j].getMovieId() == moviesInHall[k]->getId()) {
					regularUser->addBalance(moviesInHall[k]->getPrice());
				}
			}
		}
	}
	for (size_t i = 0; i < halls.getSize(); i++)
	{
		if (halls[i].getId() == id) halls.remove(i);
	}
	return true;
}

void System::removeUser(User* userToRemove)
{
	if (userToRemove->isAdminUser())
	{
		std::cout << "Cannot remove admin user." << std::endl;
		return;
	}
	for (size_t i = 0; i < users.getSize(); ++i) {
		if (users[i] == userToRemove) {
			users.remove(i);
			delete userToRemove;
			std::cout << "User removed successfully." << std::endl;
			return;
		}
	}
}
void System::checkTickets(User* user)
{
	RegularUser* regularUser = dynamic_cast<RegularUser*>(user);
	for (size_t i = 0; i < regularUser->getTickets().getSize(); i++)
	{
		if (regularUser->getTickets()[i].getDate() < getCurrentDate())
		{
			regularUser->getTickets()[i].setPassed(true);
			regularUser->getHistory().push_back(getMovieNameById(regularUser->getTickets()[i].getMovieId()));

		}
	}
	for (size_t i = 0; i < movies.getSize(); i++)
	{
		if ((movies[i]->getDate() < getCurrentDate()) || ((movies[i]->getDate() == getCurrentDate()) && (movies[i]->getStartTime() < getCurrentTime())))
		{
			movies[i]->setPassed(true);
		}
	}
}
bool System::isHallFree(int hallId, const myString& date, const myString& startTime, const myString& endTime, int movieId) {
	for (size_t i = 0; i < movies.getSize(); ++i) {
		if (movies[i]->getHallId() != hallId) continue;
		if (movies[i]->getId() == movieId) continue;
		if (movies[i]->getDate() != date) continue;

		// Проверка за припокриване на времеви интервали
		if (!(endTime <= movies[i]->getStartTime() || startTime >= movies[i]->getEndTime())) {
			return false; // Има припокриване
		}
	}
	return true;
}
System::System() {
	User* admin = new Admin();
	users.push_back(admin);

}
bool System::updateMovieHaul(int movieId, int newHallId) {
	Hall& hall = getHallById(newHallId);
	for (size_t i = 0; i < movies.getSize(); ++i) {
		if (movies[i]->getId() == movieId) {
			myString date = movies[i]->getDate();
			myString start = movies[i]->getStartTime();
			myString end = movies[i]->getEndTime();

			// Проверка дали филмът вече е минал
			if (movies[i]->isPassed()) {
				std::cout << "Movie has already passed. Cannot update hall." << std::endl;
				return false;
			}

			// Проверка дали залата е свободна
			if (!isHallFree(newHallId, date, start, end, movieId)) {
				std::cout << "New hall is not free at the same time." << std::endl;
				return false;
			}
			hall.getMovieIds().push_back(movieId);
			movies[i]->setHallId(newHallId);
			return true;
		}
	}
	return false;
}


bool System::updateMovieTitle(size_t id, myString newTitle)
{
	myString title = getMovieNameById(id);
	for (size_t i = 0; i < movies.getSize(); ++i) {
		if (movies[i]->getId() == id) {
			movies[i]->setTitle(newTitle);
			for (size_t i = 0; i < users.getSize(); i++)
			{
				for (size_t j = 0; j < users[i]->getHistory().getSize(); j++)
				{
					if (users[i]->getHistory()[j] == title)
						users[i]->getHistory()[j] = newTitle;
				}
			}

			return true;
		}
	}
	return false;
}

void System::run()
{
	myString input;
	Vector<myString> command;
	User* currentUser = nullptr;
	char buffer[1024];
	
		while (true)
		{
			try {
			std::cout << "> ";
			std::cin.getline(buffer, 1024);
			input = myString(buffer);

			command = input.getWords();
			if (command[0] == "exit") {
				saveToFile();
				break;
			}
			myString test = command[1];
			Command* c = CommandFactory::createCommand(*this, currentUser, command);
			c->execute(*this, currentUser, command);
			delete c;
		}
		catch (const std::exception& e) {
			std::cout << "Caught exception: " << e.what() << std::endl;
		}
		}
	


}
void System::saveToFile()
{

}

void System::loadFromFile()
{
}
