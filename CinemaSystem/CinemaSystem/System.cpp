#include "System.h"
#include "RegularUser.h"
#include "Admin.h"
#include "DramaMovie.h"
#include "ActionMovie.h"
#include "DocumentaryMovie.h"
#include <ctime>
#include <iomanip>
#include <sstream>

myString getCurrentDate() {
	time_t now = time(nullptr);
	tm localTime;
	
#ifdef _MSC_VER
	localtime_s(&localTime, &now);
#else
	localtime_r(&now, &localTime);
#endif

	std::ostringstream oss;
	oss << std::setfill('0')
		<< std::setw(2) << localTime.tm_mday << '.' << std::setw(2) << (localTime.tm_mon + 1) << '.'
		<< std::setw(4) << (1900 + localTime.tm_year);



	return myString(oss.str().c_str());
}


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


	if (currentUser->getPassword() == password) {

		checkTickets(currentUser);
		return currentUser;
	}
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
			if (static_cast<RegularUser*>(currentUser)->getBalance() < movies[i]->getPrice()) {
				std::cout << "Not enough balance to buy ticket." << std::endl;
				return false;
			}


			static_cast<RegularUser*>(currentUser)->addBalance(-movies[i]->getPrice());
			movies[i]->reserveSeat(row, col);
			Ticket ticket(movies[i]->getId(), row, col, movies[i]->getPrice(), getCurrentDate(), getCurrentTime(), movies[i]->getTitle(), movies[i]->getHallId());
			static_cast<RegularUser*>(currentUser)->getTickets().push_back(ticket);
			//std::cout << "Ticket purchased successfully." << std::endl;
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
		User*& user = users[i];
		if (user->isAdminUser()) continue;
		RegularUser* regularUser = static_cast<RegularUser*>(user);

		for (size_t j = 0; j < regularUser->getHistory().getSize(); j++) {
			if (regularUser->getHistory()[j] == movie->getTitle()) {

				regularUser->getHistory().remove(j);
				j--;
			}
		}
		for (size_t j = 0; j < regularUser->getTickets().getSize(); j++) {
			if (regularUser->getTickets()[j].getMovieId() == movieId) {
				regularUser->getTickets().remove(j);
				j--;
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

bool System::checkMovieExists(myString date, myString startTime, myString endTime, int hallid) const
{
	for (size_t i = 0; i < movies.getSize(); i++)
	{
		if (movies[i]->getHallId() == hallid && movies[i]->getDate() == date && (movies[i]->getStartTime() >= startTime && movies[i]->getStartTime() <= endTime ||
			movies[i]->getEndTime() >= startTime && movies[i]->getEndTime() <= endTime ||
			movies[i]->getStartTime() >= startTime && movies[i]->getEndTime() <= endTime ||
			movies[i]->getStartTime() <= startTime && movies[i]->getEndTime() >= endTime)) return true;
	}
	return false;

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
		User*& user = users[i];
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
	for (size_t i = 0; i < movies.getSize(); i++)
	{
		if (movies[i]->getHallId() == hall->getId()) movies.remove(i);
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
		throw std::invalid_argument("Cannot remove admin user.");
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
	int s = regularUser->getTickets().getSize();
	for (size_t i = 0; i < s; i++)
	{
		if ((regularUser->getTickets()[i].getDate() < getCurrentDate()||(regularUser->getTickets()[i].getDate() == getCurrentDate()&& regularUser->getTickets()[i].getTime() < getCurrentTime())))
		{
			//!regularUser->getTickets()[i].isPassed() &&
			//regularUser->getTickets()[i].setPassed(true);
			myString movieName = getMovieNameById(regularUser->getTickets()[i].getMovieId());
			//std::cout << "Adding to history: " << movieName << std::endl;
			regularUser->getHistory().push_back(movieName);
			regularUser->getTickets().remove(i);

			//regularUser->getHistory().push_back(getMovieNameById(regularUser->getTickets()[i].getMovieId()));
			i--;
			s--;
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

		
		if (!(endTime <= movies[i]->getStartTime() || startTime >= movies[i]->getEndTime())) {
			return false; 
		}
	}
	return true;
}
System::System() {
	loadFromFile();
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->isAdminUser()) return;
	}
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

			if (movies[i]->isPassed()) {
				std::cout << "Movie has already passed. Cannot update hall." << std::endl;
				return false;
			}

	
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

	std::ofstream out("data.dat", std::ios::binary);
	if (!out) return;


	out.write((char*)&User::nextid, sizeof(size_t));
	out.write((char*)&Movie::nextid, sizeof(size_t));
	out.write((char*)&Hall::nextid, sizeof(size_t));

	size_t hallCount = halls.getSize();
	out.write((char*)&hallCount, sizeof(hallCount));
	for (size_t i = 0; i < hallCount; ++i)
		halls[i].serialize(out);


	size_t movieCount = movies.getSize();
	out.write((char*)&movieCount, sizeof(movieCount));
	for (size_t i = 0; i < movieCount; ++i) {
		myString type = movies[i]->getType();
		type.serialize(out);
		movies[i]->serialize(out);
	}

	
	size_t userCount = users.getSize();
	out.write((char*)&userCount, sizeof(userCount));
	for (size_t i = 0; i < userCount; ++i) {
		myString type = users[i]->isAdminUser() ? "Admin" : "Regular";
		type.serialize(out);
		users[i]->serialize(out);
	}

	out.close();


}

void System::loadFromFile()
{

	std::ifstream in("data.dat", std::ios::binary);
	if (!in) return;

	in.read((char*)&User::nextid, sizeof(size_t));
	in.read((char*)&Movie::nextid, sizeof(size_t));
	in.read((char*)&Hall::nextid, sizeof(size_t));

	
	size_t hallCount;
	in.read((char*)&hallCount, sizeof(hallCount));
	for (size_t i = 0; i < hallCount; ++i) {
		Hall h;
		h.deserialize(in);
		halls.push_back(h);
	}

	
	size_t movieCount;
	in.read((char*)&movieCount, sizeof(movieCount));
	for (size_t i = 0; i < movieCount; ++i) {
		myString type;
		type.deserialize(in);
		Movie* m = nullptr;
		if (type == "Drama") m = new DramaMovie();
		else if (type == "Action") m = new ActionMovie();
		else if (type == "Documentary") m = new DocumentaryMovie();
		if (m) {
			m->deserialize(in);
			movies.push_back(m);
		}
	}

	
	size_t userCount;
	in.read((char*)&userCount, sizeof(userCount));
	for (size_t i = 0; i < userCount; ++i) {
		myString type;
		type.deserialize(in);
		User* u = nullptr;
		if (type == "Admin") u = new Admin();
		else if (type == "Regular") u = new RegularUser();
		if (u) {
			u->deserialize(in);
			users.push_back(u);
		}
	}
	
	in.close();


}
Movie* System::getMovieByName(myString name) {
	for (size_t i = 0; i < movies.getSize(); ++i) {
		if (movies[i]->getTitle() == name) {
			return movies[i];
		}
	}
	throw::std::invalid_argument("Movie with the given name does not exist.");
	return nullptr;
}
Movie* System::getMovieById(size_t id) {
	for (size_t i = 0; i < movies.getSize(); ++i) {
		if (movies[i]->getId() == id) {
			return movies[i];
		}
	}
	throw::std::invalid_argument("Movie with the given ID does not exist.");
	return nullptr;
}
