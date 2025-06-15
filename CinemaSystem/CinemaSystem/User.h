#pragma once
#include "myString.h"
class User {
protected:
	size_t id;
	myString name;
	myString password;
	double balance;
	bool isAdmin;
	Vector<myString> history;
public:
	static size_t nextid;

	User() = default; 
	User(const myString& name, const myString& password, double balance, bool isAdmin = false)
		: name(name), password(password), balance(balance), isAdmin(isAdmin) {
		id = nextid++;

	}

	myString getPassword() const { return password; }
	myString getName() const { return name; }
	Vector<myString>& getHistory();
	void addBalance(double m);
	double getBalance() const { return balance; }
	size_t getId() const { return id; }
	virtual void printMenu() const = 0;
	bool isAdminUser() const;
	void serializeBase(std::ofstream& out) const;
	void deserializeBase(std::ifstream& in);

	virtual void serialize(std::ofstream& out) const = 0;
	virtual void deserialize(std::ifstream& in) = 0;

	virtual ~User() = default;
};


