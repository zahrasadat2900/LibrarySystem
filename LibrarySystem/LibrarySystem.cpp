#include "LibrarySystem.h"

// Item class implementation
Item::Item(int id, const std::string& title, const std::string& author, const std::string& pubDate)
    : id(id), title(title), author(author), publicationDate(pubDate) {}

Item::~Item() {
    // Destructor
}

void Item::displayDetails() const {
    std::cout << "ID: " << id << ", Title: " << title << ", Author: " << author
              << ", Publication Date: " << publicationDate << std::endl;
}

int Item::getId() const {
    return id;
}

// Book class implementation
Book::Book(int id, const std::string& title, const std::string& author, const std::string& pubDate)
    : Item(id, title, author, pubDate) {}

void Book::displayDetails() const {
    std::cout << "[Book] ";
    Item::displayDetails();
}

// User class implementation
User::User(int id) : id(id) {}

User::~User() {
    // Free borrowed items
    for (size_t i = 0; i < borrowedItems.size(); ++i) {
        delete borrowedItems[i];
    }
}

void User::borrowItem(Item* item) {
    borrowedItems.push_back(item);
    std::cout << "Book borrowed: " << item->getId() << std::endl;
}

void User::returnItem(int itemId) {
    for (size_t i = 0; i < borrowedItems.size(); ++i) {
        if (borrowedItems[i]->getId() == itemId) {
            delete borrowedItems[i];
            borrowedItems.erase(borrowedItems.begin() + i);
            std::cout << "Book returned: " << itemId << std::endl;
            return;
        }
    }
    std::cout << "Book with ID " << itemId << " not found in borrowed items." << std::endl;
}

void User::displayBorrowedItems() const {
    if (borrowedItems.empty()) {
        std::cout << "No borrowed items." << std::endl;
    } else {
        for (size_t i = 0; i < borrowedItems.size(); ++i) {
            borrowedItems[i]->displayDetails();
        }
    }
}

// Library class implementation
Library::~Library() {
    // Free library items
    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }
}

void Library::addItem(Item* item) {
    items.push_back(item);
}

Item* Library::searchItem(int id) const {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i]->getId() == id) {
            return items[i];
        }
    }
    return NULL;
}

void Library::displayAvailableItems(const User& user) const {
    std::cout << "Available Books:\n";
    for (size_t i = 0; i < items.size(); ++i) {
        items[i]->displayDetails();
    }
}

// Menu class implementation
Menu::Menu(Library& library, User& user) : library(library), user(user) {}

void Menu::displayMenu() {
    int choice;
    do {
        std::cout << "\nOptions:\n";
        std::cout << "1. View Available Books\n";
        std::cout << "2. Borrow a Book\n";
        std::cout << "3. View Borrowed Books\n";
        std::cout << "4. Return a Book\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                library.displayAvailableItems(user);
                break;
            case 2: {
                int bookId;
                std::cout << "Enter Book ID to borrow: ";
                std::cin >> bookId;
                Item* item = library.searchItem(bookId);
                if (item != NULL) {
                    user.borrowItem(item);
                } else {
                    std::cout << "Book not found!" << std::endl;
                }
                break;
            }
            case 3:
                user.displayBorrowedItems();
                break;
            case 4: {
                int bookId;
                std::cout << "Enter Book ID to return: ";
                std::cin >> bookId;
                user.returnItem(bookId);
                break;
            }
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option! Please try again.\n";
        }
    } while (choice != 5);
}
