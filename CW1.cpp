#include <iostream>
#include "catch.hpp"
#include <chrono>
#include <string>
#include <iterator>
#include <vector>
#include <ctime>
#include <thread>
#include <fstream>
#include <sstream>

// Forward declaration
class Book;
class Member;

std::vector<Book *> libraryBooks;
std::vector<Member> members; // Vector to store members

// Struct for Date
struct Date
{
    int year;
    int month;
    int day;
};

// Function to get today's date
Date getTodayDate()
{
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct std::tm *currentTime = std::localtime(&now);

    Date todayDate;
    todayDate.year = currentTime->tm_year + 1900;
    todayDate.month = currentTime->tm_mon + 1;
    todayDate.day = currentTime->tm_mday;

    return todayDate;
}

// Function to add days to a Date
Date addDays(const Date &date, int days)
{
    Date result = date;
    result.day += days;

    // Handle overflow
    while (result.day > 30)
    {
        result.day -= 30;
        result.month += 1;

        // Handle overflow of months
        while (result.month > 12)
        {
            result.month -= 12;
            result.year += 1;
        }
    }

    return result;
}

// Struct to store book data
struct BookData
{
    std::vector<std::string> fields;
};

// Class for a Person
class Person
{
private:
    std::string name;
    std::string address;
    std::string email;

public:
    Person(const std::string &name, const std::string &address, const std::string &email)
        : name(name), address(address), email(email) {}

    // getter methods
    const std::string &getName() const { return name; }
    const std::string &getAddress() const { return address; }
    const std::string &getEmail() const { return email; }

    // setter methods
    void setName(const std::string &newName)
    {
        name = newName;
    }

    void setAddress(const std::string &newAddress)
    {
        address = newAddress;
    }

    void setEmail(const std::string &newEmail)
    {
        email = newEmail;
    }
};

// Class for a Book
class Book
{
private:
    int bookId;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    Date dueDate;
    std::string borrower;

public:
    Book(int bookId, const std::string &bookName, const std::string &authorFirstName,
         const std::string &authorLastName, const std::string &bookType, const Date &dueDate,
         const std::string &borrower)
        : bookId(bookId), bookName(bookName), authorFirstName(authorFirstName),
          authorLastName(authorLastName), bookType(bookType), dueDate(dueDate), borrower(borrower) {}

    // getter methods
    int getBookId() const { return bookId; }
    const std::string &getBookName() const { return bookName; }
    const std::string &getAuthorFirstName() const { return authorFirstName; }
    const std::string &getAuthorLastName() const { return authorLastName; }
    const std::string &getBookType() const { return bookType; }
    const Date &getDueDate() const { return dueDate; }
    const std::string &getBorrower() const { return borrower; }

    void returnBook()
    {
        // Implementation for returning a book
    }

    void borrowBook(const Member &member, const Date &dueDate)
    {
    }

    double calculateFine(const Date &today, const Date &returnDate) const
    {
        // Calculate fine for overdue book
        // Implementation for calculating fine

        if (returnDate.year > dueDate.year || (returnDate.year == dueDate.year && returnDate.month > dueDate.month) ||
            (returnDate.year == dueDate.year && returnDate.month == dueDate.month && returnDate.day > dueDate.day))
        {
            // Book is overdue
            // Calculate the number of days overdue
            int daysOverdue = (returnDate.year - dueDate.year) * 365 + (returnDate.month - dueDate.month) * 30 + (returnDate.day - dueDate.day);

            // Fine is $1 per day overdue
            return daysOverdue * 1.0;
        }

        // Book is not overdue, no fine
        return 0.0;
    }
};

// Class for a Member, derived from Person
class Member : public Person
{
private:
    int memberId;
    std::vector<Book> booksLoaned;

public:
    Member(int memberId, const std::string &name, const std::string &address, const std::string &email)
        : Person(name, address, email), memberId(memberId) {}

    int getMemberId() const { return memberId; }

    const std::vector<Book> &getBooksBorrowed() const
    {
        return booksLoaned;
    }

    std::vector<Book> &getBooksBorrowed()
    {
        return booksLoaned;
    }

    void setBooksBorrowed(const Book &book)
    {
        // Add a book to the borrowed books list
        booksLoaned.push_back(book);
    }

