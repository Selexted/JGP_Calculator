#include "CheckError.h"
#include <iostream>
#include <cctype>
#include "CalculatorException.h"

using namespace std;

void CheckError::Check(char ex[]) {

	int equalcount = 0, num = 0, oper = 0, errorcount = 0, open = 0, close = 0;
	vector<CalculatorException>* exceptions = new vector<CalculatorException>();

	if (strlen(ex) > 100) {
		exceptions->push_back(CalculatorException(OUT_OF_LENGTH_LIMIT));
		throw exceptions;
	}

	for (int i = 0; i < strlen(ex); i++)
	{
		if (ex[i] == '(')
		{
			open++;
		}
		else if (ex[i] == ')')
		{
			close++;
		}

		try
		{
			CheckAllowedChar(ex[i]);
		}
		catch (CalculatorException e) {
			exceptions->push_back(e);
			throw exceptions;
		}
	}

	try
	{
		CheckParanthese(open, close);
	}
	catch (CalculatorException e) {
		exceptions->push_back(e);
		throw exceptions;
	}

	int openidx = -1, closeidx = -1, openstack = 0, closestack = 0;
	////
	for (int i = 0; i < strlen(ex); i++) {
		/*
		��� 1
		���� �����ΰ��� �˻�
		*/
		if (!isdigit(ex[i]) && ex[i] != '+' && ex[i] != '-' && ex[i] != '*' && ex[i] != '/' && ex[i] != '=' && ex[i] != ' ' && ex[i] != '(' && ex[i] != ')' && ex[i] != '.' && ex[i] != '^') {
			exceptions->push_back(CalculatorException(NOT_AN_EXPRESSION, ex, i));
			continue;
		}


		/*
		��� 2
		��ȣ�� ���õ� ���� ��Ģ �˻�
		*/
		if (ex[i] == '(')
		{
			openstack++;
			openidx = i;

				if (ex[i + 1] != ' ')
				{
					exceptions->push_back(CalculatorException(SPACE_NOT_EXIST, ex, i));
					continue;
				}
				else if (ex[i + 2] == ')')
				{
					exceptions->push_back(CalculatorException(EMPTY_PARENTHESE, ex, i));
					continue;
				}
				else if ( ( ( !isdigit(ex[i + 2]) && !isdigit(ex[i + 3])) && ex[i + 2] != '(') )
				{
					exceptions->push_back(CalculatorException(INVALID_AFTER_OPEN, ex, i));
					continue;
				}
		
		}
		else if (ex[i] == ')')
		{
			closestack++;
			closeidx = i;
			if (closestack > openstack)
			{
				exceptions->push_back(CalculatorException(REVERSED_PARENTHESE, ex, i));
				throw exceptions;
			}
			if ((closeidx < openidx) && openidx == -1)
			{
				exceptions->push_back(CalculatorException(REVERSED_PARENTHESE, ex, i));
				throw exceptions;
			}

			if (ex[i + 1] != ' ')
			{
				exceptions->push_back(CalculatorException(SPACE_NOT_EXIST, ex, i));
				continue;
			}
			else if (isdigit(ex[i + 2]) || (IsOperation(ex[i + 2]) && ex[i + 2] != ')'))
			{
				exceptions->push_back(CalculatorException(INVALID_AFTER_CLOSE, ex, i));
				continue;
			}
			
		}


		/*
		��� 3
		����� ���õ� ���� ��Ģ �˻�, ���� �ݺ�, ���� ���� ����
		*/
		if (ex[i] == ' ')
		{
			int space_count = 0;
			for (int k = i; ex[k] == ' '; k++) 
			{
				space_count++;
			}

			if (i == 0 && space_count==1)
			{
				exceptions->push_back(CalculatorException(LEADING_SPACE, ex, i));
				continue;
			}

			if (space_count > 1)
			{
				if (i == 0)
				{
					exceptions->push_back(CalculatorException(LEADING_SPACE, ex, i));
				}

				exceptions->push_back(CalculatorException(MULTIPLE_SPACE, ex, i));
				i = i + space_count - 1;
				continue;
			}
		}

		/*
		��� 4
		��ȣ�� ���� ��Ģ �˻�. ��ȣ�� ���� ��� ��ġ�� ���� Ȯ��
		*/

		if (ex[i] == '=') {
			equalcount++;
			if (i != strlen(ex)-1)
			{
				exceptions->push_back(CalculatorException(INVALID_EQUAL_SIGN, ex, i));
				continue;
			}
			else 
			{
				if (ex[i + 1] != ' ' && i != strlen(ex)-1 )
				{
					exceptions->push_back(CalculatorException(SPACE_NOT_EXIST, ex, i));
					continue;
				}
			}

		}

		/*
		��� 5
		�ǿ����ڿ��� �Ҽ����� �������� �ϴ� ���� �˻�.
		*/
		if (ex[i] == '.')
		{

			//� �ǿ������̵�, �Ҽ����� 2�� �̻� �������� �˻�.
			int test_length = 0;
			int test_dp_count = 0;
			int test_dp_locate = -1;
			for (int l = i; (isdigit(ex[l]) || ex[l] == '.'); l++)
			{
				if (ex[l] == '.')
				{
					test_length++;
					test_dp_count++;
					test_dp_locate = l;
				}
				else
				{
					test_length++;
				}
			}

			if (test_dp_count > 1)
			{
				exceptions->push_back(CalculatorException(MULTIPLE_DECIMAL_POINT, ex, i));
				i = i + test_length - 1;
				num++;
				continue;
			}
			//��2���˻�����

			//���� �� �� ���� ��� 
			bool flag=false;
			if (i == 0) {
				flag = true;
			}
			else if(!isdigit(ex[i - 1]) )
			{
				flag = true;
			}

			if ( flag || !isdigit(ex[i + 1]))
			{
				//���� ���ڰ� ���� Ȥ�� ������ �ƴ϶��
				if (!isdigit(ex[i + 1]) && ex[i + 1] != ' ')
				{
					exceptions->push_back(CalculatorException(SPACE_NOT_EXIST, ex, i));
				}

				//��, �Ŀ� ���ڰ� ���ٸ�
				exceptions->push_back(CalculatorException(DECIMAL_POINT_ERROR, ex, i));
				i = i + test_length-1;
				num++;
				continue;
			}
			else
			{
				++i; //�Ҽ��� �ʿ� �Է��� ���� ��Ų ��� �Ҽ��� ���� ���� �Ҽ��� ���� �˻縦 �����Ѵ�.

				int zero_count = 0;
				int decimal_digit = 0;
				for (int k = i; isdigit(ex[k]); k++)
				{
					if (ex[k] == '0')
					{
						zero_count++;
						decimal_digit++;
					}
					else {
						decimal_digit++;
					}

				}

				//0�� 2�� �̻��� ����� ���� 0 �˻�
				//-0.00.. ����
				if (zero_count > 1 && zero_count == decimal_digit && ex[i-2] == '0' && ex[i-3] == '-')
				{
					exceptions->push_back(CalculatorException(MINUS_ZERO, ex, i - 3));
					if (zero_count > 1 && ex[i + decimal_digit - 1] == '0')
					{
						exceptions->push_back(CalculatorException(DECIMAL_END_WITH_ZERO, ex, i));
					}
					i = i + decimal_digit - 2;
					continue;
				}
				//0���� �Ҽ��� ������ ���
				if (zero_count > 1 && ex[i + decimal_digit - 1] == '0')
				{
					exceptions->push_back(CalculatorException(DECIMAL_END_WITH_ZERO, ex, i));
					i = i + decimal_digit - 2;
					continue;
				}
				//���� 0 �˻�1 ����

				//�Ҽ��� ����, 0�� 1���� ��쿡 ����0 �˻�
				int digit = 0;
				for (int k = i; isdigit(ex[k]); k++) {
					digit++;
				}

				if (digit > 6) {
					exceptions->push_back(CalculatorException(OUT_OF_PRECISION_LIMIT, ex, i));
					i = i + digit - 2;
					continue;
				}
				
				if (digit > 1 && ex[i + digit - 1] == '0')
				{
					exceptions->push_back(CalculatorException(DECIMAL_END_WITH_ZERO, ex, i));
					i = i + digit - 2;
					continue;
				}			

				//�Ҽ��� �˻縦 ���������� ��ġ�� ������ ���ڷ� ������ �̵�
				i = i + digit - 2;
				continue;

			}
		}


	
		/*
		��� 6
		�ǿ������� ���� ���ڸ� ������ �� �˻�
		*/
		if (isdigit(ex[i])) 
		{
			
			//� �ǿ������̵�, �Ҽ����� 2�� �̻� �������� �˻�.
			int test_length = 0;
			int test_dp_count = 0;
			int test_dp_locate = -1;
			for (int l = i; (isdigit(ex[l]) || ex[l] == '.'); l++)
			{
				if (ex[l] == '.')
				{
					test_length++;
					test_dp_count++;
					test_dp_locate = l;
				}
				else
				{
					test_length++;
				}
			}
			if (test_dp_count > 1)
			{
				exceptions->push_back(CalculatorException(MULTIPLE_DECIMAL_POINT, ex, i));
				i = i + test_length - 1;
				num++;
				continue;
			}
			//�� 2�� �˻� ����

			//ó�� ���� �� �� 0�� ��쿡 ���� 0 �˻�
			int zero_count = 0;
			if (ex[i] == '0')
			{
				for (int k = i; ex[k] == '0'; k++)
				{
					zero_count++;
				}
			}
			//zero_count�� 2 �̻��϶��� ���ӵ� 0 ���Ŀ� �ִ� ���ڸ�  �˻�
			if ( zero_count>1)
			{
				i = i + zero_count - 1;

				if (isdigit(ex[i + 1]))
				{
					i = i - zero_count + 1;
					exceptions->push_back(CalculatorException(OPERAND_START_WITH_ZERO, ex, i));
					i = i + zero_count - 1;
					continue;
				}

				if (ex[i + 1] != ' ' && ex[i+1]!='.')
				{
					exceptions->push_back(CalculatorException(SPACE_NOT_EXIST, ex, i));
					continue;
				}

				i = i - zero_count + 1;
				exceptions->push_back(CalculatorException(OPERAND_START_WITH_ZERO, ex, i));
				i = i + zero_count - 1;
				if (ex[i + 1] == '.')
				{
					continue;
				}
				else 
				{
					num++;
					continue;
				}
			}
			//zero_count�� 1�� ���
			else if ( zero_count == 1)
			{					
				if (ex[i + 1] == '.')
				{
					//�Ҽ� �Է��̶�� �Ҽ� �˻�� �̵�
					continue;
				}
				if (isdigit(ex[i + 1]))
				{
					//����0
					exceptions->push_back(CalculatorException(OPERAND_START_WITH_ZERO, ex, i));
					continue;
				}

				if (ex[i + 1] != ' ')
				{
					exceptions->push_back(CalculatorException(SPACE_NOT_EXIST, ex, i));
					continue;
				}
				else 
				{
					if (isdigit(ex[i + 2]) || ( ex[i + 2] == '-' && isdigit(ex[i + 3]) ) )
					{
						//�������� 0 �̸鼭 �������� �ǿ����ڰ� ���� ���
						exceptions->push_back(CalculatorException(MULTIPLE_OPERAND, ex, i));
						num++;
						continue;
					}
					else 
					{
						//���� �̰ų� ������ �ΰ��
					}
				}

				//���� 0�� ���� �ǿ����� �� ���� 
				num++;
				continue;

			}
			//���� 0 �˻� ����

			//�Ҽ����� ���Ե� ������ ó�� -> ���� �Ѵٸ� �Ҽ������� �˻���ġ�� ����
			int length = 0;
			int dp_count = 0;
			int dp_locate = -1;
			for (int l = i; (isdigit(ex[l]) || ex[l] == '.'); l++)
			{
				if (ex[l]=='.')
				{
					length++;
					dp_count++;
					dp_locate = l;
				}
				else
				{
					length++;
				}
			}

			//�Ҽ��� ����(1��)  9���� ���ڰ� �Ѿ�� 
			if (length > 9 && dp_count==1) {
				exceptions->push_back(CalculatorException(OPERAND_OUT_OF_RANGE, ex, i));
				i = i + length - 1;
				num++;
				continue;
			}
			 
			//�� �ǿ����� ���� �Ҽ����� 2�� �̻� ���� ��� �ƴ϶�� �˻� ��ġ �̵�
			if (dp_count > 1)
			{
				exceptions->push_back(CalculatorException(MULTIPLE_DECIMAL_POINT, ex, i));
				i = i + length - 1;
				num++;
				continue;
			}
			else if (dp_count == 1)
			{
				i = dp_locate-1;
				continue;
			}
			
			//������ ������ ��� ������ ��ĭ ������ �̵�
			if (ex[i + length - 1] == '.')
			{
				i = i + length - 2;
				continue;
			}

			//���� ó�� �κ�
			int  int_digit = 0;
			for (int k = i; isdigit(ex[k]); k++) {
				int_digit++;
			}

			//���� ��
			if (int_digit > 9) {
				exceptions->push_back(CalculatorException(OPERAND_OUT_OF_RANGE, ex, i));
				i = i + int_digit - 1;
				num++;
				continue;
			}

			//�Ҽ�, ���� ��� ���Ŀ� ���� ���� �˻�
			i = i + int_digit - 1;

			if (ex[i + 1] != ' ')
			{
				exceptions->push_back(CalculatorException(SPACE_NOT_EXIST, ex, i));
				num++;
				continue;
			}

			if ( isdigit(ex[i + 2]) )
			{
				exceptions->push_back(CalculatorException(MULTIPLE_OPERAND, ex, i));
				num ++;
				continue;
			}

			if (ex[i + 2] == '-' && isdigit(ex[i + 3]))
			{
				exceptions->push_back(CalculatorException(MULTIPLE_OPERAND, ex, i));
				num++;
				continue;
			}

			//���� ���� �ǿ����� ���� 1 ����
			num++;
			continue;
		}

		/*
		��� 7
		�ǿ����ڰ� �ƴ� ���ڸ� ������ ���, ������ �̿��� ���ڴ� ���� ��Ͽ��� �˻� �Ϸ�
		*/
		else
		{
			if (ex[i] == '-' && isdigit(ex[i + 1]))
			{

				if ( ex[i + 1] == '0' )
				{
					if ( ex[i + 2] == ' ' )
					{
						exceptions->push_back(CalculatorException(MINUS_ZERO, ex, i));
						continue;
					}
					else if ( isdigit(ex[i + 2]) )
					{
						exceptions->push_back(CalculatorException(MINUS_ZERO, ex, i));
						continue;
					}
					else if (ex[i + 2] == '.' && ex[i+3] == '0' && ex[i+4]==' ')//-0.0 ����
					{
						exceptions->push_back(CalculatorException(MINUS_ZERO, ex, i));
						continue;
					}
					else
					{
						
					}

				}
			}
			else if (ex[i] == '+' || ex[i] == '-' || ex[i] == '*' || ex[i] == '/' || ex[i] == '^' )
			{

				oper++;				

				if (ex[i + 1] != ' ')
				{

					if (ex[i + 1] == '+' || ex[i + 1] == '*' || ex[i + 1] == '/' || (ex[i + 1] == '-' && !isdigit(ex[i + 2])) || ex[i + 1] == '^')
					{
						exceptions->push_back(CalculatorException(SPACE_NOT_EXIST, ex, i));
						exceptions->push_back(CalculatorException(MULTIPLE_OPERATOR_WITH_NO_SPACE, ex, i));
						continue;
					}

					exceptions->push_back(CalculatorException(SPACE_NOT_EXIST, ex, i));
					continue;
				}

				if (ex[i + 2] == '+' || ex[i + 2] == '*' || ex[i + 2] == '/' || (ex[i + 2] == '-' && !isdigit(ex[i + 3])) || ex[i+2]=='^')
				{
					exceptions->push_back(CalculatorException(MULTIPLE_OPERATOR, ex, i)); 
					continue;
				}

			}
		}

	}

	if ((num - oper) != 1) {
		CalculatorException e(OPERATOR_COUNT_NOT_MATCH);
		e.message << " (������ " << oper << "��, �ǿ����� " << num << "��)";
		exceptions->push_back(e);
	}

	if (equalcount > 1) {
		CalculatorException e(MULTIPLE_EQUAL_SIGN);
		exceptions->push_back(e);
	}

	if (ex[strlen(ex) - 1] != '=') {
		CalculatorException e(EQUAL_SIGN_NOT_EXIST);
		exceptions->push_back(e);
	}

	if (exceptions->size() > 0) {
		throw exceptions;
	}
}

void CheckError::CheckAllowedChar(char op) { //���� ���� �ΰ�
	if (!isdigit(op) && op != '+' && op != '-' && op != '*' && op != '/' && op != '=' && op != ' ' && op != '(' && op != ')' && op != '^' && op != '.')
	{
		throw CalculatorException(INVALID_CHARACTER);
	}
}

void CheckError::CheckParanthese(int open, int close) { //��ȣ ¦ ������ �³� 
	if (open != close)
	{
		throw CalculatorException(PARENTHESE_NOT_MATCH);
	}
}


int CheckError::IsOperation(char tok) {
	if (!(tok == '+' || tok == '-' || tok == '*' || tok == '/' || tok == '=' || tok == '^'))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool CheckError::CheckBlank(char op) {
	if (isdigit(op) && op != '+' && op != '-' && op != '*' && op != '/' && op != '=' && op != ' ' && op != '(' && op != ')' && op != '^' && op!= '.')
	{
		return true;
	}
	else
	{
		return false;
	}
}