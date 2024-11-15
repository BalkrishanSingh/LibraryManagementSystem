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
    Book(int bookID,std::string bookName, std::string author, std::string publisher);
    std::string BookInformation();
};


class User {
protected:
    std::string userName;
    int password;
    int userID;
public:
    std::shared_ptr<Book>  borrowedBook;
    User( int userID,std::string userName,int password);

    virtual ~User() = default;
    std::string virtual DisplayMenu();
};

class Student :public User{
    std::string DisplayMenu();
};

class Adminstrator : public User {
     std::string  DisplayMenu();
};

class Library {
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Book>> books;
    void issueBook();
    void addBook();
    void displayBooks();
    void searchBook();
public:
    void RegisterUser(int userId,std::string userName,int password);
    void LoginUser();
};

#endif //LIBRARY_H
