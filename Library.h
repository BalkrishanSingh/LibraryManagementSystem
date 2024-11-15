//
// Created by Balkrishan Singh on 13/11/24.
//

#ifndef LIBRARY_H
#define LIBRARY_H
#include <string>
#include <vector>
class Book;
class User;
class Library;

class Book {
    std::string bookName;
    std::string author;
    std::string publisher;
    int bookID;
public:
    std::shared_ptr<User> bookBorrower;
    Book(std::string bookName, std::string author, std::string publisher);
};

enum UserType {
    Admin,
    Student
};
class User {

    std::string userName;
    int password;
    int userID;
    UserType userType = UserType::Student;

public:
    std::vector<std::shared_ptr<Book>> borrowedBook;
    User( int userID,std::string borrowerName,int password, UserType userType);
};


class Library {
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Book>> books;
    void issueBook();
    void addBook();
    void displayBooks();
    void searchBook();
public:
    void RegisterUser(int userId,std::string borrowerName,int password, UserType userType);
    void LoginUser();
    void Menu(User activeUser);
};

#endif //LIBRARY_H
