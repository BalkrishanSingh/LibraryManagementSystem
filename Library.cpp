#include "Library.h"
#include "string"
#include <iostream>

Book::Book(int bookID, std::string bookName, std::string author, std::string publisher)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->author = author;
    this->publisher = publisher;
}

User::User(int userID, std::string userName, int password)
{
    this->userName = userName;
    this->userID = userID;
    this->password = password;
}

void Library::RegisterUser(int userId, std::string borrowerName, int password)
{
    std::cout << std::endl;
    std::cin >> borrowerName >> userId >> password;
    users.push_back(std::make_shared<User>(userId, borrowerName, password));
}
std::string Student::DisplayStudentMenu()
{
    return R"(
========== Library Management System (Administrator Menu) ==========
Please select an option :
 1. Add Book
 2. Modify Book
 3. Delete Book
 4. View All Books
 5. Exit
=====================================================================
)";
}

std::string Adminstrator::DisplayAdminstratorMenu()
{
    return R"(
========== Library Management System (Student Menu) ==========
Please select an option :
 Student Menu:
 1. Issue a Book
 2. Return a Book
 3. View Issued Book
 4. Exit
===============================================================
)";
}