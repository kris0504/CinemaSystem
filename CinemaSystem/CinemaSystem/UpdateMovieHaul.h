#pragma once


#include <iostream>
#include "MyString.h"
#include "System.h"
#include "User.h"

class UpdateMovieHaul : public Command {
public:
    void execute(System& sys, User*& currentUser, const Vector<myString>& command) const override;
};

