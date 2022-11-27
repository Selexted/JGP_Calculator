#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

enum {
	DEFAULT_EXCEPTION,
	OUT_OF_LENGTH_LIMIT,
	INVALID_CHARACTER,
	PARENTHESE_NOT_MATCH,
	INVALID_EQUAL_SIGN,
	SPACE_NOT_EXIST,
	NOT_AN_EXPRESSION,
	OPERAND_OUT_OF_RANGE,
	REVERSED_PARENTHESE,
	MULTIPLE_EQUAL_SIGN,
	OPERATOR_COUNT_NOT_MATCH,
	EMPTY_PARENTHESE,
	INVALID_AFTER_OPEN,
	INVALID_AFTER_CLOSE,
	OPERAND_START_WITH_ZERO,
	MULTIPLE_OPERATOR,
	MULTIPLE_OPERAND,
	EQUAL_SIGN_NOT_EXIST,
	ZERO_DIVISION,
	INVALID_OPEN,
	INVALID_CLOSE,
	MULTIPLE_SPACE,
	LEADING_SPACE,
	MINUS_ZERO,
	CALC_INVALID_OPERATOR,
	CALC_OVERFLOW,
	MULTIPLE_OPERATOR_WITH_NO_SPACE,
	DECIMAL_POINT_ERROR,
	MULTIPLE_DECIMAL_POINT,
	OUT_OF_PRECISION_LIMIT,
	DECIMAL_END_WITH_ZERO,
	NOT_A_NUMBER,
};

class CalculatorException {
public:
	const int type;
	std::stringstream message;
	CalculatorException(const int& type = DEFAULT_EXCEPTION) 
		: type(type)
	{
		switch (type)
		{
		case OUT_OF_LENGTH_LIMIT:
			message << "수식의 길이가 너무 깁니다.";
			break;
		case INVALID_CHARACTER:
			message << "처리할 수 없는 문자가 사용되었습니다.";
			break;
		case PARENTHESE_NOT_MATCH:
			message << "여는 괄호와 닫는 괄호의 수가 일치하지 않습니다.";
			break;
		case INVALID_EQUAL_SIGN:
			message << "등호가 잘못된 위치에서 사용되었습니다.";
			break;
		case SPACE_NOT_EXIST:
			message << "이 뒤에 구분을 위한 공백 문자가 없습니다.";
			break;
		case NOT_AN_EXPRESSION:
			message << "입력된 문자열은 올바른 수식이 아닙니다.";
			break;
		case OPERAND_OUT_OF_RANGE:
			message << "피연산자가 계산 불가능한 크기를 가집니다.";
			break;
		case REVERSED_PARENTHESE:
			message << "닫는 괄호가 여는 괄호보다 먼저 사용되었습니다.";
			break;
		case MULTIPLE_EQUAL_SIGN:
			message << "등호가 여러 번 사용되었습니다.";
			break;
		case OPERATOR_COUNT_NOT_MATCH:
			message << "연산자의 수가 피연산자의 수보다 하나 적어야 합니다.";
			break;
		case EMPTY_PARENTHESE:
			message << "괄호항이 비어있습니다.";
			break;
		case INVALID_AFTER_OPEN:
			message << "여는 괄호 뒤에 처리할 수 없는 문자가 사용되었습니다.";
			break;
		case INVALID_AFTER_CLOSE:
			message << "닫는 괄호 뒤에 처리할 수 없는 문자가 사용되었습니다.";
			break;
		case OPERAND_START_WITH_ZERO:
			message << "피연산자에 선행 0이 사용되었습니다.";
			break;
		case MULTIPLE_OPERATOR:
			message << "연산자가 연속으로 사용되었습니다.";
			break;
		case MULTIPLE_OPERAND:
			message << "피연산자가 연속으로 사용되었습니다.";
			break;
		case EQUAL_SIGN_NOT_EXIST:
			message << "식의 마지막 문자로 등호가 사용되지 않았습니다.";
			break;
		case ZERO_DIVISION:
			message << "0으로 나누는 경우가 발생하였습니다.";
			break;
		case MULTIPLE_SPACE:
			message << "공백이 여러번 사용되었습니다.";
			break;
		case LEADING_SPACE:
			message << "공백으로 수식을 시작할 수 없습니다.";
			break;
		case MINUS_ZERO:
			message << "0 앞에 음수 표현자를 붙힐 수 없습니다.";
			break;
		case CALC_INVALID_OPERATOR:
			message << "정의되지 않은 연산자가 수식에 포함되어있습니다.";
			break;
		case CALC_OVERFLOW:
			message << "피연산자가 계산 가능한 범위를 벗어났습니다.";
			break;
		case MULTIPLE_OPERATOR_WITH_NO_SPACE:
			message << "연속되는 연산자가 공백없이 사용되었습니다.";
			break;
		case DECIMAL_POINT_ERROR :
			message << "소수점이 잘못된 위치에 사용되었습니다.";
			break;
		case MULTIPLE_DECIMAL_POINT :
			message << "한 피연산자에서 두 개 이상의 소수점이 사용되었습니다.";
			break;
		case OUT_OF_PRECISION_LIMIT :
			message << "소숫점 이하로 입력할 수 있는 자리수를 초과하였습니다.";
			break;
		case DECIMAL_END_WITH_ZERO :
			message << "소수 피연산자에 후행 0이 부적절하게 사용되었습니다.";
			break;
		case NOT_A_NUMBER :
			message << "음수의 유리수 제곱은 계산할 수 없습니다.";
			break;
		case DEFAULT_EXCEPTION:
		default:
			message << "처리되지 않은 예외입니다.";
			break;
		}
	}

	CalculatorException(const int& type, const char* expression, const int& index)
		: CalculatorException(type)
	{
		message << endl << "\t오류 지표:\t" << expression << endl << "\t\t\t";
		for (int i = 0; i < index; i++) {
			message << " ";
		}
		message << "^";
	}

	CalculatorException(const CalculatorException& e) : type(e.type) {
		message = std::stringstream(e.message.str());
	}

	CalculatorException(CalculatorException&& e) : type(e.type) {
		message = std::stringstream(e.message.str());
	}
};