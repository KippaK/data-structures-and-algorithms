#include "list.h"
#include "timing.h"
#include "list-generation.h"
#include "random.h"
#include "utility.h"
#include "thread-pool.h"

#include <cmath>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include <thread>
#include <stdint.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
using std::thread;
using std::ref;

const size_t GROUP_3_4_LIST_SIZE = 2000;
const size_t GROUP_3_4_PRINT_SIZE = 100;
const int GROUP_3_4_MAX_VAL = 10000;

const int GROUP_5_LIST_MAX_VAL = 10000;

// Raising this value will greatly increase runtime of group 5
const size_t GROUP_5_LIST_SIZE_MULTIPLIER = 100;

void clear_console()
{
#ifdef _WIN32
	system("CLS");
#else
	system("clear");
#endif // _WIN32
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
	List<int> list;
	status = random_list(list, GROUP_3_4_LIST_SIZE, GROUP_3_4_MAX_VAL);
	if (status != success) { return status; }

	cout << "--- UNSORTED LIST (first " << GROUP_3_4_PRINT_SIZE << " items) ---" << endl;
	print_first_n_items(list, GROUP_3_4_PRINT_SIZE);
	
	status = (*sort_func)(list);
	if (status != success) { return status; }

	cout << "---- SORTED LIST (first " << GROUP_3_4_PRINT_SIZE << " items) ----" << endl;
	print_first_n_items(list, GROUP_3_4_PRINT_SIZE);

	return status;
}

void print_line(const uint8_t *col_width, uint8_t col_count)
{
    for (uint8_t i = 0; i < col_count; i++) {
        cout << '+';
        for (uint8_t j = 0; j < col_width[i]; j++) {
            cout << '-';
        }
    }
    cout << '+' << endl;
}

void print_sort_performance(
    clock_t (&times)[10][4], 
    uint32_t (&swaps)[10][4], 
    uint32_t (&comparisons)[10][4])
{
    const char* sorts[] = {
        "Insertion",
        "Bubble",
        "Quick",
        "Heap"
    };
    clear_console();
    const uint8_t col_width[6] = { 6, 14, 13, 13, 13, 13 };

    print_line(col_width, 6);
    cout << "| Size | Stat         ";
    for (int i = 0; i < 4; ++i) {
        cout << '|' << std::setw(col_width[i + 2]) << sorts[i];
    }
    cout << '|' << endl;
    print_line(col_width, 6);

    for (int i = 0; i < 10; ++i) {
        cout	<< '|' << std::setw(5) 
				<< (i + 1) * GROUP_5_LIST_SIZE_MULTIPLIER 
				<< " | Swaps        ";

        for (int j = 0; j < 4; ++j) {
            cout << '|' << std::setw(col_width[j + 2]) << swaps[i][j];
        }
        cout << '|' << endl;

        cout << "|      | Comparisons  ";
        for (int j = 0; j < 4; ++j) {
            cout << '|' << std::setw(col_width[j + 2]) << comparisons[i][j];
        }
        cout << '|' << endl;
/*
        cout << "|      | Clock Cycles ";
        for (int j = 0; j < 4; ++j) {
            cout << '|' << std::setw(col_width[j + 2]) << times[i][j];
        }
        cout << '|' << endl;
*/
        cout << "|      | Time         ";
        for (int j = 0; j < 4; ++j) {
            cout	<< '|' << std::setw(col_width[j + 2]) 
					<< std::fixed << std::setprecision(6) 
					<< ((float)times[i][j]) / CLOCKS_PER_SEC;
        }
        cout << '|' << endl;

        print_line(col_width, 6);
    }
}

Error_code group_5()
{
	Error_code status = success;

	List<int> lists[10][4];

	ThreadPool threads(std::thread::hardware_concurrency());

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 4; j++) {
			size_t list_size = (i + 1) * GROUP_5_LIST_SIZE_MULTIPLIER;
			threads.enqueue([&lists, i, j, list_size](int GROUP_5_LIST_MAX_VAL) {
				random_list_threaded(
					lists[i][j],
					list_size,
					GROUP_5_LIST_MAX_VAL
				);
			}, GROUP_5_LIST_MAX_VAL);
		}
	}
	size_t threadsFinished = 0;
	while (threads.tasksCompleted != 40) {}
	threads.tasksCompleted = 0;


	clock_t times[10][4] = {};
	uint32_t swaps[10][4] = {};
	uint32_t comparisons[10][4] = {};

	Error_code (*sort_func[])(List<int>&, uint32_t&, uint32_t&) = {
		insertion_sort,
		bubble_sort,
		quicksort,
		heapsort
	};

	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			threads.enqueue(
				[&lists, i, j, &swaps, &comparisons, &times, &sort_func]()
			{
				sort_list_time(
					lists[i][j],
					swaps[i][j],
					comparisons[i][j],
					sort_func[j],
					times[i][j]
				);
			});
		}
	}

	threadsFinished = 0;
	while (threads.tasksCompleted != 40) {
		if (threadsFinished != threads.tasksCompleted) {
			threadsFinished = threads.tasksCompleted;
			print_sort_performance(times, swaps, comparisons);
		}
	}
	return status;
}

int main()
{
	srand(time(NULL));
	const char *choices[] = {
		"Sequential search on sorted list",
		"Comparison of sequential and binary search",
		"Insertion sort on randomized data",
		"Quicksort on randomized data",
		"Sort comparisons on randomized data"
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
		break;
	case 5:
		status = group_5();
		break;
	}
	if (status == success) { return 0; }
	return 1;
}
