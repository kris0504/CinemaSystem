#pragma once
#include "Command.h"
#include "LoginCommand.h"
#include "RegisterCommand.h"
#include "LogoutCommand.h"
#include "BuyTicketCommand.h"
#include "ListMoviesCommand.h"
#include "ListTicketsCommand.h"
#include "RateMovieCommand.h"
#include "ExitCommand.h"
#include "AddMovieCommand.h"
#include "ListHistoryCommand.h"
#include "OpenHaulCommand.h"
#include "RemoveMovieCommand.h"
#include "CloseHaulCommand.h"
#include "UpdateMovieTitleCommand.h"
#include "UpdateMovieHaul.h"
#include "ListUserHistoryCommand.h"
#include "ListUserTicketsCommand.h"
#include "ListUsersCommand.h"
#include "RemoveUserCommand.h"
#include "PrintSeatsCommand.h"
#include "InvalidCommand.h"
#include "addBalanceCommand.h"
#include "ViewBalanceCommand.h"
class System;
class User;
    class CommandFactory {
    public:
        static Command* createCommand(System& sys, User*& currentUser, const Vector<myString>& command);
    };


