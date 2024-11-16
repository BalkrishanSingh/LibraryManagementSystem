//
// Created by Balkrishan Singh on 13/11/24.
//

#ifndef LIBRARY_H
#define LIBRARY_H
#include <string>
#include <vector>
#include <memory>
class Book;
class User;
class library;

class Book
{
    std::string bookName;
    std::string author;
    int bookID;

public:
    std::shared_ptr<User> bookBorrower;
    Book(int bookID, std::string bookName, std::string author);
    std::string BookInformation();
};

class User
{
protected:
    std::string userName;
    int password;
    User(std::string userName, int password);
public:
    virtual ~User() = default;
};

class Student : public User
{
    int userID; //Roll no
    Student(int userID, std::string userName, int password);
    std::shared_ptr<Book> borrowedBook;
    public:
        void DisplayIssuedBooks();
};

class Adminstrator : public User
{

};

class Menu {
    static void Registration();
    static void Login();
    static void StudentDashboard();
    static void AdminstratorDashboard();
};

class library
{
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Book>> books;
    void issueBook();
    void addBook();
    void displayBooks();
    void searchBook();

public:
    void RegisterStudent(int userId, std::string userName, int password);
    void LoginUser();
};

#endif // LIBRARY_H
