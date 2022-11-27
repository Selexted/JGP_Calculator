#include "Operand.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include "CalculatorException.h"
#include "CheckFlow.h"

Operand::Operand(const int& integer) : Operand(0.0, integer, 1, OPERAND_INT, nullptr)
{
}

Operand::Operand(const double& decimal) : Operand(decimal, 0, 1, OPERAND_DOUBLE, nullptr)
{
}

Operand::Operand(const double& decimal, const int& numerator, const int& denominator, const int& type, Operand* exponent)
	: _decimal(decimal)
	, _numerator(numerator)
	, _denominator(denominator)
	, _type(type)
	, _exponent(exponent)
{
}

Operand::Operand(const Operand& o) :Operand(o._decimal, o._numerator, o._denominator, o._type, nullptr)
{
	if (o._exponent != nullptr) {
		_exponent = new Operand(*o._exponent);
	}
}

Operand::~Operand()
{
	if (_exponent != nullptr) {
		delete _exponent;
	}
}

int Operand::type() const
{
	return _type;
}

double Operand::value() const
{
	Operand copy(*this);
	while (copy._exponent != nullptr) {
		copy.Dexponentiate();
	}
	copy.FractionToRealNumber();
	return copy._decimal;
}

Operand Operand::base() const
{
	Operand b(*this);
	delete b._exponent;
	b._exponent = nullptr;
	return b;
}

bool Operand::is_exponentiated() const
{
	return _exponent != nullptr;
}

void Operand::exponent(const Operand& new_exponent)
{
	if (_exponent != nullptr) {
		delete _exponent;
	}
	_exponent = new Operand(new_exponent);
}

void Operand::ReduceFraction()
{
	if (_type == OPERAND_DOUBLE) {
		return;
	}
	if (_numerator == 0) {
		_denominator = 1;
		_type = OPERAND_INT;
		return;
	}
	if (_denominator == 0) {
		vector<CalculatorException>* exceptions = new vector<CalculatorException>();
		exceptions->push_back(CalculatorException(ZERO_DIVISION));
		throw exceptions;
	}
	int a = _numerator;
	int b = _denominator;
	int r = 0;
	if (a <= b) {
		r = a;
		a = b;
		b = r;
		r = 0;
	}
	while (true) {
		r = a % b;
		if (r == 0) {
			break;
		}
		a = b;
		b = r;
	}
	_numerator /= b;
	_denominator /= b;
	if (_numerator < 0 && _denominator < 0) {
		_numerator *= -1;
		_denominator *= -1;
	}
	if (_denominator == -1) {
		_numerator *= -1;
		_denominator = 1;
	}
	if (_denominator == 1) {
		_type = OPERAND_INT;
	}
	else
	{
		_type = OPERAND_FRACTION;
	}
}

Operand& Operand::FractionToRealNumber()
{
	if (_type == OPERAND_DOUBLE) {
		return *this;
	}
	_type = OPERAND_DOUBLE;
	_decimal = CheckFlow::DivDouble(_numerator, _denominator);
	_numerator = 0;
	_denominator = 1;
	return *this;
}

Operand& Operand::Exponentiate(const Operand& new_exponent)
{
	if (new_exponent == Operand(1)) {
		return *this;
	}
	if (_exponent == nullptr) {
		exponent(new_exponent);
	}
	else {
		*_exponent *= new_exponent;
	}
	if (_type == OPERAND_DOUBLE || new_exponent._type == OPERAND_DOUBLE || *_exponent == Operand(0)) {
		while (_exponent != nullptr) {
			Dexponentiate();
		}
	}
	else if (*_exponent == Operand(1)) {
		delete _exponent;
		_exponent = nullptr;
	}
	return *this;
}

