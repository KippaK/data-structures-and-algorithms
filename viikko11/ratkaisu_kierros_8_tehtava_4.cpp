#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;


void move(int count, int start, int finish, int temp)
{
    if (count > 0) {
        move(count - 1, start, temp, finish);
        // Commented out the user message for timing analysis
        // cout << "Move disk " << count << " from " << start << " to " << finish << "." << endl;
        move(count - 1, temp, finish, start);
    }
}

void moveIterative(int count, int start, int finish, int temp) {
    int swap;

    while (count > 0) {
        move(count - 1, start, temp, finish);
        // Comment out the line below for analysis
        // cout << "Move disk " << count << " from " << start << " to " << finish << "." << endl;
        count--;
        swap = start;
        start = temp;
        temp = swap;
    }
}

int main()
{
    const int maxDisks = 15;  // Set the maximum number of disks for testing
    high_resolution_clock::time_point t1, t2;

	cout << "move():" << endl;
    for (int disks = 10; disks <= maxDisks; ++disks) {
        t1 = high_resolution_clock::now();  // Record start time
        move(disks, 1, 3, 2);
        t2 = high_resolution_clock::now();  // Record end time

        auto duration = duration_cast<nanoseconds>(t2 - t1).count();
        cout << "Number of Disks: " << disks << ", Execution Time: " << duration << " ns" << endl;
    }

	cout << endl;
	cout << "moveIterative():" << endl;
    for (int disks = 10; disks <= maxDisks; ++disks) {
        t1 = high_resolution_clock::now();  // Record start time
        moveIterative(disks, 1, 3, 2);
        t2 = high_resolution_clock::now();  // Record end time

        auto duration = duration_cast<nanoseconds>(t2 - t1).count();
        cout << "Number of Disks: " << disks << ", Execution Time: " << duration << " ns" << endl;
    }


    return 0;
}

