#pragma once
class User;
class System;
class myString;
template <typename T> class Vector;
class Command {
public:
    virtual void execute(System& sys, User*& currentUser, const Vector<myString>& command) const = 0;
    virtual ~Command() = default;
};

