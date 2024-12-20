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
    //TODO  save which user has issued a book to file.
    Book(int bookID, std::string bookName, std::string author);

    Book(std::ifstream &inFile);

    void Save(std::ofstream &outFile);

    void BookInformation();

    int getBookID() {
        return bookID;
    }

    bool isBookIssued() const { return isIssued; }
    void setIssued(bool status) { isIssued = status; }
};

class User {
protected:
    std::string userName;
    int password;

    User(std::string userName, int password);

public:
    virtual ~User() = default;

    std::string getUserName() const { return userName; }
    int getPassword() const { return password; }
};

class Student : public User {
    int userID; //Roll no
    //TODO Save which book has been borrowed.
    std::shared_ptr<Book> borrowedBook;
    int borrowedBookID;

public:
    void SaveStudent(std::ofstream &outFile);

    Student(int userID, std::string userName, int password);

    void DisplayIssuedBook();

    std::shared_ptr<Book> getBorrowedBook() const { return borrowedBook; }

    void setBorrowedBook(std::shared_ptr<Book> borrowedBook) {
        this->borrowedBook = borrowedBook;
    }

    bool hasIssuedBook() {
        return borrowedBook != nullptr;
    }

    Student(std::ifstream &inFile);

    void studentInformation();
};

class FileManager {
public:
    static void SaveBooks(const std::vector<std::shared_ptr<Book> > &books, const std::string &filename);

    static void LoadBooks(std::vector<std::shared_ptr<Book> > &books, const std::string &filename);

    static void SaveUsers(const std::vector<std::shared_ptr<User> > &users, const std::string &filename);

    static void LoadUsers(std::vector<std::shared_ptr<User> > &users, const std::string &filename);
};

class Administrator : public User {
public:
    Administrator(std::string userName, int password);
};

class library {
    std::shared_ptr<Administrator> administrator;
    std::vector<std::shared_ptr<User> > users;
    std::vector<std::shared_ptr<Book> > books;

public:
    library();

    ~library();

    void RegisterStudent(int userID, std::string userName, int password);

    void LoginUser(bool isAdmin);

    void issueBook(std::shared_ptr<Student> student);

    void addBook();

    void displayBooks();

    void searchBook();

    void displayIssuedBooksForStudent();

    void displaystudents();

    void returnBook(std::shared_ptr<Student> student);

    void AddDummyStudentsToBinaryFile();

    void AddDummyBooksToBinaryFile();
};

class Menu {
public:
    static void Registration(library &lib);

    static void Login(library &lib);

    static void StudentDashboard(library &lib, std::shared_ptr<Student> activeStudent);

    static void AdministratorDashboard(library &lib);
};

#endif // LIBRARY_H
