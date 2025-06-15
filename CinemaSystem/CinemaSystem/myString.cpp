//Kristiyan Todorov 6MI0600484 4grupa

#include "MyString.h"
#include <cstring>
#include <algorithm>
#pragma warning (disable : 4996)

Vector<myString> myString::getWords() const {
    Vector<myString> result;
    size_t i = 0;

    while (i < this->_size) {

        while (i < _size && (_data[i] == ' ' || _data[i] == '\t' || _data[i] == '\n'))
            ++i;


        size_t start = i;

        while (i < _size && _data[i] != ' ' && _data[i] != '\t' && _data[i] != '\n')
            ++i;


        if (start < i) {
            size_t wordLen = i - start;
            char* buffer = new char[wordLen + 1];

            for (size_t j = 0; j < wordLen; j++)
                buffer[j] = _data[start + j];

            buffer[wordLen] = '\0';

            result.push_back(myString(buffer));
            delete[] buffer;
        }
    }

    return result;
}
Vector<myString> myString::getWordsBy(char delim) const
{
    Vector<myString> result;
    size_t start = 0;
    for (size_t i = 0; i <= _size; ++i) {
        if (_data[i] == delim || _data[i] == '\0') {
            size_t len = i - start;
            char* buffer = new char[len + 1];
            for (size_t j = 0; j < len; j++) buffer[j] = _data[start + j];
            buffer[len] = '\0';
            result.push_back(myString(buffer));
            delete[] buffer;
            start = i + 1;
        }
    }
    return result;
}
static unsigned roundToPowerOfTwo(unsigned v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{
    return std::max(roundToPowerOfTwo(stringLength + 1), 16u);
}

myString::myString() : myString("") {}

myString::myString(const char* data)
{
    _size = std::strlen(data);
    _allocatedDataSize = dataToAllocByStringLen(_size);
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, data);
}

myString::myString(size_t stringLength)
{
    _allocatedDataSize = dataToAllocByStringLen(stringLength);
    _data = new char[_allocatedDataSize];
    _size = 0;
    _data[0] = '\0';
}

myString::myString(const myString& other)
{
    copyFrom(other);
}
myString::myString(myString&& other) noexcept
{
    moveFrom(std::move(other));
}


void myString::moveFrom(myString&& other)
{
    _data = other._data;
    _size = other._size;
    _allocatedDataSize = other._allocatedDataSize;


    other._data = nullptr;
    other._size = 0;
    other._allocatedDataSize = 0;
}


myString& myString::operator=(const myString& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

myString& myString::operator=(myString&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}


myString::~myString()
{
    free();
}

size_t myString::getCapacity() const
{
    return _allocatedDataSize - 1;
}

size_t myString::getSize() const
{
    return _size;
}

size_t myString::toSizeT() const
{
	if (_size == 0 || _data[0] == '\0')
		return 0;
	
    size_t result = 0;
    for (size_t i = 0; _data[i] != '\0'; i++) {
        if (_data[i] < '0' || _data[i] > '9') {
            throw std::invalid_argument("Invalid string for conversion to size_t");
            return 0; 
        }
        if (_data[i] < '0' || _data[i] > '9')
            return 0;
        result = result * 10 + (_data[i] - '0');
    }
    return result;
}

const char* myString::c_str() const
{
    return _data;
}

myString& myString::operator+=(const myString& other)
{
    if (getSize() + other.getSize() + 1 > _allocatedDataSize)
        resize(dataToAllocByStringLen(getSize() + other.getSize()));

    std::strncat(_data, other._data, other.getSize());

    _size = getSize() + other.getSize();
    return *this;
}

double myString::toDouble() const
{
	double result = 0.0;
	double factor = 1.0;
	bool isFractionalPart = false;

	for (size_t i = 0; _data[i] != '\0'; i++) {
		if (_data[i] == '.') {
			isFractionalPart = true;
			continue;
		}
		if (_data[i] < '0' || _data[i] > '9')
			return 0.0;

		if (isFractionalPart) {
			factor /= 10.0;
			result += (_data[i] - '0') * factor;
		}
		else {
			result = result * 10 + (_data[i] - '0');
		}
	}
	return result;
    
}

char& myString::operator[](size_t index)
{
    return _data[index]; 
}

const char& myString::operator[](size_t index) const
{
    return _data[index]; 
}

std::ostream& operator<<(std::ostream& os, const myString& obj)
{
    return os << obj._data;
}
size_t myString::getLen() const
{
    return _size;
}
int myString::find(char ch) const
{

    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == ch)
            return i;
    }
    return -1;

}
std::istream& operator>>(std::istream& is, myString& ref)
{
    char buff[1024];
    is >> buff;
    size_t buffStringSize = std::strlen(buff);

    if (buffStringSize > ref.getCapacity())
        ref.resize(dataToAllocByStringLen(buffStringSize));

    strcpy(ref._data, buff);
    ref._size = buffStringSize;
    return is;
}

void myString::resize(unsigned newAllocatedDataSize)
{
    char* newData = new char[newAllocatedDataSize + 1];
    std::strcpy(newData, _data);
    delete[] _data;
    _data = newData;
    _allocatedDataSize = newAllocatedDataSize;
}

void myString::free()
{
    delete[] _data;
}

void myString::copyFrom(const myString& other)
{
    _allocatedDataSize = other._allocatedDataSize;
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, other._data);
    _size = other._size;
}

myString myString::substr(size_t begin, size_t howMany) const
{
    if (begin + howMany > getSize())
        throw std::length_error("Error, Substr out of range");


    myString res(howMany + 1);
    strncat(res._data, _data + begin, howMany);
    return res;
}


myString operator+(const myString& lhs, const myString& rhs)
{
    myString result(lhs.getSize() + rhs.getSize());
    result += lhs; 
    result += rhs;
    return result;
}
void myString::serialize(std::ofstream& out) const {
    out.write((char*)&_size, sizeof(_size));
    out.write(_data, _size);
}

void myString::deserialize(std::ifstream& in) {
    in.read((char*)&_size, sizeof(_size));
    _allocatedDataSize = dataToAllocByStringLen(_size);
    delete[] _data;
    _data = new char[_allocatedDataSize];
    in.read(_data, _size);
    _data[_size] = '\0';
}
bool operator==(const myString& lhs, const myString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const myString& lhs, const myString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const myString& lhs, const myString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const myString& lhs, const myString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const myString& lhs, const myString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const myString& lhs, const myString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}