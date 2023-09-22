#include <iostream>
#include "../include/file-operations.h"

int main() {
    FileOperations<std::filesystem::path, void> fileOperations(std::make_unique<ListFiles>());
    std::string option;

    while (true) {
        std::cout << ">> ";
        std::cin >> option;
        if (option == "ls") {
            fileOperations.run();
        } else if (option == "exit") {
            break;
        } else {
            std::cout << "Incorrect command." << std::endl;
        }
    }

    return 0;
}
