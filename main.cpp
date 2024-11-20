#include <iostream>
#include "library.h"

int main() {
    library lib;
    std::cout << "Welcome to Library management System! ";
    char choice;
    std::cout << "Registered Already? (y/n)";
    std::cin >> choice;
    toupper(choice);
    if (choice == 'y') {
        Menu::Login(lib);
    } else if (choice == 'n') {
        Menu::Registration(lib);
        Menu::Login(lib);
    }
    lib.displayBooks();
    return 0;
}
