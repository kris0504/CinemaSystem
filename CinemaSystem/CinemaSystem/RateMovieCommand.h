#pragma once


#include <iostream>
#include "MyString.h"
#include "System.h"
#include "User.h"

class RateMovieCommand : public Command {
public:
    void execute(System& sys, User*& currentUser, const Vector<myString>& command) const override;
};

