#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Date{
    int year;
    int month;
    int day;
};
class Member;
class Person {
private:
    string name;
    string address;
    string email;

public:
    Person(const string& name, const string& address, const string& email)
        : name(name), address(address), email(email) {}

    const string& getName() const { return name; }
    const string& getAddress() const { return address; }
    const string& getEmail() const { return email; }

    void setName(const string& newName) {
        name = newName;
    }

    void setAddress(const string& newAddress) {
        address = newAddress;
    }

    void setEmail(const string& newEmail) {
        email = newEmail;
    }
};

class Librarian {
private:
    int staffId;
    string name;
    string address;
    string email;
    int salary;

public:
    Librarian(int staffId, const string& name, const string& address, const string& email, int salary)
        : staffId(staffId), name(name), address(address), email(email), salary(salary) {}

    int getStaffId() const { return staffId; }
    const string& getName() const { return name; }
    const string& getAddress() const { return address; }
    const string& getEmail() const { return email; }
    int getSalary() const { return salary; }

    void addMember() {
        // Implementation for adding a member
    }

    void issueBook(int memberId, int bookId) {
        // Implementation for issuing a book to a member
    }

    void returnBook(int memberId, int bookId) {
        // Implementation for returning a book from a member
    }

    void displayBorrowedBooks(int memberId) {
        // Implementation for displaying borrowed books of a member
    }

    void calcFine(int memberId) {
        // Implementation for calculating fine for a member
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
class Book {
public:
    Book(int bookId, const string& bookName, const string& authorFirstName,
        const string& authorLastName, const string& bookType, const Date& dueDate,
        const string& borrower)
        : bookId(bookId), bookName(bookName), authorFirstName(authorFirstName),
        authorLastName(authorLastName), bookType(bookType), dueDate(dueDate), borrower(borrower) {}

    int getBookId() const { return bookId; }
    const string& getBookName() const { return bookName; }
    const string& getAuthorFirstName() const { return authorFirstName; }
    const string& getAuthorLastName() const { return authorLastName; }
    const string& getBookType() const { return bookType; }
    const Date& getDueDate() const { return dueDate; }
    const string& getBorrower() const { return borrower; }

    void returnBook() {
        // Implementation for returning a book
    }

     void borrowBook(const Member& borrower, const Date& dueDate) {
        // Implementation for borrowing a book
    }

private:
     int bookId;
    string bookName;
    string authorFirstName;
    string authorLastName;
    string bookType;
    Date dueDate;
    string borrower;
};

class Member : public Person {
public:
    Member(int memberId, const string& name, const string& address, const string& email)
        : Person(name, address, email), memberId(memberId) {}

    int getMemberId() const { return memberId; }

    const vector<Book>& getBooksBorrowed() const { return booksLoaned; }

    void setBooksBorrowed(const Book& book) {
        booksLoaned.push_back(book);
    }

private:
    int memberId;
    vector<Book> booksLoaned;
};

int main(){

cout<<"Welcome to the library system\n";
 Librarian admin(1, "Stuti", "London", "stuti123@gmail.com", 8000);

 //load books (csv files)

 //gather user input
 int userChoice = 0;
    while (userChoice < 5) {
        cout << "Enter the choice: \n";
        cin >> userChoice;

        switch (userChoice) {
        case 1:
            cout << "[1].add a member\n";
            break;
        case 2:
            cout << "[2]. issue a book\n";
            break;
        case 3:
            cout << "[3]. return book\n";
            break;
        case 4:
            cout << "[4]. display borrowed books\n";
            break;
        case 5:
            cout << "[5]. calculate fine\n";
            break;
        default:
            cout << "[6]. Exit";
        }
        // use switch statements for user input
    }

    // input handling
    admin.addMember();

    return 0;
}

//main function
//create librarian
//load books
//gather user inputs 
//handle the inputs


//fill in the methods