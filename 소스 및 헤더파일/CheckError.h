#pragma once

class CheckError {
private:

public:
	CheckError() {

	}
	void Check(char ex[]);

	void CheckAllowedChar(char op);

	void CheckParanthese(int open, int close);

	int IsOperation(char tok);

	bool CheckBlank(char op);
};
