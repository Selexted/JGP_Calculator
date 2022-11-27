#pragma once
#include <iostream>
#include <string>

using namespace std;

class Term
{
public:
	virtual string str() const = 0;
};

inline ostream& operator<<(ostream& out, const Term* t) { return out << t->str(); }
