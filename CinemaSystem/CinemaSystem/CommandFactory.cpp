#include "CommandFactory.h"
class User;
Command* CommandFactory::createCommand(System& sys, User*& currentUser, const Vector<myString>& command)
{
	if (!currentUser) {
		if (command[0] == "login") {
			return new LoginCommand();

		}
		else if (command[0] == "register") {
			return new RegisterCommand();
		}
		else {
			std::cout << "Please login first.\n";
			//return new Error();
			return new InvalidCommand();
		}

	}
	if (command[0] == "logout") {
		return new LogoutCommand();

	}

	if (command[0] == "print_seats") return new PrintSeatsCommand();
	if (command[0] == "add_balance") return new AddBalanceCommand();
	if (command[0] == "list_movies") return new ListMoviesCommand();
	if (command[0] == "list_tickets") return new ListTicketsCommand();
	if (command[0] == "rate_movie") return new RateMovieCommand();
	if (command[0] == "list_history") return new ListHistoryCommand();
	if (command[0] == "buy_ticket") return new BuyTicketCommand();
	if (command[0] == "exit") return new ExitCommand();
	if (currentUser->isAdminUser()) {
		if (command[0] == "add_movie") return new AddMovieCommand();
		if (command[0] == "open_haul") return new OpenHaulCommand();
		if (command[0] == "remove_movie") return new RemoveMovieCommand();
		if (command[0] == "close_haul") return new CloseHaulCommand();
		if (command[0] == "update_movie_title") return new UpdateMovieTitleCommand();
		if (command[0] == "update_movie_haul") return new UpdateMovieHaul();
		if (command[0] == "list_user_history") return new ListUserHistoryCommand();
		if (command[0] == "list_user_tickets") return new ListUserTicketsCommand();
		if (command[0] == "list_users") return new ListUsersCommand();
		if (command[0] == "remove_user") return new RemoveUserCommand();

	}
	return new InvalidCommand();


}