    void removeBook(int bookId)
    {
        // Remove a book from the borrowed books list
        // Find the book in the vector and remove it
        auto it = std::remove_if(booksLoaned.begin(), booksLoaned.end(),
                                 [bookId](const Book &book)
                                 { return book.getBookId() == bookId; });

        // Erase the book from the vector if found
        if (it != booksLoaned.end())
        {
            booksLoaned.erase(it, booksLoaned.end());
        }
    }
};

// Class for a Librarian
class Librarian
{
private:
    int staffId;
    std::string name;
    std::string address;
    std::string email;
    int salary;
    int memberId; // Member ID counter
    std::vector<Book> books;

public:
    Librarian(int staffId, const std::string &name, const std::string &address, const std::string &email, int salary)
        : staffId(staffId), name(name), address(address), email(email), salary(salary), memberId(0) {}

    // getter methods
    int getStaffId() const { return staffId; }
    const std::string &getName() const { return name; }
    const std::string &getAddress() const { return address; }
    const std::string &getEmail() const { return email; }
    int getSalary() const { return salary; }

    Member *getMemberById(int memberId)
    {
        for (auto &member : members)
        {
            if (member.getMemberId() == memberId)
            {
                return &member;
            }
        }
        return nullptr; // Member not found
    }

    // Function to add a member
    void addMember()
    {
        // Add a new member to the system
        // Implementation for adding a member

        std::cout << "Enter member details:\n";
        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << "Enter your address: ";
        std::cin >> address;
        std::cout << "Enter your email: ";
        std::cin >> email;

        members.push_back(Member(memberId, name, address, email));

        std::cout << "-----------------------------------\n";
        std::cout << "Successfully registered new member.\n";
        std::cout << "ID: " << memberId << "\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Address: " << address << "\n";
        std::cout << "Email: " << email << "\n";
        std::cout << "-----------------------------------\n";
    }

    // Function to initialize books from CSV data
    void initializeBooks(const std::vector<BookData> &bookData)
    {
        Date today = getTodayDate(); // Get today's date

        for (const auto &bookInfo : bookData)
        {
            int bookId = std::stoi(bookInfo.fields[0]);
            std::string bookName = bookInfo.fields[1];
            std::string authorFirstName = bookInfo.fields[2];
            std::string authorLastName = bookInfo.fields[3];
            std::string bookType = bookInfo.fields[4];

            Date dueDate = today;          // Start with today's date
            dueDate = addDays(dueDate, 3); // Add 3 days to get the due date

            std::string borrower;

            // Create a Book object and add it to the collection
            books.push_back(Book(bookId, bookName, authorFirstName, authorLastName, bookType, dueDate, borrower));
        }
    }

    // Function to issue a book to a member
    void issueBook(int memberId, int bookId)
    {
        for (auto &member : members)
        {
            if (member.getMemberId() == memberId)
            {
                for (auto &book : libraryBooks)
                {
                    if (book->getBookId() == bookId)
                    {
                        // Calculate due date
                        Date dueDate = addDays(getTodayDate(), 3); // Assuming 3 days checkout period

                        // Update book details and member's borrowed books
                        book->borrowBook(member, dueDate);
                        member.setBooksBorrowed(*book);

                        std::cout << "Book: " << book->getBookName() << " issued to Member : " << getName() << "\n";
                        std::cout << "Due Date: " << dueDate.year << "/" << dueDate.month << "/" << dueDate.day << "\n";
                        break;
                    }
                }
            }
        }
    }
    // Return a book from a member
    void returnBook(int memberId, int bookId)
    {
        for (auto &member : members)
        {
            if (member.getMemberId() == memberId)
            {
                bool bookFound = false;

                for (auto &book : member.getBooksBorrowed())
                {
                    if (book.getBookId() == bookId)
                    {
                        // Get today's date
                        Date returnDate = getTodayDate();

                        // Calculate fine before returning the book
                        double fine = book.calculateFine(returnDate, returnDate);
                        if (fine > 0.0)
                        {
                            std::cout << "Fine for overdue book: $" << fine << std::endl;
                        }

                        // Return the book
                        book.returnBook();
                        member.removeBook(bookId);

                        std::cout << "Book returned by Member: " << member.getName() << "\n";
                        bookFound = true;
                        break;
                    }
                }

                if (!bookFound)
                {
                    std::cout << "Book not found for Member: " << member.getName() << "\n";
                }

                break;
            }
        }
    }

