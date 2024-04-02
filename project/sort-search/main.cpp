#include "list.h"
#include "timing.h"
#include "list-generation.h"
#include "random.h"

using std::cout;
using std::cin;
using std::endl;

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

Error_code group_2_single_run(const List<int> &list)
{
	Error_code status = success;
	int target = (rand() % list.size() + 1) * 2 - 1;
	int position;
	clock_t clk_cycles[2];
	double time[2];

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

	cout	<< '|' 
			<< time[0] 
			<< "\t|" 
			<< clk_cycles[0] 
			<< "\t|" 
			<< time[1]
			<< "\t|"
			<< clk_cycles[1]
			<< "\t|"
			<< target
			<< "\t|"
			<< endl;
	return status;
}

Error_code group_2()
{
	List<int> list;
	Error_code status = success;
	Random rand(false);
	size_t list_size;

	cout << "Enter data size (length of the lists): ";
	cin >> list_size;

	status = sorted_two_n_minus_one(list_size, list);
	if (status != success) { return status; }
	cout << "+---------------+---------------+-------+" << endl;
	cout << "|  Sequential   |    Binary     |       |" << endl;
	cout << "|Time   |Cycles |Time   |Cycles |Target |" << endl;
	cout << "+-------+-------+-------+-------+-------+" << endl;
	for (int i = 0; i < 10; i++) {
		status = group_2_single_run(list);
		if (status != success) { return status; }
	}
	cout << "+---------------+---------------+-------+" << endl;
	return status;
}

int main()
{
	srand(time(NULL));
	const char *choices[] = {
		"Sequential search on sorted list",
		"Binary search on sorted list",
		"Insertion sort on randomized data",
		"Merge sort on randomized data",
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
	}
	if (status == success) { return 0; }
	return 1;
}
