//
// Created by Balkrishan Singh on 13/11/24.
//

#ifndef LIBRARY_H
#define LIBRARY_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
class Book;
class User;
class library;

class Book
{   
    bool isIssued;
    std::string bookName;
    std::string author;
    int bookID;

public:
    std::shared_ptr<User> bookBorrower;
    Book(int bookID, std::string bookName, std::string author);
    Book(std::ifstream& inFile);
    void Save(std::ofstream& outFile);
    void BookInformation();
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

    std::shared_ptr<Book> borrowedBook;
    public:
        Student(int userID, std::string userName, int password);
        void DisplayIssuedBook();
};

    class FileManager
    {
    public:
        static void SaveBooks(const std::vector<std::shared_ptr<Book>>& books, const std::string& filename);

        static void LoadBooks(std::vector<std::shared_ptr<Book>>& books, const std::string& filename);

    };

class Administrator : public User
{public:
    Administrator(std::string userName, int password);
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

public:
    void RegisterStudent(int userId, std::string userName, int password);
    library();
    ~library();
    void LoginUser();
    void issueBook();
    void addBook();
    void displayBooks();
    void searchBook();
};

#endif // LIBRARY_H
