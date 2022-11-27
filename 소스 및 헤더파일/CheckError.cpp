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
		블록 1
		허용된 문자인가를 검사
		*/
		if (!isdigit(ex[i]) && ex[i] != '+' && ex[i] != '-' && ex[i] != '*' && ex[i] != '/' && ex[i] != '=' && ex[i] != ' ' && ex[i] != '(' && ex[i] != ')' && ex[i] != '.' && ex[i] != '^') {
			exceptions->push_back(CalculatorException(NOT_AN_EXPRESSION, ex, i));
			continue;
		}


		/*
		블록 2
		괄호와 관련된 문법 규칙 검사
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
		블록 3
		공백과 관련된 문법 규칙 검사, 공백 반복, 공백 시작 관련
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
		블록 4
		등호의 문법 규칙 검사. 등호가 사용된 경우 위치와 개수 확인
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
		블록 5
		피연산자에서 소수점을 기준으로 하는 문법 검사.
		*/
		if (ex[i] == '.')
		{

			//어떤 피연산자이든, 소수점이 2개 이상 쓰였나를 검사.
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
			//점2개검사종료

			//점이 한 개 쓰인 경우 
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
				//직후 문자가 숫자 혹은 공백이 아니라면
				if (!isdigit(ex[i + 1]) && ex[i + 1] != ' ')
				{
					exceptions->push_back(CalculatorException(SPACE_NOT_EXIST, ex, i));
				}

				//전, 후에 숫자가 없다면
				exceptions->push_back(CalculatorException(DECIMAL_POINT_ERROR, ex, i));
				i = i + test_length-1;
				num++;
				continue;
			}
			else
			{
				++i; //소숫점 필요 입력을 충족 시킨 경우 소숫점 다음 문자 소수부 부터 검사를 시작한다.

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

				//0이 2개 이상인 경우의 후행 0 검사
				//-0.00.. 검정
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
				//0으로 소수가 끝나는 경우
				if (zero_count > 1 && ex[i + decimal_digit - 1] == '0')
				{
					exceptions->push_back(CalculatorException(DECIMAL_END_WITH_ZERO, ex, i));
					i = i + decimal_digit - 2;
					continue;
				}
				//후행 0 검사1 종료

				//소수부 범위, 0이 1개인 경우에 후행0 검사
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

				//소수부 검사를 정상적으로 거치면 마지막 문자로 앞으로 이동
				i = i + digit - 2;
				continue;

			}
		}


	
		/*
		블록 6
		피연산자인 숫자 문자를 만났을 때 검사
		*/
		if (isdigit(ex[i])) 
		{
			
			//어떤 피연산자이든, 소수점이 2개 이상 쓰였나를 검사.
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
			//점 2개 검사 종료

			//처음 시작 수 가 0인 경우에 선행 0 검사
			int zero_count = 0;
			if (ex[i] == '0')
			{
				for (int k = i; ex[k] == '0'; k++)
				{
					zero_count++;
				}
			}
			//zero_count가 2 이상일때는 연속된 0 이후에 있는 문자를  검사
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
			//zero_count가 1인 경우
			else if ( zero_count == 1)
			{					
				if (ex[i + 1] == '.')
				{
					//소수 입력이라면 소수 검사로 이동
					continue;
				}
				if (isdigit(ex[i + 1]))
				{
					//선행0
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
						//정상적인 0 이면서 연속적인 피연산자가 사용된 경우
						exceptions->push_back(CalculatorException(MULTIPLE_OPERAND, ex, i));
						num++;
						continue;
					}
					else 
					{
						//공백 이거나 연산자 인경우
					}
				}

				//정수 0에 대한 피연산자 수 증가 
				num++;
				continue;

			}
			//선행 0 검사 종료

			//소수점이 포함된 연산자 처리 -> 존재 한다면 소수점으로 검사위치를 이전
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

			//소수점 포함(1개)  9개의 문자가 넘어가면 
			if (length > 9 && dp_count==1) {
				exceptions->push_back(CalculatorException(OPERAND_OUT_OF_RANGE, ex, i));
				i = i + length - 1;
				num++;
				continue;
			}
			 
			//한 피연산자 내에 소수점이 2개 이상 쓰인 경우 아니라면 검사 위치 이동
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
			
			//점으로 끝나는 경우 점에서 한칸 앞으로 이동
			if (ex[i + length - 1] == '.')
			{
				i = i + length - 2;
				continue;
			}

			//정수 처리 부분
			int  int_digit = 0;
			for (int k = i; isdigit(ex[k]); k++) {
				int_digit++;
			}

			//범위 평가
			if (int_digit > 9) {
				exceptions->push_back(CalculatorException(OPERAND_OUT_OF_RANGE, ex, i));
				i = i + int_digit - 1;
				num++;
				continue;
			}

			//소수, 정수 블록 이후에 사용된 문자 검사
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

			//오류 없이 피연산자 개수 1 증가
			num++;
			continue;
		}

		/*
		블록 7
		피연산자가 아닌 문자를 만났을 경우, 연산자 이외의 문자는 이전 블록에서 검사 완료
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
					else if (ex[i + 2] == '.' && ex[i+3] == '0' && ex[i+4]==' ')//-0.0 검정
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
		e.message << " (연산자 " << oper << "개, 피연산자 " << num << "개)";
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

void CheckError::CheckAllowedChar(char op) { //허용된 문자 인가
	if (!isdigit(op) && op != '+' && op != '-' && op != '*' && op != '/' && op != '=' && op != ' ' && op != '(' && op != ')' && op != '^' && op != '.')
	{
		throw CalculatorException(INVALID_CHARACTER);
	}
}

void CheckError::CheckParanthese(int open, int close) { //괄호 짝 갯수가 맞나 
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