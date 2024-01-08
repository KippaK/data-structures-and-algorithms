#include <cstdlib>
#include "life.h"
#include <termios.h>
#include <unistd.h>

#define DEFAULT_GRID_WIDTH 20
#define DEFAULT_GRID_HEIGHT 20

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main(int argc, char **argv)
{
   int row = DEFAULT_GRID_HEIGHT;
   int col = DEFAULT_GRID_WIDTH;  
   for (int i = 1; i < argc; i++) {
      if (argv[i] == "-w" || argv[i] == "--width") {
         if (argc > i + 1) {
            col = atoi(argv[i+1]);
            i++;
         }
      }
      if (argv[i] == "-h" || argv[i] == "--height") {
         if (argc > i + 1) {
            row = atoi(argv[i+1]);
            i++;
         }
      }
   }
   Life life(row, col);
   life.instructions();
   life.initialize();
   system("clear");
   life.print();
   cout << "Press enter to view next generation" << endl;
   getch();
   for (;;) {
      system("clear");
      life.update();
      life.print();
      cout << "Press enter to view nexr generation" << endl;
      getch();
   }
   return 0;
}
