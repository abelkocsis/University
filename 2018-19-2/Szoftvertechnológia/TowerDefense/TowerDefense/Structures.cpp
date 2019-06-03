#include "pch.h"
#include "Structures.h"
#include <sstream>


double distance(Coordinate c1, Coordinate c2) {
	//return sqrt((c1.row - c2.row) ^ 2 + (c1.col - c2.col) ^ 2);
	return abs(c1.row - c2.row) + abs(c1.col - c2.col);
}



std::string Field::toString() {
	std::string r;

	r += std::to_string(Status) + ";";
	r += std::to_string(Obj) + ";";
	r += std::to_string(Whose) + ".";

	return r;
}

Field::Field(std::string s) {
	std::istringstream f(s);
	std::string splitted;

	Status = Free;
	Obj = Empty;
	Whose = nobody;

	if (getline(f, splitted, ';')) {
		Status = S(std::stoi(splitted));
	}
	if (getline(f, splitted, ';')) {
		Obj = O(std::stoi(splitted));
	}
	if (getline(f, splitted, ';')) {
		Whose = W(std::stoi(splitted));
	}

}