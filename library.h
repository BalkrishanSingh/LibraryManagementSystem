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

class Book {
    bool isIssued;
    std::string bookName;
    std::string author;
    int bookID;

public:
    std::shared_ptr<User> bookBorrower;
    Book(int bookID, const std::string bookName, const std::string author);
    Book(std::ifstream& inFile);
    void Save(std::ofstream& outFile);
    void BookInformation();
    bool isBookIssued() const { return isIssued; }
    void setIssued(bool status) { isIssued = status; }
};

class User {
protected:
    std::string userName;
    int password;

    User(const std::string userName, int password);

public:
    virtual ~User() = default;
    std::string getUserName() const { return userName; }
    int getPassword() const { return password; } 
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

class library {
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Book>> books;

public:
    library();
    ~library();
    void RegisterStudent(int userID, const std::string userName, int password);
    void LoginUser(bool isAdmin);
    void issueBook();
    void addBook();
    void displayBooks();
    void searchBook();
    void displayIssuedBooksForStudent();
};

class Menu {
public:
    static void Registration(library& lib);
    static void Login(library& lib);
    static void StudentDashboard(library& lib);
    static void AdminstratorDashboard(library& lib);
};

#endif // LIBRARY_H
