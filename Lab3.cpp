#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack>
#include <string>

class MPAuto {
protected:
	std::vector<std::string> letters;
	std::vector<std::string> magsymb;
	std::stack<char> stack;
	std::string line;
	std::string output;
	short accept = 0;
	short end = 0;

	virtual int CheckLine(std::string *str);

public:
	MPAuto();
	~MPAuto() {}
	virtual std::string GetOutput() = 0;
	virtual void Accept();                // Принять
	void Cancel();                        // Отвергнуть
	void GoFwd();                         // Сдвиг
	void Wait();                          // Удержать
	void Pop();                           // Вытолкнуть
	void Push(char ch);		              // Втолкнуть()
	void Exchange(std::string str);       // Заменить()
	int GetLine();
	void PushLetters(std::vector<std::string> str);
	void PushMagSymbols(std::vector<std::string> str);
	virtual int Work() = 0;
	short GetAccept();
};

MPAuto::MPAuto() {
	stack.push('^');
	magsymb.push_back("^");
}

void MPAuto::Accept() {
	accept = 1;
	end = 1;
}

short MPAuto::GetAccept() {
	return accept;
}

void MPAuto::Cancel() {
	accept = -1;
	end = 1;
}

void MPAuto::GoFwd() {
	line.erase(0, 1);
}

void MPAuto::Wait() {
	return;
}

void MPAuto::Pop() {
	stack.pop();
}

void MPAuto::Push(char ch) {
	stack.push(ch);
}

void MPAuto::Exchange(std::string str) {
	Pop();
	for (unsigned i = 0; i < str.length(); ++i)
		Push(str[i]);
}



int MPAuto::CheckLine(std::string *str) {
	for (unsigned i = 0; i < str->length(); ++i)
		if ((*str)[i] != '1' && (*str)[i] != '0')
			return 0;
	return 1;
}

int MPAuto::GetLine() {
	std::string str;
	std::getline(std::cin, str);
	if (CheckLine(&str)) {
		line = str;
		return 1;
	}
	else return 0;
}

void MPAuto::PushLetters(std::vector<std::string> str) {
	for (unsigned i = 0; i < str.size(); ++i)
		letters.push_back(str[i]);
}


void MPAuto::PushMagSymbols(std::vector<std::string> str) {
	for (unsigned i = 0; i < str.size(); ++i)
		magsymb.push_back(str[i]);

}


class MPAuto1 : virtual public MPAuto {
private:



public:
	MPAuto1();
	~MPAuto1() {}
	std::string GetOutput() { return ""; }
	int Work();
};

MPAuto1::MPAuto1() {
	std::vector<std::string> str;
	str.push_back("0");
	str.push_back("1");
	PushLetters(str);
	str.clear();
	str.push_back("Z");
	str.push_back("A");
	PushMagSymbols(str);
}

int MPAuto1::Work() {
	char p;
	while (!end) {
		p = stack.top();

		if (!line.length()) {
			
			if (p == magsymb[0][0]) { // ^
				Cancel();
			}
			else if (p == magsymb[1][0]) { // Z
				Accept();
			}
			else if (p == magsymb[2][0]) { // A
				Accept();
			}

		}
		else {
			if (letters[0][0] == line[0]) { // 0
				if (p == magsymb[0][0]) {
					Cancel();
				}

				else if (p == magsymb[1][0]) {
					Pop();
					GoFwd();
				}

				else if (p == magsymb[2][0]) {
					GoFwd();
				}
			}
			else { // 1
				if (p == magsymb[0][0]) {
					Push(magsymb[2][0]);
					Push(magsymb[1][0]);
					GoFwd();
				}

				else if (p == magsymb[1][0]) {
					GoFwd();
				}

				else if (p == magsymb[2][0]) {
					Cancel();
				}

			}
		}
	}
	return accept;
}




class MPAuto2 : virtual public MPAuto {
private:
	void ToPrint(char ch);  // Выдать() 
	int CheckLine(std::string *str);
	void Accept();
public:
	MPAuto2();
	~MPAuto2() {}
	std::string GetOutput();
	int GetLine();
	int Work();
};


