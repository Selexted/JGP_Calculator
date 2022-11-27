#include "Calculator.h"
#include <sstream>
#include "Operand.h"

Calculator::~Calculator()
{
	for (Term* t : _expression_stack) {
		delete t;
	}
}

void Calculator::Calcuoate(char* exp)
{
	Clear();
	ConvertToPostfix(exp);
	CalculateAll();
}

void Calculator::ConvertToPostfix(const string& expression)
{
	stringstream tokens(expression);
	string token;
	vector<char> ops;
	char last_op;
	while (tokens >> token) {
		if (token == "=") {
			break;
		}
		char first_char = token.at(0);
		if (token.length() == 1 && is_operator(first_char))
		{
			if (first_char == OP_OPEN_BRACKET) {
				ops.push_back(first_char);
			}
			else if (first_char == OP_CLOSE_BRACKET) {
				while ((last_op = ops.back(), last_op) != OP_OPEN_BRACKET) {
					ops.pop_back();
					_expression_stack.push_back((Term*)new Operator(last_op));
				}
				ops.pop_back();
			}
			else {
				while (ops.size() > 0 && priority_of((last_op = ops.back(), last_op)) >= priority_of(first_char)
					&& !(last_op == first_char && last_op == OP_EXPONENTIATION))
				{
					ops.pop_back();
					_expression_stack.push_back((Term*)new Operator(last_op));
				}
				ops.push_back(first_char);
			}
		}
		else {
			if (token.find(".") != string::npos) {
				_expression_stack.push_back((Term*)new Operand(stod(token)));
			}
			else {
				_expression_stack.push_back((Term*)new Operand(stoi(token)));
			}
		}
	}
	while (ops.size() > 0) {
		last_op = ops.back();
		ops.pop_back();
		_expression_stack.push_back((Term*)new Operator(last_op));
	}
}

void Calculator::CalculateAll()
{
	vector<Term*>::iterator iter;
	Operator* op;
	Operand* right;
	Operand* left;

	cout << "====Calculate====" << endl;
	for (iter = _expression_stack.begin(); iter < _expression_stack.end(); iter++) {
		if (typeid(**iter) == typeid(Operator)) {
			op = (Operator*)*iter;
			right = (Operand*)*--iter;
			left = (Operand*)*--iter;
			cout << left << " " << op << " " << right << " = ";
			cout << left->Calculate(*op, *right) << endl;
			_expression_stack.erase(iter + 1, iter + 3);
			delete right;
			delete op;
		}
	}
	left = (Operand*)_expression_stack.back();
	while (left->is_exponentiated()) {
		cout << left << " = ";
		cout << left->Dexponentiate() << endl;
	}
	if (left->type() == OPERAND_FRACTION) {
		cout << left << " = ";
		cout << left->FractionToRealNumber() << endl;
	}
	cout << "====Result====" << endl;
	cout << left << endl;
	delete left;
	_expression_stack = vector<Term*>();
}

void Calculator::Clear()
{
	for (Term* t : _expression_stack) {
		delete t;
	}
	_expression_stack = vector<Term*>();
}
