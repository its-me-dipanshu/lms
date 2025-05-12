#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string LIBRARIAN_PASSWORD = "password";

// Structure to represent a book
struct Book
{
  string title;
  string author;
  int id;
  bool isIssued = false;
  string issuedTo;
};

// Function to add a book to the library
void addBook(vector<Book> &books)
{
  Book book;
  cout << "Enter the title of the book: ";
  cin.ignore();
  getline(cin, book.title);
  cout << "Enter the author of the book: ";
  getline(cin, book.author);
  cout << "Enter the ID of the book: ";
  cin >> book.id;

  // Check for duplicate ID
  for (const Book &b : books)
  {
    if (b.id == book.id)
    {
      cout << "Book ID already exists. Try again with a different ID." << endl;
      return;
    }
  }

  book.isIssued = false;
  books.push_back(book);
  cout << "Book added successfully!" << endl;
}

// Function to search for a book by title or author
void searchBooks(const vector<Book> &books)
{
  string keyword;
  cout << "Enter a keyword to search for: ";
  cin.ignore();
  getline(cin, keyword);

  cout << "Search Results:" << endl;
  bool found = false;
  for (const Book &book : books)
  {
    if (book.title.find(keyword) != string::npos || book.author.find(keyword) != string::npos)
    {
      cout << "----------------------------------" << endl;
      cout << "Title: " << book.title << endl;
      cout << "Author: " << book.author << endl;
      cout << "ID: " << book.id << endl;
      cout << "Issued: " << (book.isIssued ? "Yes" : "No") << endl;
      if (book.isIssued)
      {
        cout << "Issued To: " << book.issuedTo << endl;
      }
      cout << "----------------------------------" << endl;
      found = true;
    }
  }

  if (!found)
  {
    cout << "No books found matching the keyword." << endl;
  }
}

// Function to issue a book to a student
void issueBook(vector<Book> &books)
{
  int id;
  cout << "Enter the ID of the book to issue: ";
  cin >> id;

  bool found = false;
  for (Book &book : books)
  {
    if (book.id == id)
    {
      if (book.isIssued)
      {
        cout << "Book is already issued." << endl;
      }
      else
      {
        string studentName;
        cin.ignore();
        cout << "Enter the name of the student: ";
        getline(cin, studentName);
        book.isIssued = true;
        book.issuedTo = studentName;
        cout << "Book issued successfully!" << endl;
      }
      found = true;
      break;
    }
  }

  if (!found)
  {
    cout << "Book not found." << endl;
  }
}

// Function to return a book
void returnBook(vector<Book> &books)
{
  int id;
  cout << "Enter the ID of the book to return: ";
  cin >> id;

  bool found = false;
  for (Book &book : books)
  {
    if (book.id == id)
    {
      found = true;
      if (book.isIssued)
      {
        book.isIssued = false;
        book.issuedTo = "";
        cout << "Book returned successfully!" << endl;
      }
      else
      {
        cout << "This book was not issued." << endl;
      }
      break;
    }
  }

  if (!found)
  {
    cout << "Book not found." << endl;
  }
}

// Function to delete an issued book
void deleteIssuedBook(vector<Book> &books)
{
  int id;
  cout << "Enter the ID of the issued book to delete: ";
  cin >> id;

  bool found = false;
  for (size_t i = 0; i < books.size(); i++)
  {
    if (books[i].id == id)
    {
      if (books[i].isIssued)
      {
        books.erase(books.begin() + i);
        cout << "Issued book deleted successfully!" << endl;
      }
      else
      {
        cout << "The book with ID " << id << " is not currently issued." << endl;
      }
      found = true;
      break;
    }
  }

  if (!found)
  {
    cout << "Book not found." << endl;
  }
}

// Function to view all issued books
void viewIssuedBooks(const vector<Book> &books)
{
  cout << "Issued Books:" << endl;
  bool found = false;
  for (const Book &book : books)
  {
    if (book.isIssued)
    {
      cout << "----------------------------------" << endl;
      cout << "Title: " << book.title << endl;
      cout << "Author: " << book.author << endl;
      cout << "ID: " << book.id << endl;
      cout << "Issued To: " << book.issuedTo << endl;
      cout << "----------------------------------" << endl;
      found = true;
    }
  }

  if (!found)
  {
    cout << "No books currently issued." << endl;
  }
}

// Function to display all books
void displayBooks(const vector<Book> &books)
{
  if (books.empty())
  {
    cout << "No books in the library." << endl;
    return;
  }

  for (const Book &book : books)
  {
    cout << "----------------------------------" << endl;
    cout << "Title: " << book.title << endl;
    cout << "Author: " << book.author << endl;
    cout << "ID: " << book.id << endl;
    cout << "Issued: " << (book.isIssued ? "Yes" : "No") << endl;
    if (book.isIssued)
    {
      cout << "Issued To: " << book.issuedTo << endl;
    }
  }
  cout << "----------------------------------" << endl;
}

// Main function
int main()
{
  vector<Book> books;

  while (true)
  {
    cout << "\n----------- Library Management System -----------" << endl;
    cout << "1. Student Login" << endl;
    cout << "2. Librarian Login" << endl;
    cout << "0. Exit" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 0:
      cout << "Exiting the program. Goodbye!" << endl;
      return 0;

    case 1:
    {
      // Student login
      cout << "Student Login" << endl;
      cout << "Do you want to display book records? (yes/no): ";
      string displayChoice;
      cin >> displayChoice;
      if (displayChoice == "yes")
      {
        displayBooks(books);
      }
      break;
    }

    case 2:
    {
      // Librarian login
      cout << "Librarian Login" << endl;
      cout << "Enter the password: ";
      string password;
      cin >> password;
      if (password == LIBRARIAN_PASSWORD)
      {
        while (true)
        {
          cout << "\n----------- Librarian Menu -----------" << endl;
          cout << "1. Add Books" << endl;
          cout << "2. Search Books" << endl;
          cout << "3. Issue Books" << endl;
          cout << "4. Delete Issued Books" << endl;
          cout << "5. View Issued Books" << endl;
          cout << "6. Return Book" << endl;
          cout << "0. Logout" << endl;
          cout << "--------------------------------------" << endl;
          cout << "Enter your choice: ";

          cin >> choice;

          switch (choice)
          {
          case 0:
            cout << "Logging out from the librarian account." << endl;
            break;
          case 1:
            addBook(books);
            break;
          case 2:
            searchBooks(books);
            break;
          case 3:
            issueBook(books);
            break;
          case 4:
            deleteIssuedBook(books);
            break;
          case 5:
            viewIssuedBooks(books);
            break;
          case 6:
            returnBook(books);
            break;
          default:
            cout << "Invalid choice. Please try again." << endl;
          }

          if (choice == 0)
            break;
        }
      }
      else
      {
        cout << "Invalid password. Access denied." << endl;
      }
      break;
    }

    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  }

  return 0;
}
