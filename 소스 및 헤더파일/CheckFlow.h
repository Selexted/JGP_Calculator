#pragma once
#include "CalculatorException.h"

class CheckFlow
{
public:
	static double AddDouble(const double& a, const double& b);
	static double SubDouble(const double& a, const double& b);
	static double MulDouble(const double& a, const double& b);
	static double DivDouble(const double& a, const double& b);
	static double PowDouble(const double& a, const double& b);

	static int AddInt(const int& a, const int& b);
	static int SubInt(const int& a, const int& b);
	static int MulInt(const int& a, const int& b);
	static int PowInt(const int& a, const unsigned int& b);

	static double PowDoubleInt(const double& a, const int& b);
};

inline int sign(double val) {
	return (0.0 < val) - (val < 0.0);
}

inline unsigned int absu(int val) {
	return val == INT_MIN ? (unsigned int)INT_MAX + 1 : abs(val);
}