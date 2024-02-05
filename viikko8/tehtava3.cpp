#include "queue.h"

#include <iostream>
#include <string>

char process_input() {
    std::string line;
    Queue<char> leftPart;

    std::cout << "Input: ";
    std::getline(std::cin, line);

    size_t colonPos = line.find(':');

    if (colonPos == std::string::npos) {
        return 'N';
    }

    for (size_t i = 0; i < colonPos; ++i) {
        leftPart.append(line[i]);
    }

    std::string rightPart = line.substr(colonPos + 1);

    if (leftPart.size() > rightPart.size()) {
        return 'L';
    } else if (rightPart.size() > leftPart.size()) {
        return 'R';
    } else {
        bool same = true;
        while (!leftPart.empty()) {
			char leftChar;
            leftPart.retrieve(leftChar);
            char rightChar = rightPart[rightPart.length() - leftPart.size()];
            leftPart.serve();

            if (leftChar != rightChar) {
                same = false;
                break;
            }
        }
        if (same) {
            return 'S';
        } else {
            return 'D';
        }
    }
}

int main() {
    char result = process_input();
    std::cout << "Output: " << result << std::endl;

    return 0;
}
