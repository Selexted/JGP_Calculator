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
	cout << "*�Ʒ��� �� ���û��� �տ� ǥ�õ� ���ڵ� �� �ϳ��� �Է��Ͽ� ���ϴ� ��� �Է� ����� ���ÿ�." << endl << endl;
	cout << "*�Ʒ� �� ���� �̿��� �Է��� ���α׷��� �����մϴ�." << endl << endl;
	cout << "1. ���� �Է�" << endl << endl;
	cout << "2. ���ϸ� �Է�" << endl << endl << endl;
	cout << "���� ������ �Է��Ͻÿ� : ";
	
	getline(cin, choose);
	cout << endl;
		if (!(choose == "1" || choose == "2"))
	{
		cout << endl << "1,2 �̿��� �Է��� �޾� ���α׷��� �����մϴ�." << endl << endl;
		cout << "�� â�� �������� �ƹ�Ű�� �����ּ���.";
		getch();
		return 0;
	}
	else if (choose == "1")
	{
		cout << "���� �Է� : ";
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
			cout << "���� �Է��� ���� ����� �Ϸ��Ͽ����ϴ�" << endl << endl;
			cout << "�� â�� �������� �ƹ�Ű�� �����ּ���.";
		}
		catch (vector<CalculatorException>* exceptions)
		{
			cerr << "\n������ ���� ����� �� �����ϴ�: \"" << string(ex) << "\"" << endl << endl;
			for (CalculatorException e : *exceptions) {
				cerr << "* " << e.message.str() << endl;
			}
			cerr << endl << endl << exceptions->size() << "���� ������ �߻��Ͽ� ���α׷��� �����մϴ�." << endl << endl;
			delete exceptions;
			cout << "�� â�� �������� �ƹ�Ű�� �����ּ���.";
		}
	}
	else if (choose == "2") {
		char path[102];
		cout << "���� ��� �Է� : ";
		cin.getline(path, 102);
		cout << endl;

		regex path_check("^[a-zA-Z]:[\\\\/]([^\\\\/:*?��<>|]+[\\\\/])*input\\.txt$");
		if (!regex_match(path, path_check)) {
			cerr << endl << "���� ����� ������ �ùٸ��� �ʽ��ϴ�." << endl << endl;
			cout << "�� â�� �������� �ƹ�Ű�� �����ּ���.";
			getch();
			return 0;
		}

		ifstream input;
		input.open(path);
		if (!input.is_open()) {
			cerr << endl << "������ ã�� �� �����ϴ�." << endl << endl;
			cout << "�� â�� �������� �ƹ�Ű�� �����ּ���.";
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
				cerr << "\n������ ���� ����� �� �����ϴ�: \"" << string(ex) << "\"" << endl << endl;
				for (CalculatorException e : *exceptions) {
					cerr << "* " << e.message.str() << endl;
				}
				cerr << endl << exceptions->size() << "���� ������ �߻��Ͽ� ����� �ߴ��մϴ�." << endl << endl;
				delete exceptions;
				exnum++;
				continue;
			}
			exnum++;
		}
		input.close();
		cout << endl << "���� �Է��� ���� ����� �Ϸ��Ͽ����ϴ�." << endl << endl;
		cout << "�� â�� �������� �ƹ�Ű�� �����ּ���.";
	}

	getch();
	return 0;
}

