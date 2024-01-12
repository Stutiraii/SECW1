#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
#include <thread>

// Forward declaration
class Member;

// Struct for Date
struct Date {
    int year;
    int month;
    int day;
};

// Function to get today's date
Date getTodayDate() {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct std::tm* currentTime = std::localtime(&now);

    Date todayDate;
    todayDate.year = currentTime->tm_year + 1900;
    todayDate.month = currentTime->tm_mon + 1;
    todayDate.day = currentTime->tm_mday;

    return todayDate;
}

// Function to add days to a Date
Date addDays(const Date& date, int days) {
    Date result = date;
    result.day += days;

    // Handle overflow
    while (result.day > 30) {
        result.day -= 30;
        result.month += 1;

        // Handle overflow of months
        while (result.month > 12) {
            result.month -= 12;
            result.year += 1;
        }
    }

    return result;
}

// Struct to store book data
struct BookData {
    std::vector<std::string> fields;
};

// Function to read CSV and return book data
std::vector<BookData> readCSV(const std::string& filename) {
    std::vector<BookData> books;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return books;  // Return an empty vector in case of an error
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> fields;

        while (getline(iss, token, ',')) {
            fields.push_back(token);
        }

        books.push_back({fields});
    }

    file.close();
    return books;
}

// Class for a Person
class Person {
private:
    std::string name;
    std::string address;
    std::string email;

public:
    Person(const std::string& name, const std::string& address, const std::string& email)
        : name(name), address(address), email(email) {}

    const std::string& getName() const { return name; }
    const std::string& getAddress() const { return address; }
    const std::string& getEmail() const { return email; }

    void setName(const std::string& newName) {
        name = newName;
    }

    void setAddress(const std::string& newAddress) {
        address = newAddress;
    }

    void setEmail(const std::string& newEmail) {
        email = newEmail;
    }
};

// Class for a Book
class Book {
public:
    Book(int bookId, const std::string& bookName, const std::string& authorFirstName,
        const std::string& authorLastName, const std::string& bookType, const Date& dueDate,
        const std::string& borrower)
        : bookId(bookId), bookName(bookName), authorFirstName(authorFirstName),
          authorLastName(authorLastName), bookType(bookType), dueDate(dueDate), borrower(borrower) {}

    int getBookId() const { return bookId; }
    const std::string& getBookName() const { return bookName; }
    const std::string& getAuthorFirstName() const { return authorFirstName; }
    const std::string& getAuthorLastName() const { return authorLastName; }
    const std::string& getBookType() const { return bookType; }
    const Date& getDueDate() const { return dueDate; }
    const std::string& getBorrower() const { return borrower; }

    void returnBook() {
        // Implementation for returning a book
    }

    void borrowBook(const Member& borrower, const Date& dueDate) {
        // Implementation for borrowing a book
    }

    double calculateFine(const Date& today) const {
        if (today.year > dueDate.year || (today.year == dueDate.year && today.month > dueDate.month) ||
            (today.year == dueDate.year && today.month == dueDate.month && today.day > dueDate.day)) {
            // Book is overdue
            // Calculate the number of days overdue
            int daysOverdue = (today.year - dueDate.year) * 365 + (today.month - dueDate.month) * 30 + (today.day - dueDate.day);

            // Fine is $1 per day overdue
            return daysOverdue * 1.0;
        }

        // Book is not overdue, no fine
        return 0.0;
    }

private:
    int bookId;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    Date dueDate;
    std::string borrower;
};

// Class for a Member, derived from Person
class Member : public Person {
public:
    Member(int memberId, const std::string& name, const std::string& address, const std::string& email)
        : Person(name, address, email), memberId(memberId) {}

    int getMemberId() const { return memberId; }

    const std::vector<Book>& getBooksBorrowed() const { return booksLoaned; }

    void setBooksBorrowed(const Book& book) {
        booksLoaned.push_back(book);
    }

private:
    int memberId;
    std::vector<Book> booksLoaned;
};

// Class for a Librarian
class Librarian {
private:
    int staffId;
    std::string name;
    std::string address;
    std::string email;
    int salary;
    int memberIdCounter;  // Member ID counter

    std::vector<Member> members;  // Vector to store members
    std::vector<Book> books;

public:
    Librarian(int staffId, const std::string& name, const std::string& address, const std::string& email, int salary)
        : staffId(staffId), name(name), address(address), email(email), salary(salary), memberIdCounter(0) {}

