#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <iostream>
#include <string>
#include <vector>

// Base class for a general Item
class Item {
protected:
    int id;
    std::string title;
    std::string author;
    std::string publicationDate;

public:
    Item(int id, const std::string& title, const std::string& author, const std::string& pubDate);
    virtual ~Item();  // Destructor (no "= default")

    virtual void displayDetails() const;  // No override keyword
    int getId() const;
};

// Derived class from Item for a Book
class Book : public Item {
public:
    Book(int id, const std::string& title, const std::string& author, const std::string& pubDate);
    void displayDetails() const;  // No override keyword
};

// User class encapsulating user details and borrowed books
class User {
private:
    int id;
    std::vector<Item*> borrowedItems;  // Using raw pointers instead of shared_ptr

public:
    User(int id);
    ~User();  // Destructor to clean up borrowed items
    void borrowItem(Item* item);
    void returnItem(int itemId);
    void displayBorrowedItems() const;
};

// Library class managing all items
class Library {
private:
    std::vector<Item*> items;  // Using raw pointers instead of shared_ptr

public:
    ~Library();  // Destructor to clean up items
    void addItem(Item* item);
    Item* searchItem(int id) const;
    void displayAvailableItems(const User& user) const;
};

// Menu class to interact with users
class Menu {
private:
    Library& library;
    User& user;

public:
    Menu(Library& library, User& user);
    void displayMenu();
};

#endif // LIBRARY_SYSTEM_H

