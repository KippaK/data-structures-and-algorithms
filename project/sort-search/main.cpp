#include "list.h"
#include "timing.h"
#include "list-generation.h"
#include "random.h"
#include "utility.h"

#include <cmath>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include <thread>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
using std::thread;
using std::ref;

double round_to(double value, double precision = 1.0)
{
	return std::round(value / precision) * precision;
}

int user_selection(int choice_count, const char *choices[])
{
	int choice;
	do {
		for (int i = 0; i < choice_count; i++) {
			cout << i + 1 << ". " << choices[i] << std::endl;
		}
		cout << "Enter your choice: ";
		cin >> choice;
	} while (choice < 1 || choice > choice_count);
	return choice;
}

Error_code group_1()
{
	size_t list_size;
	List<int> list;
	Error_code status = success;
	Random rand(false);

	cout << "Enter data size (length of the list): ";
	cin >> list_size;

	status = sorted_two_n_minus_one(list_size, list);
	if (status != success) { return status; }
	int target = rand.random_integer(1, list_size) * 2 - 1;
	int position;
	
	status = sequential_search(list, target, position);
	
	if (status == entry_found) {
		cout << "Entry found" << endl;
		cout << "Target value was " << target << endl;
		cout << "Position target was found at " << position << endl;
	}
	else if (status == not_present) {
		cout << "Entry not found" << endl;
		cout << "Target value was " << target << endl;
	}
	else {
		cout << "Error occured while searching for entry" << endl;
		cout << return_error_message(status) << endl;
	}
	
	return status;
}

Error_code group_2_single_run(
	const List<int> &list, 
	clock_t (&clk_cycles)[2],
	double (&time)[2],
	int &target)
{
	Error_code status = success;
	target = (rand() % list.size() + 1) * 2 - 1;
	int position;

	clk_cycles[0] = sorted_search_time(
		list, 
		target, 
		position, 
		sequential_search<int>,
		status
	);
	clk_cycles[1] = sorted_search_time(
		list, 
		target, 
		position, 
		binary_search<int>,
		status
	);
	
	time[0] = ((double) (clk_cycles[0]) / ((double) CLOCKS_PER_SEC));
	time[1] = ((double) (clk_cycles[1]) / ((double) CLOCKS_PER_SEC));
	return status;
}

void run_group_2_single_run(
	const List<int> &list,
	clock_t (&clk_cycles)[2],
	double (&time)[2],
	int &target,
	Error_code &status)
{
	status = group_2_single_run(list, clk_cycles, time, target);
}

Error_code group_2()
{
	List<int> list;
	Error_code status = success;
	Random rand(false);
	size_t list_size;

	cout << "Enter data size (length of the lists): ";
	cin >> list_size;

	cout << "Generating list with size of " << list_size << "..." << endl;
	status = sorted_two_n_minus_one(list_size, list);
	cout << "List generated!" << endl;
	if (status != success) { return status; }

	clock_t clk_cycles[10][2];
	double times[10][2];
	int targets[10];

	vector<thread> threads;

	for (int i = 0; i < 10; i++) {
		threads.emplace_back(
			run_group_2_single_run,
			ref(list),
			ref(clk_cycles[i]),
			ref(times[i]),
			ref(targets[i]),
			ref(status));
	}

	for (auto& thread : threads) {
		thread.join();
	}

	cout << "+-----------------+---------------+------+" << endl;
	cout << "|   Sequential    |     Binary    |      |" << endl;
	cout << "|  Time  | Cycles |  Time  |Cycles|Target|" << endl;
	cout << "+--------+--------+--------+------+------+" << endl;
	
	for (int i = 0; i < 10; i++) {
		cout << '|';
		cout.width(8);
		cout << std::left << times[i][0] << '|';
		cout.width(8);
		cout << std::right << clk_cycles[i][0] << '|';
		cout.width(8);
		cout << std::left << times[i][1] << '|';
		cout.width(6);
		cout << std::right << clk_cycles[i][1] << '|';
		cout.width(6);
		cout << targets[i] << '|' << endl;
	}

	cout << "+--------+--------+--------+------+------+" << endl;
	return status;
}

Error_code group_3_4(Error_code (*sort_func)(List<int>&))
{
	Error_code status = success;
	const size_t LIST_SIZE = 1000;
	const size_t PRINT_SIZE = 200;
	const int MAX_VAL = 10000;
	List<int> list;
	status = random_list(list, LIST_SIZE, MAX_VAL);
	if (status != success) { return status; }

	cout << "--- UNSORTED LIST (first " << PRINT_SIZE << " items) ---" << endl;
	print_first_n_items(list, PRINT_SIZE);
	
	status = (*sort_func)(list);
	if (status != success) { return status; }

	cout << "---- SORTED LIST (first " << PRINT_SIZE << " items) ----" << endl;
	print_first_n_items(list, PRINT_SIZE);

	return status;
}

int main()
{
	srand(time(NULL));
	const char *choices[] = {
		"Sequential search on sorted list",
		"Binary search on sorted list",
		"Insertion sort on randomized data",
		"Quicksort on randomized data",
		"Additional sort on randomized data"
	};
	int choice = user_selection(5, choices);
	Error_code status = success;
	switch (choice) {
	case 1:
		status = group_1();
		break;
	case 2:
		status = group_2();
		break;
	case 3:
		status = group_3_4(insertion_sort);
		break;
	case 4:
		status = group_3_4(quicksort);
	}
	cout << return_error_message(status) << endl;
	if (status == success) { return 0; }
	return 1;
}
