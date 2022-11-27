#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Term.h"
#include "Operator.h"

using namespace std;

class Calculator {
private:
	vector<Term*> _expression_stack;

	void ConvertToPostfix(const string& expression);
	void CalculateAll();
	void Clear();
public:
	Calculator(): _expression_stack() { }
	~Calculator();

	void Calcuoate(char * exp); //콘솔계산
};
