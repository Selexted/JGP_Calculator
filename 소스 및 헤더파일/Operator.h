#pragma once
#include "Term.h"

enum OPERATOR_TYPE
{
	OP_ADDITION = '+',
	OP_SUBTRACTION = '-',
	OP_MULTIPLICATION = '*',
	OP_DIVISION = '/',
	OP_OPEN_BRACKET = '(',
	OP_CLOSE_BRACKET = ')',
	OP_EXPONENTIATION = '^',
};

class Operator : public Term
{
private:
	int _type;			// uses enum OPERATOR_TYPE

public:
	Operator(const int& type) : _type(type) {}

	int type() const { return _type; }
	string str() const { return string(1, _type); }
};

inline bool is_operator(const char& c)
{
	return c == OP_ADDITION || c == OP_SUBTRACTION || c == OP_MULTIPLICATION || c == OP_DIVISION ||
		c == OP_CLOSE_BRACKET || c == OP_OPEN_BRACKET || c == OP_EXPONENTIATION;
}

inline int priority_of(const char& op) {
	switch (op)
	{
	case OP_ADDITION:
	case OP_SUBTRACTION:
		return 1;
	case OP_MULTIPLICATION:
	case OP_DIVISION:
		return 2;
	case OP_EXPONENTIATION:
		return 3;
	}
	return 0;
}

inline ostream& operator<<(ostream& out, const Operator& o) { return out << o.str(); }