MPAuto2::MPAuto2() {
	std::vector<std::string> str;
	str.push_back("0");
	str.push_back("1");
	PushLetters(str);
	str.clear();
	str.push_back("Z");
	str.push_back("A");
	str.push_back("B");
	PushMagSymbols(str);
}

std::string MPAuto2::GetOutput() {
	return output;
}

int MPAuto2::CheckLine(std::string *str) {
	for (unsigned i = 0; i < str->length(); ++i)
		if ((*str)[i] != '1' && (*str)[i] != '0')
			return 0;

	int n = 0, m = 0, n1 = 0, m1 = 0;
	unsigned i = 0;
	for (; i < str->length() && (*str)[i] == '1'; ++i, ++n);
	if (!n) return 0;
	for (; i < str->length() && (*str)[i] == '0'; ++i, ++m);
	if (!m) return 0;
	for (; i < str->length() && (*str)[i] == '1'; ++i, ++n1);
	if (n != n1) return 0;
	for (; i < str->length() && (*str)[i] == '0'; ++i, ++m1);
	if (m != m1 || i != str->length()) return 0;

	return 1;
}

int MPAuto2::GetLine() {
	std::string str;
	std::getline(std::cin, str);
	if (CheckLine(&str)) {
		line = str;
		return 1;
	}
	else return 0;
}


void MPAuto2::ToPrint(char ch) {
	output.push_back(ch);
}

void MPAuto2::Accept() {
	accept = 0;
	end = 1;
}

int MPAuto2::Work() {
	char p;
	while (!end) {
		p = stack.top();

		if (!line.length()) {

			if (p == magsymb[0][0]) { // ^
				Accept();
			}
			else if (p == magsymb[1][0]) { // Z
				Cancel();
			}
			else if (p == magsymb[2][0]) { // A
				Cancel();
			}
			else if (p == magsymb[3][0]) { // B
				Cancel();
			}

		}
		else {
			if (letters[0][0] == line[0]) { // 0
				if (p == magsymb[0][0]) {
					Cancel();
				}

				else if (p == magsymb[1][0]) {
					Pop();
					Wait();
				}

				else if (p == magsymb[2][0]) {
					ToPrint(letters[1][0]);
					Exchange("BA");
					GoFwd();
				}

				else if (p == magsymb[3][0]) { // B
					ToPrint(letters[0][0]);
					Pop();
					GoFwd();
				}
			}
			else { // 1
				if (p == magsymb[0][0]) {
					Push(magsymb[2][0]);
					Push(magsymb[1][0]);
					GoFwd();
				}

				else if (p == magsymb[1][0]) {
					GoFwd();
				}

				else if (p == magsymb[2][0]) {
					Pop();
					Wait();
				}

				else if (p == magsymb[3][0]) { // B
					ToPrint(letters[0][0]);
					GoFwd();
				}

			}
		}
	}
	return accept;
}


int main()
{
	int again = 1;
	MPAuto* Auto;
	do {
		char mode = 0;
		std::cout << "What task do you want to check? (1/2)" << std::endl;
		std::cin >> mode;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (mode == '2') {
			std::cout << "Ok, task #2." << std::endl;
			Auto = new MPAuto2();
		}
		else {
			if (mode != '1')
				std::cout << "You gave me incorrect symbol! So ok, it will be task #1." << std::endl;
			else
				std::cout << "Ok, task #1." << std::endl;
			Auto = new MPAuto1();
		}

		std::cout << "Give me the expression. Use only 0 and 1." << std::endl;

		while (!Auto->GetLine())
			std::cout << "Incorrect line for this task!\nGive me the expression. Use only 0 and 1." << std::endl;

		int result = Auto->Work();
		if (!result)
			std::cout << "That's the result: " << Auto->GetOutput() << "." << std::endl;
		else if (result == 1)
			std::cout << "Your line perfectly fit the 1st FSM!" << std::endl;
		else if (result == -1)
			std::cout << "Your line doesn't fit the 1st FSM." << std::endl;


		std::cout << "Again? (1/0)" << std::endl;
		std::cin >> again;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
	} while (again);

	std::cout << "Okay, Good Bye!" << std::endl;
	system("Pause");
	return 0;
}

