#include "library.h"
#include "string"
#include <iostream>

library::library() {
    books.push_back(std::make_shared<Book>(1, "The Great Gatsby", "F. Scott Fitzgerald"));
    books.push_back(std::make_shared<Book>(2, "To Kill a Mockingbird", "Harper Lee"));
    books.push_back(std::make_shared<Book>(3, "1984", "George Orwell"));
    books.push_back(std::make_shared<Book>(4, "Moby Dick", "Herman Melville"));
    books.push_back(std::make_shared<Book>(5, "Pride and Prejudice", "Jane Austen"));
}

Book::Book(int bookID, std::string bookName, std::string author)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->author = author;
}
void Book::BookInformation(){
    std::cout << "Book ID: " << bookID
              << "\nTitle: " << bookName
              << "\nAuthor: " << author
              << "\nIssued: " << (isIssued ? "Yes" : "No") << '\n';
}

User::User(std::string userName, int password)
{
    this->userName = userName;
    this->password = password;
}

Student::Student(int userID, std::string userName, int password): User(userName, password) {
    this->userID = userID;
};
Administrator::Administrator(std::string userName, int password): User(userName, password) {

}
void library::RegisterStudent(int userId, std::string borrowerName, int password)
{
    std::cout << std::endl;
    std::cin >> borrowerName >> userId >> password;
    users.push_back(std::make_shared<Student>(userId, borrowerName, password));
}

void FileManager::loadBooks(std::vector<std::shared_ptr<Book>>& books, const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for loading.\n";
        return;
    }
    size_t count;
    inFile.read(reinterpret_cast<char*>(&count), sizeof(count));
    books.clear();
    for (size_t i = 0; i < count; ++i) {
        auto book = std::make_shared<Book>(inFile);
        books.push_back(book);
    }
}


Book::Book(std::ifstream inFile) {
        inFile.read(reinterpret_cast<char*>(&bookID), sizeof(bookID));
        size_t nameSize, authorSize;
        inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        bookName.resize(nameSize);
        inFile.read(&bookName[0], nameSize);
        inFile.read(reinterpret_cast<char*>(&authorSize), sizeof(authorSize));
        author.resize(authorSize);
        inFile.read(&author[0], authorSize);
        inFile.read(reinterpret_cast<char*>(&isIssued), sizeof(isIssued));
    }

void Book::Save(std::ofstream outFile) {

    outFile.write(reinterpret_cast<const char*>(&bookID), sizeof(bookID));
    size_t nameSize = bookName.size();
    size_t authorSize = author.size();
    outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
    outFile.write(bookName.c_str(), nameSize);
    outFile.write(reinterpret_cast<const char*>(&authorSize), sizeof(authorSize));
    outFile.write(author.c_str(), authorSize);
    outFile.write(reinterpret_cast<const char*>(&isIssued), sizeof(isIssued));
}

}
void library::displayBooks(){
    for (const auto& book : books) {
        book->BookInformation();
    }
}


void Menu::StudentDashboard()
{
    std::cout << R"(
========== Library Management System (Student Menu) ==========
Please select an option :
 1. Add Book
 2. Modify Book
 3. Delete Book
 4. View All Books
 5. Exit
=====================================================================
)";
}

void Menu::AdminstratorDashboard()
{
   std::cout << R"(
========== Library Management System (Administrator Menu) ==========
Please select an option :
 Student Menu:
 1. Issue a Book
 2. Return a Book
 3. View Issued Book
 4. Exit
===============================================================
)";
}