    // Function to display borrowed books of a member
    void displayBorrowedBooks(int memberId)
    {
        for (const auto &member : members)
        {
            if (member.getMemberId() == memberId)
            {
                std::cout << "-----------------------------\n";
                std::cout << "Borrowed books for Member ID " << memberId << ":\n";
                const auto &borrowedBooks = member.getBooksBorrowed();

                if (borrowedBooks.empty())
                {
                    std::cout << "No books borrowed.\n";
                }
                else
                {
                    for (const auto &book : borrowedBooks)
                    {
                        std::cout << "Book ID: " << book.getBookId() << "\n";
                        std::cout << "Book Name: " << book.getBookName() << "\n";
                        std::cout << "Author: " << book.getAuthorFirstName() << " " << book.getAuthorLastName() << "\n";
                        std::cout << "-----------------------------\n";
                    }
                }

                return;
            }
        }

        std::cout << "Member ID " << memberId << " not found.\n";
    }

    // methods to calculate fine for a member
    void calcFine(int memberId)
    {
        for (auto &member : members)
        {
            if (member.getMemberId() == memberId)
            {

                // Get today's date
                Date today = getTodayDate();

                // Iterate through the books borrowed by the member
                for (const Book &book : member.getBooksBorrowed())
                {
                    double fine = book.calculateFine(today, today);

                    if (fine > 0.0)
                    {
                        std::cout << "Book ID: " << book.getBookId() << ", Fine: $" << fine << std::endl;
                    }
                    else
                    {
                        std::cout << "Book ID: " << book.getBookId() << ", No fine incurred.\n";
                    }
                }
            }
        }
    }

    // Setter methods
    void setStaffId(int newStaffId)
    {
        staffId = newStaffId;
    }

    void setSalary(int newSalary)
    {
        salary = newSalary;
    }
};

int main()
{
    // load books (csv files)
    std::string filename;
    filename = "library_books.csv";

    // Read CSV file and get the book data
    std::ifstream file(filename);
    std::string temp;
    std::string line;
    std::string bookName;
    int bookId;
    std::string authorFirstName, authorLastName;

    std::cout << "-----------------------------------\n";
    std::cout << "Welcome to the library system\n";
    std::cout << "-----------------------------------\n";
    Librarian admin(1, "Name", "Adress", "email@mail.com", 00);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1; // Return an empty vector in case of an error
    }

    getline(file, line);

    // Reading the CSV file
    while (getline(file, line))
    {
        std::stringstream ss(line);

        /**extract information from each line,
         and use that information to create Book objects**/

        std::getline(ss, temp, ','); // Read bookId
        bookId = stoi(temp);
        std::getline(ss, bookName, ',');        // Read bookName
        std::getline(ss, temp, ',');            // Ignore a field (not used in Book constructor)
        std::getline(ss, authorFirstName, ','); // Read authorFirstName
        std::getline(ss, authorLastName, ',');  // Read authorLastName
        std::getline(ss, temp, ',');            // Ignore a field (not used in Book constructor)

        // add the objects to the vector
        libraryBooks.push_back(new Book(bookId, bookName, authorFirstName, authorLastName, "", Date(), ""));
    }

    // Variable to store the member ID
    int memberId;

    // Menu Bar
    int userChoice = 0;
    do
    {
        std::cout << "-----------------------------------\n";
        std::cout << "Enter the choice: \n";
        std::cout << "[1]. Add a member\n";
        std::cout << "[2]. Issue a book\n";
        std::cout << "[3]. Return a book\n";
        std::cout << "[4]. Display borrowed books\n";
        std::cout << "[5]. Exit\n";

        std::cin >> userChoice;

        switch (userChoice)
        {
        case 1:
            std::cout << "-----------------------------------\n";
            admin.addMember();
            std::cout << "-----------------------------------\n";
            break;
        case 2:
            std::cout << "-----------------------------------\n";
            std::cout << "Enter memberId: ";
            std::cin >> memberId;
            std::cout << "Enter bookID: ";
            std::cin >> bookId;
            admin.issueBook(memberId, bookId);
            break;
        case 3:
            std::cout << "-----------------------------------\n";
            std::cout << "Enter memberId: ";
            std::cin >> memberId;
            std::cout << "Enter bookID: ";
            std::cin >> bookId;
            admin.returnBook(memberId, bookId);

            break;
        case 4:
            std::cout << "-----------------------------------\n";
            std::cout << "Enter memberId: ";
            std::cin >> memberId;
            admin.displayBorrowedBooks(memberId);
            break;

        case 5:
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }

    } while (userChoice != 5);

    return 0;
};