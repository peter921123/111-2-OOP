#include "Calculator.h"
#include "utility.h"
#include <string>
#include <sstream>
#include <vector>
using namespace std;

string calculation(string operation) {
	stringstream ss(operation);
	double num; char Operator;
	vector<double>num_in_operation;
	ss >> num; num_in_operation.push_back(num);
	while(ss >> Operator) {
		ss >> num;
		if(Operator == '+')
			num_in_operation.push_back(num);
		else if (Operator == '-')
			num_in_operation.push_back(-num);
		else if (Operator == '*') {
			double temp = num_in_operation[num_in_operation.size()-1];
			num_in_operation.pop_back();
			temp = temp * num;
			num_in_operation.push_back(temp);
		}else if (Operator == '/') {
			double temp = num_in_operation[num_in_operation.size()-1];
			num_in_operation.pop_back();
			temp = temp / num;
			num_in_operation.push_back(temp);
		}
	}
	double result = 0;
	for (int i=0; i<num_in_operation.size(); i++) {
		result += num_in_operation[i];
	}
	return to_string(result);
}


Window Calculator::window(50, 30);
Label* Calculator::display = new Label(41, 5, "",Alignment::RIGHT);
string Calculator::expression = "";

void Calculator::exitWindow(View* view) {
	window.setExit();	
}

void Calculator::pressSymbolButton(View* view) {
	expression += dynamic_cast<Button*>(view)->getText();
	display->setOutput(expression);
}

void Calculator::pressEqualButton(View* view) {
	string result = calculation(expression);
	display->setOutput(result);
	expression = "";
}

Calculator::~Calculator() {
	View::deleteAllView();
}

Calculator::Calculator() {
	for(int i=0; i<10; i++)
		numButtons[i] = new Button(9, 5, to_string(i));
	exitButton = new Button(19, 3, "Exit");
	dotButton = new Button(9, 5, ".");
	addButton = new Button(9, 5, "+");
	subButton = new Button(9, 5, "-");
	mulButton = new Button(9, 5, "*");
	divButton = new Button(9, 5, "/");
	eqButton = new Button(9, 5, "=");

	window.addView(display, 6-2, 3-2);

	window.addView(exitButton, 17-2, 28-2);
	window.addView(dotButton, 17-2, 23-2);
        window.addView(addButton, 37-2, 18-2);
	window.addView(subButton, 37-2, 23-2);	
	window.addView(mulButton, 37-2, 13-2);	
	window.addView(divButton, 37-2, 8-2);	
	window.addView(eqButton, 27-2, 23-2);

	window.addView(numButtons[0], 7-2, 23-2);
	for (int i=0, y_pos=18; i<3; i++, y_pos-=5) {
		for(int j=3*i+1, x_pos=7; j<=3*(i+1); j++, x_pos+=10) {
			window.addView(numButtons[j], x_pos-2, y_pos-2);
		}
	}

	for(int i=0; i<10; i++)
		numButtons[i]->setOnClickListener(pressSymbolButton);
	exitButton->setOnClickListener(exitWindow);
	dotButton->setOnClickListener(pressSymbolButton);
	addButton->setOnClickListener(pressSymbolButton);
	subButton->setOnClickListener(pressSymbolButton);
	mulButton->setOnClickListener(pressSymbolButton);
	divButton->setOnClickListener(pressSymbolButton);
	eqButton->setOnClickListener(pressEqualButton);


}

void Calculator::run() {
	window.run();
}

