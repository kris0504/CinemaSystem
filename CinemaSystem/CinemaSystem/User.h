#pragma once
#include "myString.h"
class User {
protected:
	static size_t nextid;
	size_t id;
	myString name;
	myString password;
	double balance;
	bool isAdmin;
	Vector<myString> history;
public:
	User() = default; // Default constructor
	User(const myString& name, const myString& password, double balance, bool isAdmin = false)
		: name(name), password(password), balance(balance), isAdmin(isAdmin) {
		id++;
	}
	myString getPassword() const { return password; }
	myString getName() const { return name; }
	Vector<myString>& getHistory();
	void addBalance(double m);
	size_t getId() const { return id; }
	virtual void printMenu() const = 0;
	bool isAdminUser() const;
	virtual ~User() = default;
};