Operand& Operand::Dexponentiate()
{
	if (_exponent == nullptr) {
		return *this;
	}
	if (_exponent->_exponent != nullptr) {		
		_exponent->Dexponentiate();
		return *this;
	}
	if (_type != OPERAND_DOUBLE && _exponent->_type != OPERAND_DOUBLE) {
		if (_exponent->value() < 0) {		// 지수가 음수인 경우 밑을 역수로 바꾼다
			int t = _numerator;
			_numerator = _denominator;
			_denominator = t;
			*_exponent *= Operand(-1);
			ReduceFraction();
		}
		if (_exponent->_denominator != 1) {		// 지수의 분모가 1이 아닐 경우 밑의 제곱근을 구한다
			unsigned int exp_denominator = _exponent->_denominator;
			unsigned int abs_numerator = abs(_numerator);
			unsigned int abs_denominator = abs(_denominator);
			int numerator_root = (int)round(CheckFlow::PowDouble(abs_numerator, 1.0 / exp_denominator));
			int denominator_root = (int)round(CheckFlow::PowDouble(abs_denominator, 1.0 / exp_denominator));
			if (_numerator == CheckFlow::PowInt(numerator_root, exp_denominator) && _denominator == CheckFlow::PowInt(denominator_root, exp_denominator)) {
				_exponent->_denominator = _exponent->_denominator < 0 ? -1 : 1;
				_exponent->_type = OPERAND_INT;
				_numerator = numerator_root;
				_denominator = denominator_root;
				ReduceFraction();
				_exponent->ReduceFraction();
				if (_exponent->_numerator == 1) {
					delete _exponent;
					_exponent = nullptr;
				}
				return *this;
			}
		}
		if (_exponent->_type == OPERAND_INT) {		// 지수가 정수인 경우 밑의 분자와 분모를 따로 제곱한다
			_numerator = CheckFlow::PowInt(_numerator, _exponent->_numerator);
			_denominator = CheckFlow::PowInt(_denominator, _exponent->_numerator);
			delete _exponent;
			_exponent = nullptr;
			return *this;
		}
	}
	FractionToRealNumber();
	if (_exponent->_type == OPERAND_INT) {		// 지수가 정수인 경우
		_decimal = CheckFlow::PowDoubleInt(_decimal, _exponent->_numerator);
	}
	else {		// 그렇지 않은 경우
		_exponent->FractionToRealNumber();
		_decimal = CheckFlow::PowDouble(_decimal, _exponent->_decimal);
	}
	delete _exponent;
	_exponent = nullptr;
	return *this;
}

Operand& Operand::Calculate(const Operator& op, const Operand& r)
{
	switch (op.type())
	{
	case OP_ADDITION:
		operator+=(r);
		break;
	case OP_SUBTRACTION:
		operator-=(r);
		break;
	case OP_MULTIPLICATION:
		operator*=(r);
		break;
	case OP_DIVISION:
		operator/=(r);
		break;
	case OP_EXPONENTIATION:
		Exponentiate(r);
		break;
	}
	return *this;
}

void Operand::operator+=(const Operand& r)
{
	Operand copy_r(r);
	while (_exponent != nullptr) {
		Dexponentiate();
	}
	while (copy_r._exponent != nullptr) {
		copy_r.Dexponentiate();
	}
	int type = _type < copy_r._type ? copy_r._type : _type;
	if (type == OPERAND_DOUBLE) {
		FractionToRealNumber();
		copy_r.FractionToRealNumber();
		_decimal = CheckFlow::AddDouble(_decimal, copy_r._decimal);
	}
	else if (type == OPERAND_INT) {
		_numerator = CheckFlow::AddInt(_numerator, copy_r._numerator);
	}
	else {
		_numerator = CheckFlow::AddInt(
			CheckFlow::MulInt(_numerator, copy_r._denominator),
			CheckFlow::MulInt(copy_r._numerator, _denominator));
		_denominator = CheckFlow::MulInt(_denominator, copy_r._denominator);
		ReduceFraction();
	}
}

