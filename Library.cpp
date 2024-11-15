#include "Library.h"
#include <iostream>


Book::Book(std::string bookName, std::string author, std::string publisher) {
    this->bookName = bookName;
    this->author = author;
    this->publisher = publisher;
}

User::User(int userID,std::string userName,int password,UserType userType = UserType::Student) {
    this->userName = userName;
    this->userID = userID;
    this->password = password;
    this->userType = userType;
}

void Library::RegisterUser(int userId,std::string borrowerName,int password, UserType userType) {
    std::cout << std::endl;
    std::cin >> borrowerName >> userId >> password;
    users.push_back(std::make_shared<User>(userId, borrowerName, password, userType));
}
