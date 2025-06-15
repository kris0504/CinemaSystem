#include "User.h"
size_t User::nextid = 1;

Vector<myString>& User::getHistory()
{
	return history;
}

void User::addBalance(double m)
{
	balance += m;

}

bool User::isAdminUser() const
{
	return isAdmin;
}


void User::serializeBase(std::ofstream& out) const {
	out.write((char*)&id, sizeof(id));
	name.serialize(out);
	password.serialize(out);
	out.write((char*)&balance, sizeof(balance));
	out.write((char*)&isAdmin, sizeof(isAdmin));

	size_t historySize = history.getSize();
	out.write((char*)&historySize, sizeof(historySize));
	for (size_t i = 0; i < historySize; i++) {
		history[i].serialize(out);
	}
}

void User::deserializeBase(std::ifstream& in) {
	in.read((char*)&id, sizeof(id));
	name.deserialize(in);
	password.deserialize(in);
	in.read((char*)&balance, sizeof(balance));
	in.read((char*)&isAdmin, sizeof(isAdmin));

	size_t historySize;
	in.read((char*)&historySize, sizeof(historySize));
	for (size_t i = 0; i < historySize; i++) {
		myString s;
		s.deserialize(in);
		history.push_back(s);
	}

}
