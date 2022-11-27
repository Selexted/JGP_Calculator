#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <regex>
#include <conio.h>
#include "Calculator.h"
#include "CheckError.h"
#include "CalculatorException.h"

using namespace std;

int main(void) {
	string choose;
	cout << "JGP Calculator" << endl << endl;
	cout << "*아래의 두 선택사항 앞에 표시된 숫자들 중 하나를 입력하여 원하는 계산 입력 방식을 고르시오." << endl << endl;
	cout << "*아래 두 숫자 이외의 입력은 프로그램을 종료합니다." << endl << endl;
	cout << "1. 수식 입력" << endl << endl;
	cout << "2. 파일명 입력" << endl << endl << endl;
	cout << "선택 사항을 입력하시오 : ";
	
	getline(cin, choose);
	cout << endl;
		if (!(choose == "1" || choose == "2"))
	{
		cout << endl << "1,2 이외의 입력을 받아 프로그램을 종료합니다." << endl << endl;
		cout << "이 창을 닫으려면 아무키나 눌러주세요.";
		getch();
		return 0;
	}
	else if (choose == "1")
	{
		cout << "수식 입력 : ";
		char ex[102];
		cin.getline(ex, 102);
		cout << endl;
		try
		{
			CheckError ce;
			ce.Check(ex);

			Calculator cal;
			cal.Calcuoate(ex);

			cout << endl << endl;
			cout << "수식 입력을 통한 계산을 완료하였습니다" << endl << endl;
			cout << "이 창을 닫으려면 아무키나 눌러주세요.";
		}
		catch (vector<CalculatorException>* exceptions)
		{
			cerr << "\n다음의 식은 계산할 수 없습니다: \"" << string(ex) << "\"" << endl << endl;
			for (CalculatorException e : *exceptions) {
				cerr << "* " << e.message.str() << endl;
			}
			cerr << endl << endl << exceptions->size() << "개의 오류가 발생하여 프로그램을 종료합니다." << endl << endl;
			delete exceptions;
			cout << "이 창을 닫으려면 아무키나 눌러주세요.";
		}
	}
	else if (choose == "2") {
		char path[102];
		cout << "파일 경로 입력 : ";
		cin.getline(path, 102);
		cout << endl;

		regex path_check("^[a-zA-Z]:[\\\\/]([^\\\\/:*?”<>|]+[\\\\/])*input\\.txt$");
		if (!regex_match(path, path_check)) {
			cerr << endl << "파일 경로의 형식이 올바르지 않습니다." << endl << endl;
			cout << "이 창을 닫으려면 아무키나 눌러주세요.";
			getch();
			return 0;
		}

		ifstream input;
		input.open(path);
		if (!input.is_open()) {
			cerr << endl << "파일을 찾을 수 없습니다." << endl << endl;
			cout << "이 창을 닫으려면 아무키나 눌러주세요.";
			getch();
			return 0;
		}

		CheckError ce;
		Calculator cal;
		string ex_raw;
		char ex[102];
		int count = 0;
		int exnum = 1;
		while (!input.eof() && count++ < 50) {
			getline(input, ex_raw);
			strcpy(ex, ex_raw.substr(0, 102).c_str());
			cout << "### Expression No.[ " << exnum << " ] : " << ex_raw << endl << endl;
			try
			{
				ce.Check(ex);
				cal.Calcuoate(ex);
				cout << endl;
			}
			catch (vector<CalculatorException>* exceptions)
			{
				cerr << "\n다음의 식은 계산할 수 없습니다: \"" << string(ex) << "\"" << endl << endl;
				for (CalculatorException e : *exceptions) {
					cerr << "* " << e.message.str() << endl;
				}
				cerr << endl << exceptions->size() << "개의 오류가 발생하여 계산을 중단합니다." << endl << endl;
				delete exceptions;
				exnum++;
				continue;
			}
			exnum++;
		}
		input.close();
		cout << endl << "파일 입력을 통한 계산을 완료하였습니다." << endl << endl;
		cout << "이 창을 닫으려면 아무키나 눌러주세요.";
	}

	getch();
	return 0;
}