    int getStaffId() const { return staffId; }
    const std::string& getName() const { return name; }
    const std::string& getAddress() const { return address; }
    const std::string& getEmail() const { return email; }
    int getSalary() const { return salary; }

    // Function to add a member
    void addMember() {
        std::cout << "Enter member details:\n";
        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << "Enter your address: ";
        std::cin >> address;
        std::cout << "Enter your email: ";
        std::cin >> email;

        members.push_back(Member(memberIdCounter++, name, address, email));
               std::cout << "Successfully registered new member.\n";
        std::cout << "ID: " << memberIdCounter - 1 << "\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Address: " << address << "\n";
        std::cout << "Email: " << email << "\n";
    }

    // Function to initialize books from CSV data
    void initializeBooks(const std::vector<BookData>& bookData) {
        Date today = getTodayDate();  // Get today's date

        for (const auto& bookInfo : bookData) {
            // Extract relevant information from bookInfo.fields
            int bookId = std::stoi(bookInfo.fields[0]);
            std::string bookName = bookInfo.fields[1];
            std::string authorFirstName = bookInfo.fields[2];
            std::string authorLastName = bookInfo.fields[3];
            std::string bookType = bookInfo.fields[4];

        
            Date dueDate = today;  // Start with today's date
            dueDate = addDays(dueDate, 3);  // Add 3 days to get the due date

            std::string borrower;

            // Create a Book object and add it to the collection
            books.push_back(Book(bookId, bookName, authorFirstName, authorLastName, bookType, dueDate, borrower));
        }
    }

    // Function to issue a book to a member
    void issueBook(int memberId, int bookId) {
        // Implementation for issuing a book to a member
    }

    // Function to return a book from a member
    void returnBook(int memberId, int bookId) {
        // Implementation for returning a book from a member
    }

    // Function to display borrowed books of a member
    void displayBorrowedBooks(int memberId) {
        // Implementation for displaying borrowed books of a member
    }

    // Function to calculate fine for a member
    void calcFine(const Member& member) {
        Date today = getTodayDate();  // Assuming getTodayDate is a member function or a friend function

        std::cout << "Fine calculation for member " << member.getMemberId() << ":\n";

        // Iterate through the books borrowed by the member
        for (const Book& book : member.getBooksBorrowed()) {
            double fine = book.calculateFine(today);
            std::cout << "Book ID: " << book.getBookId() << ", Fine: $" << fine << std::endl;
        }
    }

    // Getter and Setter for staffId
    void setStaffId(int newStaffId) {
        staffId = newStaffId;
    }

    // Getter and Setter for salary
    void setSalary(int newSalary) {
        salary = newSalary;
    }
};

// ...

int main() {
    std::cout << "Welcome to the library system\n";
    Librarian admin(1, "Stuti", "London", "stuti123@gmail.com", 8000);

    // Add some debugging output
    std::cout << "Getting today's date...\n";
    Date today = getTodayDate();
    std::cout << "Today's date: " << today.year << "-" << today.month << "-" << today.day << std::endl;

    // load books (csv files)
    std::string filename = "library_books.csv";
    // Read CSV file and get the book data
    std::vector<BookData> bookData = readCSV(filename);

    
    admin.initializeBooks(bookData);
    // Modified loop for improved input handling
    int userChoice = 0;
    while (userChoice != 6) {
        std::cout << "Entering the loop\n";

        // Add a pause to observe the output
        std::cout << "Enter the choice: ";
        std::cin >> userChoice;

        // Clear the input buffer to prevent issues with subsequent input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (userChoice) {
            case 1:
                admin.addMember();
                break;
            case 2:
                std::cout << "[2]. Issue a book\n";
                // admin.issueBook();
                break;
            case 3:
                std::cout << "[3]. Return a book\n";
                // admin.returnBook();
                break;
            case 4:
                std::cout << "[4]. Display borrowed books\n";
                // admin.displayBorrowedBooks();
                break;
            case 5:
                std::cout << "[5]. Calculate fine\n";
                // admin.calcFine();
                break;
            case 6:
                std::cout << "[6]. Exit\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }

        std::cout << "Exiting the loop\n";
    }
    return 0;
}