void Operand::operator-=(const Operand& r)
{
	Operand copy_r(r);
	while (_exponent != nullptr) {
		Dexponentiate();
	}
	while (copy_r._exponent != nullptr) {
		copy_r.Dexponentiate();
	}
	int type = _type < copy_r._type ? copy_r._type : _type;
	if (type == OPERAND_DOUBLE) {
		FractionToRealNumber();
		copy_r.FractionToRealNumber();
		_decimal = CheckFlow::SubDouble(_decimal, copy_r._decimal);
	}
	else if (type == OPERAND_INT) {
		_numerator = CheckFlow::SubInt(_numerator, copy_r._numerator);
	}
	else {
		_numerator = CheckFlow::SubInt(
			CheckFlow::MulInt(_numerator, copy_r._denominator),
			CheckFlow::MulInt(copy_r._numerator, _denominator));
		_denominator *= copy_r._denominator;
		ReduceFraction();
	}
}

void Operand::operator*=(const Operand& r)
{
	Operand copy_r(r);
	if (_exponent != nullptr && copy_r._exponent != nullptr && base() == r.base())
	{
		*_exponent += *(copy_r._exponent);
	}
	else {
		if (_exponent == nullptr || copy_r._exponent == nullptr || *_exponent != *copy_r._exponent) {
			while (_exponent != nullptr) {
				Dexponentiate();
			}
			while (copy_r._exponent != nullptr) {
				copy_r.Dexponentiate();
			}
		}
		int type = _type < copy_r._type ? copy_r._type : _type;
		if (type == OPERAND_DOUBLE) {
			while (_exponent != nullptr) {
				Dexponentiate();
			}
			while (copy_r._exponent != nullptr) {
				copy_r.Dexponentiate();
			}
			FractionToRealNumber();
			copy_r.FractionToRealNumber();
			_decimal = CheckFlow::MulDouble(_decimal, copy_r._decimal);
		}
		else if (type == OPERAND_INT) {
			_numerator = CheckFlow::MulInt(_numerator, copy_r._numerator);
		}
		else {
			_numerator = CheckFlow::MulInt(_numerator, copy_r._numerator);
			_denominator = CheckFlow::MulInt(_denominator, copy_r._denominator);
			ReduceFraction();
		}
	}
}

void Operand::operator/=(const Operand& r)
{
	Operand copy_r(r);
	if (_exponent != nullptr && copy_r._exponent != nullptr && base() == r.base()) {
		*_exponent -= *(copy_r._exponent);
	}
	else {
		if (_exponent == nullptr || copy_r._exponent == nullptr || *_exponent != *copy_r._exponent) {
			while (_exponent != nullptr) {
				Dexponentiate();
			}
			while (copy_r._exponent != nullptr) {
				copy_r.Dexponentiate();
			}
		}
		int type = _type < copy_r._type ? copy_r._type : _type;
		if (type == OPERAND_DOUBLE) {
			while (_exponent != nullptr) {
				Dexponentiate();
			}
			while (copy_r._exponent != nullptr) {
				copy_r.Dexponentiate();
			}
			FractionToRealNumber();
			copy_r.FractionToRealNumber();
			_decimal = CheckFlow::DivDouble(_decimal, copy_r._decimal);
		}
		else {
			_numerator = CheckFlow::MulInt(_numerator, copy_r._denominator);
			_denominator = CheckFlow::MulInt(_denominator, copy_r._numerator);
			ReduceFraction();
		}
	}
}

bool Operand::operator==(const Operand& r) const
{
	if (_type != r._type || (_exponent == nullptr) != (r._exponent ==nullptr)) {
		return false;
	}
	if (_type == OPERAND_DOUBLE) {
		return _decimal == r._decimal;
	}
	if (_exponent == nullptr) {
		return _numerator == r._numerator && _denominator == r._denominator;
	}
	return _numerator == r._numerator && _denominator == r._denominator && *_exponent == *r._exponent;
}

bool Operand::operator!=(const Operand& r) const
{
	return !operator==(r);
}

string Operand::str() const
{
	stringstream ss;
	switch (_type)
	{
	case OPERAND_INT:
		ss << _numerator;
		break;
	case OPERAND_DOUBLE:
		ss << fixed << setprecision(6) << value();
		break;
	case OPERAND_FRACTION:
		ss << "( " << _numerator << " / " << _denominator << " )";
		break;
	}
	if (_exponent != nullptr) {
		ss << " ^ " << *_exponent << " )";
		ss.str("( " + ss.str());
	}
	return ss.str();
}