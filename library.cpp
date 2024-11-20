#include "library.h"
#include "string"
#include <iostream>


Book::Book(int bookID, std::string bookName, std::string author) {
    this->bookID = bookID;
    this->bookName = bookName;
    this->author = author;
}

void Book::BookInformation() {
    std::cout << "Book ID: " << bookID
            << "\nTitle: " << bookName
            << "\nAuthor: " << author
            << "\nIssued: " << (isIssued ? "Yes" : "No") << '\n';
}

User::User(std::string userName, int password) {
    this->userName = userName;
    this->password = password;
}

Student::Student(int userID, std::string userName, int password): User(userName, password) {
    this->userID = userID;
}

Administrator::Administrator(std::string userName, int password): User(userName, password) {
}

void FileManager::SaveBooks(const std::vector<std::shared_ptr<Book> > &books, const std::string &filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for saving.\n";
        return;
    }

    // Write the count of books
    size_t count = books.size();
    outFile.write(reinterpret_cast<const char *>(&count), sizeof(count));

    // Write each book using its Save method
    for (const auto &book: books) {
        book->Save(outFile); // Call the Save method of each book
    }

    // Check if writing was successful
    if (!outFile) {
        std::cerr << "Error writing to file!\n";
    }
}

void FileManager::LoadBooks(std::vector<std::shared_ptr<Book> > &books, const std::string &filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for loading.\n";
        return;
    }
    size_t count;
    inFile.read(reinterpret_cast<char *>(&count), sizeof(count));
    books.clear();
    for (size_t i = 0; i < count; ++i) {
        auto book = std::make_shared<Book>(inFile);
        books.push_back(book);
    }
}


Book::Book(std::ifstream &inFile) {
    inFile.read(reinterpret_cast<char *>(&bookID), sizeof(bookID));

    size_t nameSize;
    inFile.read(reinterpret_cast<char *>(&nameSize), sizeof(nameSize));
    bookName.resize(nameSize);
    inFile.read(&bookName[0], nameSize);

    size_t authorSize;
    inFile.read(reinterpret_cast<char *>(&authorSize), sizeof(authorSize));
    author.resize(authorSize);
    inFile.read(&author[0], authorSize);

    inFile.read(reinterpret_cast<char *>(&isIssued), sizeof(isIssued));
}


void Book::Save(std::ofstream &outFile) {
    // Write the bookID (an integer)
    outFile.write(reinterpret_cast<const char *>(&bookID), sizeof(bookID));

    // Write the size of the bookName string and then the string itself
    size_t nameSize = bookName.size();
    outFile.write(reinterpret_cast<const char *>(&nameSize), sizeof(nameSize));
    outFile.write(bookName.c_str(), nameSize);

    // Write the size of the author string and then the string itself
    size_t authorSize = author.size();
    outFile.write(reinterpret_cast<const char *>(&authorSize), sizeof(authorSize));
    outFile.write(author.c_str(), authorSize);

    // Write the isIssued flag (bool)
    outFile.write(reinterpret_cast<const char *>(&isIssued), sizeof(isIssued));
}

void Student::DisplayIssuedBook() {
    if (borrowedBook) {
        std::cout << "Issued Book Details:\n";
        borrowedBook->BookInformation();
    } else {
        std::cout << "No book has been issued to you.\n";
    }
}


// library Class Definitions

library::library() {
    FileManager::LoadBooks(books, "./books.dat");
}

library::~library() {
    FileManager::SaveBooks(books, "./books.dat");
}

void library::RegisterStudent(int userID, const std::string userName, int password) {
    auto student = std::make_shared<Student>(userID, userName, password);
    users.push_back(student);
    std::cout << "Student registered successfully.\n";
}

