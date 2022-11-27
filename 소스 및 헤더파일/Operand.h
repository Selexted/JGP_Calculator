#pragma once
#include "Term.h"
#include "Operator.h"

enum OPERAND_TYPE
{
	OPERAND_INT,
	OPERAND_FRACTION,
	OPERAND_DOUBLE
};

class Operand : public Term
{
private:
	double _decimal;
	int _numerator;
	int _denominator;	// always 1 if not a fraction
	int _type;			// uses enum OPERAND_TYPE
	Operand* _exponent;

	Operand(const double& decimal, const int& numerator, const int& denominator, const int& type, Operand* exponent);

	double value() const;
	Operand base() const;

	void exponent(const Operand& new_exponent);

	void ReduceFraction();

	void operator+=(const Operand& r);
	void operator-=(const Operand& r);
	void operator*=(const Operand& r);
	void operator/=(const Operand& r);
	bool operator==(const Operand& r) const;
	bool operator!=(const Operand& r) const;

public:
	Operand(const int& integer);
	Operand(const double& decimal);
	Operand(const Operand& o);

	~Operand();

	int type() const;
	bool is_exponentiated() const;

	Operand& FractionToRealNumber();
	Operand& Exponentiate(const Operand& exponent_);
	Operand& Dexponentiate();

	Operand& Calculate(const Operator& op, const Operand& r);

	string str() const;
};

inline ostream& operator<<(ostream& out, const Operand& o) { return out << o.str(); }