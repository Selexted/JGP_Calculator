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
			message << "������ ���̰� �ʹ� ��ϴ�.";
			break;
		case INVALID_CHARACTER:
			message << "ó���� �� ���� ���ڰ� ���Ǿ����ϴ�.";
			break;
		case PARENTHESE_NOT_MATCH:
			message << "���� ��ȣ�� �ݴ� ��ȣ�� ���� ��ġ���� �ʽ��ϴ�.";
			break;
		case INVALID_EQUAL_SIGN:
			message << "��ȣ�� �߸��� ��ġ���� ���Ǿ����ϴ�.";
			break;
		case SPACE_NOT_EXIST:
			message << "�� �ڿ� ������ ���� ���� ���ڰ� �����ϴ�.";
			break;
		case NOT_AN_EXPRESSION:
			message << "�Էµ� ���ڿ��� �ùٸ� ������ �ƴմϴ�.";
			break;
		case OPERAND_OUT_OF_RANGE:
			message << "�ǿ����ڰ� ��� �Ұ����� ũ�⸦ �����ϴ�.";
			break;
		case REVERSED_PARENTHESE:
			message << "�ݴ� ��ȣ�� ���� ��ȣ���� ���� ���Ǿ����ϴ�.";
			break;
		case MULTIPLE_EQUAL_SIGN:
			message << "��ȣ�� ���� �� ���Ǿ����ϴ�.";
			break;
		case OPERATOR_COUNT_NOT_MATCH:
			message << "�������� ���� �ǿ������� ������ �ϳ� ����� �մϴ�.";
			break;
		case EMPTY_PARENTHESE:
			message << "��ȣ���� ����ֽ��ϴ�.";
			break;
		case INVALID_AFTER_OPEN:
			message << "���� ��ȣ �ڿ� ó���� �� ���� ���ڰ� ���Ǿ����ϴ�.";
			break;
		case INVALID_AFTER_CLOSE:
			message << "�ݴ� ��ȣ �ڿ� ó���� �� ���� ���ڰ� ���Ǿ����ϴ�.";
			break;
		case OPERAND_START_WITH_ZERO:
			message << "�ǿ����ڿ� ���� 0�� ���Ǿ����ϴ�.";
			break;
		case MULTIPLE_OPERATOR:
			message << "�����ڰ� �������� ���Ǿ����ϴ�.";
			break;
		case MULTIPLE_OPERAND:
			message << "�ǿ����ڰ� �������� ���Ǿ����ϴ�.";
			break;
		case EQUAL_SIGN_NOT_EXIST:
			message << "���� ������ ���ڷ� ��ȣ�� ������ �ʾҽ��ϴ�.";
			break;
		case ZERO_DIVISION:
			message << "0���� ������ ��찡 �߻��Ͽ����ϴ�.";
			break;
		case MULTIPLE_SPACE:
			message << "������ ������ ���Ǿ����ϴ�.";
			break;
		case LEADING_SPACE:
			message << "�������� ������ ������ �� �����ϴ�.";
			break;
		case MINUS_ZERO:
			message << "0 �տ� ���� ǥ���ڸ� ���� �� �����ϴ�.";
			break;
		case CALC_INVALID_OPERATOR:
			message << "���ǵ��� ���� �����ڰ� ���Ŀ� ���ԵǾ��ֽ��ϴ�.";
			break;
		case CALC_OVERFLOW:
			message << "�ǿ����ڰ� ��� ������ ������ ������ϴ�.";
			break;
		case MULTIPLE_OPERATOR_WITH_NO_SPACE:
			message << "���ӵǴ� �����ڰ� ������� ���Ǿ����ϴ�.";
			break;
		case DECIMAL_POINT_ERROR :
			message << "�Ҽ����� �߸��� ��ġ�� ���Ǿ����ϴ�.";
			break;
		case MULTIPLE_DECIMAL_POINT :
			message << "�� �ǿ����ڿ��� �� �� �̻��� �Ҽ����� ���Ǿ����ϴ�.";
			break;
		case OUT_OF_PRECISION_LIMIT :
			message << "�Ҽ��� ���Ϸ� �Է��� �� �ִ� �ڸ����� �ʰ��Ͽ����ϴ�.";
			break;
		case DECIMAL_END_WITH_ZERO :
			message << "�Ҽ� �ǿ����ڿ� ���� 0�� �������ϰ� ���Ǿ����ϴ�.";
			break;
		case NOT_A_NUMBER :
			message << "������ ������ ������ ����� �� �����ϴ�.";
			break;
		case DEFAULT_EXCEPTION:
		default:
			message << "ó������ ���� �����Դϴ�.";
			break;
		}
	}

	CalculatorException(const int& type, const char* expression, const int& index)
		: CalculatorException(type)
	{
		message << endl << "\t���� ��ǥ:\t" << expression << endl << "\t\t\t";
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