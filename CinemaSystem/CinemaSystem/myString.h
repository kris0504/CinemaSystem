//Kristiyan Todorov 6MI0600484 4grupa
#pragma once
#include <iostream>
#include "Vector.hpp"

class myString
{
public:
    myString();
    myString(const char* data);

    myString(const myString& other);
    myString(myString&& other) noexcept;

    myString& operator=(const myString& other);

    myString& operator=(myString&& other) noexcept;
    ~myString();

    size_t getCapacity() const;
    size_t getSize() const;
    size_t toSizeT() const;
    const char* c_str() const;
    size_t getLen() const;
    int find(char ch) const;
    myString& operator+=(const myString& other);
	double toDouble() const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;
    Vector<myString> getWords() const;
    Vector<myString> getWordsBy(char delim) const;
    void serialize(std::ofstream& out) const;

    void deserialize(std::ifstream& in);
    friend std::ostream& operator<<(std::ostream& os, const myString& obj);
    friend std::istream& operator>>(std::istream& is, myString& ref);
    friend myString operator+(const myString& lhs, const myString& rhs);

    myString substr(size_t begin, size_t howMany) const;

private:
    explicit myString(size_t stringLength);
    void resize(unsigned newAllocatedDataSize);

    void free();
    void copyFrom(const myString& other);

    void moveFrom(myString&& other);

    char* _data;
    size_t _size;
    size_t _allocatedDataSize;
};



bool operator==(const myString& lhs, const myString& rhs);
bool operator!=(const myString& lhs, const myString& rhs);
bool operator<(const myString& lhs, const myString& rhs);
bool operator<=(const myString& lhs, const myString& rhs);
bool operator>(const myString& lhs, const myString& rhs);
bool operator>=(const myString& lhs, const myString& rhs);

