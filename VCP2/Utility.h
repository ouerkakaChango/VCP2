#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
using std::string;
using std::vector;
using std::function;
using std::cout;
using std::ifstream;
using std::ofstream;
namespace VCP {
	class Utility {};

}

template <class Type>
Type stringToNum(const string& str) {
	std::istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

template <class Type>
string numToString(const Type& n) {
	std::stringstream ss;
	std::string str;
	ss << n;
	ss >> str;
	return str;
}


#endif

