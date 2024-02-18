#include "stack.h"

#include <iostream>
using std::endl;
using std::cout;
using std::cin;

#include <sstream>
using std::istringstream;

#include <cmath>
using std::pow;
using std::sqrt;
using std::fmod;
using std::stod;

#include <string>
using std::string;
using std::getline;

void print_syntax()
{
	
}


void exit_invalid_syntax(const char* error)
{
	cout << "Invalid syntax for " << error << endl;
	cout << "Exiting...";
	exit(EXIT_FAILURE);
}

void print_result(Stack<double> &s)
{
	double result;
	s.pop_top(result);
	cout << result << endl;
}

void remove_two_elements(Stack<double> &s, double &one, double &two, const char* caller)
{
	if (s.empty()) {
		exit_invalid_syntax(caller);
	}
	s.pop_top(one);
	if (s.empty()) {
		exit_invalid_syntax(caller);
	}
	s.pop_top(two);
}

void square_root(Stack<double> &s)
{
	double d;
	if (s.empty()) {
		exit_invalid_syntax("square root (v)");
	}
	s.pop_top(d);
	d = sqrt(d);
	s.push(d);
}

void power(Stack<double> &s)
{
	double one, two, result;
	remove_two_elements(s, one, two, "power (^)");
	result = pow(two, one);
	s.push(result);
}

void modulo(Stack<double> &s)
{
	double one, two, result;
	remove_two_elements(s, one, two, "modulo (%)");
	result = fmod(two, one);
	s.push(result);
}

void divide(Stack<double> &s)
{
	double one, two, result;
	remove_two_elements(s, one, two, "division (/)");
	result = two / one;
	s.push(result);
}

void multiply(Stack<double> &s)
{
	double one, two, result;
	remove_two_elements(s, one, two, "multiplication (*)");
	result = two * one;
	s.push(result);
}

void substract(Stack<double> &s)
{
	double one, two, result;
	remove_two_elements(s, one, two, "substraction (-)");
	result = two - one;
	s.push(result);
}

void exchange(Stack<double> &s)
{
	double one, two;
	remove_two_elements(s, one, two, "exchange (x)");
	s.push(one);
	s.push(two);
}

void add(Stack<double> &s)
{
	double one, two, sum;
	remove_two_elements(s, one, two, "addition (+)");
	sum = one + two;
	s.push(sum);
}

void sum(Stack<double> &s)
{
	if (s.empty()) {
		exit_invalid_syntax("sum (s)");
	}
	double sum = 0, item = 0;
	while (!s.empty()) {
		s.pop_top(item);
		sum += item;
	}
	s.push(sum);
}

void average(Stack<double> &s)
{
	double sum = 0, item, average;
	int count = 0;
	while (!s.empty()) {
		s.pop_top(item);
		sum += item;
		count++;
	}
	average = sum / count;
	s.push(average);
}

void calculate_from_string(string &input)
{
	istringstream iss(input);
	string word;
	Stack<double> s;
	double item;
	while (iss >> word) {
		if (word == "x") {
			exchange(s);
			continue; 
		}
		if (word == "s") {
			sum(s);
			continue; 
		}
		if (word == "a") {
			average(s);
			continue; 
		}
		if (word == "+") {
			add(s);
			continue; 
		}
		if (word == "-") {
			substract(s);
			continue; 
		}
		if (word == "*") {
			multiply(s);
			continue; 
		}
		if (word == "/") {
			divide(s);
			continue; 
		}
		if (word == "%") {
			modulo(s);
			continue; 
		}
		if (word == "^") {
			power(s);
			continue; 
		}
		if (word == "v") {
			square_root(s);
			continue; 
		}
		item = stod(word);
		s.push(item);
	}
	s.top(item);
	print_result(s);
}

void calculate_from_user_input()
{
	string user_input;
	while (true) {
		cout << "Enter postfix equation or only press enter to exit" << endl;
		std::getline(cin, user_input);
		if (user_input.empty()) {
			cout << "Exiting..." << endl;
			exit(0);
		}
		calculate_from_string(user_input);
	}	
}

void calculate_from_args(int argc, char** argv)
{
	string equation(argv[1]);
	calculate_from_string(equation);
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "ERROR: invalid arguments" << endl;
		print_syntax();
		return 1;
	}
	if (!strcmp(argv[1], "-p")) {
		calculate_from_user_input();
		return 0;
	}
	calculate_from_args(argc, argv);
	return 0;
}