void library::LoginUser(bool isAdmin) {
    std::string userName;
    int password;

    std::cout << "Enter Username: ";
    std::cin >> userName;
    std::cout << "Enter Password: ";
    std::cin >> password;

    for (const auto &user: users) {
        if (isAdmin && dynamic_cast<Administrator *>(user.get())) {
            if (user->getUserName() == userName && user->getPassword() == password) {
                std::cout << "Admin login successful!\n";
                Menu::AdminstratorDashboard(*this);
                return;
            }
        } else if (!isAdmin && dynamic_cast<Student *>(user.get())) {
            if (user->getUserName() == userName && user->getPassword() == password) {
                std::cout << "Student login successful!\n";
                Menu::StudentDashboard(*this, std::dynamic_pointer_cast<Student>(user));
                return;
            }
        }
    }

    std::cout << "Invalid credentials!\n";
}

void library::issueBook() {
    int bookID;
    std::cout << "Enter Book ID to issue: ";
    std::cin >> bookID;

    for (auto &book: books) {
        if (!book->isBookIssued()) {
            book->setIssued(true);
            std::cout << "Book issued successfully.\n";
            return;
        }
    }

    std::cout << "Book not available.\n";
}

void library::addBook() {
    int bookID;
    std::string bookName, author;

    std::cout << "Enter Book ID: ";
    std::cin >> bookID;
    std::cout << "Enter Book Name: ";
    std::cin >> bookName;
    std::cout << "Enter Author Name: ";
    std::cin >> author;

    auto newBook = std::make_shared<Book>(bookID, bookName, author);
    books.push_back(newBook);

    std::cout << "Book added successfully.\n";
}

void library::displayBooks() {
    std::cout << "Books in the library:\n";
    for (const auto &book: books) {
        book->BookInformation();
    }
}

void library::searchBook() {
    int bookID;
    std::cout << "Enter Book ID to search: ";
    std::cin >> bookID;

    for (const auto &book: books) {
        if (book->isBookIssued()) {
            book->BookInformation();
            return;
        }
    }

    std::cout << "Book not found.\n";
}

void library::displayIssuedBooksForStudent() {
    std::string studentName;
    std::cout << "Enter your username: ";
    std::cin >> studentName;

    for (const auto &user: users) {
        if (auto student = std::dynamic_pointer_cast<Student>(user)) {
            if (student->getUserName() == studentName) {
                student->DisplayIssuedBook();
                return;
            }
        }
    }

    std::cout << "Student not found or no books issued.\n";
}

// Menu Class Definitions
void Menu::Registration(library &lib) {
    std::cout << "Registration Menu\n1. Register as Student\n2. Exit\n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        int userID, password;
        std::string userName;
        std::cout << "Enter User ID: ";
        std::cin >> userID;
        std::cout << "Enter Username: ";
        std::cin >> userName;
        std::cout << "Enter Password: ";
        std::cin >> password;

        lib.RegisterStudent(userID, userName, password);
    }
}

void Menu::Login(library &lib) {
    std::cout << "Login Menu\n1. Student Login\n2. Admin Login\n3. Exit\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        lib.LoginUser(false);
    } else if (choice == 2) {
        lib.LoginUser(true);
    }
}


void Menu::StudentDashboard(library &lib, std::shared_ptr<Student> activeStudent) {
    std::cout << "Student Dashboard\n1. View Issued Books\n2. Exit\n";
    int choice;
    std::cin >> choice;
    bool running = true;
    while (running) {
        switch (choice) {
            case 1:
                activeStudent->DisplayIssuedBook();
                break;
            default:
                running = false;
                break;
        }
    }
}

void Menu::AdminstratorDashboard(library &lib) {
    std::cout << "Administrator Dashboard\n1. Add Book\n2. Issue Book\n3. Display Books\n4. Exit\n";
    int choice;
    std::cin >> choice;
    bool running = true;
    while (running) {
        switch (choice) {
            case 1:
                lib.addBook();
            case 2:
                lib.issueBook();
                break;
            case 3:
                lib.displayBooks();
                break;
            default:
                running = false;
        }
    }
}
