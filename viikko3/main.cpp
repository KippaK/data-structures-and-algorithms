#include "life.h"
#include <cstdlib>

int main(int argc, char **argv) {
    int row = 20, col = 60;
    if (argc == 3) {
        row = atoi(argv[1]);
        col = atoi(argv[2]);
    }
    Life configuration(row, col);
    system("clear");
    instructions();
    configuration.initialize();
    system("clear");
    configuration.print();
    cout << "Continue viewing new generations? " << endl;
    while (user_says_yes()) {
        system("clear");
        configuration.update();
        configuration.print();
        cout << "Continue viewing new generations? " << endl;
    }
    return 0;
}
