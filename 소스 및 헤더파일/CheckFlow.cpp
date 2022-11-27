#include "CheckFlow.h"

double CheckFlow::AddDouble(const double& a, const double& b)
{
	if (b > 0.0 && a > DBL_MAX - b) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (Double형 양수 오버플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	if (b < 0.0 && a < -DBL_MAX - b) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (Double형 음수 오버플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	if (-b < a && a < DBL_MIN - b) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (Double형 양수 언더플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	if (-b > a && a > -DBL_MIN - b) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (Double형 음수 언더플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	return a + b;
}

double CheckFlow::SubDouble(const double& a, const double& b)
{
	if (b > 0.0 && a < b - DBL_MAX) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (double형 음수 오버플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	if (b < 0.0 && a > b + DBL_MAX) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (double형 양수 오버플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	if (a > b && b + DBL_MIN > a) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (double형 양수 언더플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	if (a < b && b - DBL_MIN < a) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (double형 음수 언더플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	return a - b;
}

double CheckFlow::MulDouble(const double& a, const double& b)
{
	if (a == 0.0 || b == 0.0) {
		return 0.0;
	}
	if (log10(abs(a)) + log10(abs(b)) > log10(DBL_MAX)) {
		if (sign(a) == sign(b)) {
			vector<CalculatorException>* exceptions = new vector<CalculatorException>();
			CalculatorException exception(CALC_OVERFLOW);
			exception.message << " (double형 양수 오버플로우)";
			exceptions->push_back(exception);
			throw exceptions;
		}
		else {
			vector<CalculatorException>* exceptions = new vector<CalculatorException>();
			CalculatorException exception(CALC_OVERFLOW);
			exception.message << " (double형 음수 오버플로우)";
			exceptions->push_back(exception);
			throw exceptions;
		}
	}
	if (log10(abs(a)) + log10(abs(b)) < log10(DBL_MIN)) {
		if (sign(a) == sign(b)) {
			vector<CalculatorException>* exceptions = new vector<CalculatorException>();
			CalculatorException exception(CALC_OVERFLOW);
			exception.message << " (double형 양수 언더플로우)";
			exceptions->push_back(exception);
			throw exceptions;
		}
		else {
			vector<CalculatorException>* exceptions = new vector<CalculatorException>();
			CalculatorException exception(CALC_OVERFLOW);
			exception.message << " (double형 음수 언더플로우)";
			exceptions->push_back(exception);
			throw exceptions;
		}
	}
	return a * b;
}

double CheckFlow::DivDouble(const double& a, const double& b)
{
	if (b == 0.0) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		exceptions->push_back(CalculatorException(ZERO_DIVISION));
		throw exceptions;
	}
	if (a == 0.0) {
		return 0.0;
	}
	if (log10(abs(a)) - log10(abs(b)) > log10(DBL_MAX)) {
		if (sign(a) == sign(b)) {
			vector<CalculatorException>* exceptions = new vector<CalculatorException>();
			CalculatorException exception(CALC_OVERFLOW);
			exception.message << " (double형 양수 오버플로우)";
			exceptions->push_back(exception);
			throw exceptions;
		}
		else {
			vector<CalculatorException>* exceptions = new vector<CalculatorException>();
			CalculatorException exception(CALC_OVERFLOW);
			exception.message << " (double형 음수 오버플로우)";
			exceptions->push_back(exception);
			throw exceptions;
		}
	}
	if (log10(abs(a)) - log10(abs(b)) < log10(DBL_MIN)) {
		if (sign(a) == sign(b)) {
			vector<CalculatorException>* exceptions = new vector<CalculatorException>();
			CalculatorException exception(CALC_OVERFLOW);
			exception.message << " (double형 양수 언더플로우)";
			exceptions->push_back(exception);
			throw exceptions;
		}
		else {
			vector<CalculatorException>* exceptions = new vector<CalculatorException>();
			CalculatorException exception(CALC_OVERFLOW);
			exception.message << " (double형 음수 언더플로우)";
			exceptions->push_back(exception);
			throw exceptions;
		}
	}
	return a / b;
}

double CheckFlow::PowDouble(const double& a, const double& b)
{
	if (a < 0.0) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(NOT_A_NUMBER);
		exceptions->push_back(exception);
		throw exceptions;
	}
	if (a == 1.0 || b == 0.0) {
		return 1.0;
	}
	if (a == 0.0) {
		return 0.0;
	}
	double overflow_r = log10(DBL_MAX) / log10(a);
	double underflow_r = log10(DBL_MIN) / log10(a);
	if ((a > 1 && b > overflow_r) || (a < 1 && b < overflow_r)) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (double형 양수 오버플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	if ((a > 1 && b < underflow_r) || (a < 1 && b > underflow_r)) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (double형 양수 언더플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	return pow(a, b);
}

int CheckFlow::AddInt(const int& a, const int& b)
{
	if (b > 0 && a > INT_MAX - b) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (int형 양수 오버플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	if (b < 0 && a < INT_MIN - b) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (int형 음수 오버플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	return a + b;
}

int CheckFlow::SubInt(const int& a, const int& b)
{
	if (b > 0 && a < INT_MIN + b) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (int형 음수 오버플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	if (b < 0 && a > INT_MAX + b) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (int형 양수 오버플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	return a - b;
}

int CheckFlow::MulInt(const int& a, const int& b)
{
	if (a == 0 || b == 0) {
		return 0;
	}
	if (sign(a) == sign(b) && absu(a) > INT_MAX / (double)absu(b)) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (int형 양수 오버플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	if (sign(a) != sign(b) && absu(a) > -(double)INT_MIN / absu(b)) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		exception.message << " (int형 음수 오버플로우)";
		exceptions->push_back(exception);
		throw exceptions;
	}
	return a * b;
}

int CheckFlow::PowInt(const int& a, const unsigned int& b)
{
	if (b == 0 || a == 1) {
		return 1;
	}
	if (a == 0) {
		return 0;
	}
	int result = a;
	for (unsigned int i = 1; i < b; i++) {
		result = MulInt(result, a);
	}
	return result;
}

double CheckFlow::PowDoubleInt(const double& a, const int& b)
{
	if (a == 1.0 || b == 0) {
		return 1.0;
	}
	double a_;
	unsigned int b_;
	if (b < 0) {
		b_ = absu(b);
		a_ = 1.0 / a;
	}
	else {
		b_ = b;
		a_ = a;
	}
	if (a_ == 0.0) {
		return 0.0;
	}
	double overflow_r = log10(DBL_MAX) / log10(abs(a_));
	double underflow_r = log10(DBL_MIN) / log10(abs(a_));
	if ((abs(a_) > 1 && b_ > overflow_r) || (abs(a_) < 1 && b_ < overflow_r)) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		if (a < 0 && b % 2) {
			exception.message << " (double형 음수 오버플로우)";
		}
		else {
			exception.message << " (double형 양수 오버플로우)";
		}
		exceptions->push_back(exception);
		throw exceptions;
	}
	if ((abs(a_) > 1 && b_ < underflow_r) || (abs(a_) < 1 && b_ > underflow_r)) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		CalculatorException exception(CALC_OVERFLOW);
		if (a < 0 && b % 2) {
			exception.message << " (double형 음수 언더플로우)";
		}
		else {
			exception.message << " (double형 양수 언더플로우)";
		}
		exceptions->push_back(exception);
		throw exceptions;
	}
	return pow(a_, b_);
}

