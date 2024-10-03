#include "LibrarySystem.h"

int main() {
    // Library and User setup
    Library library;
    User user(1);

    // Adding some books to the library
    library.addItem(new Book(1, "The Great Gatsby", "F. Scott Fitzgerald", "1925"));
    library.addItem(new Book(2, "1984", "George Orwell", "1949"));
    library.addItem(new Book(3, "To Kill a Mockingbird", "Harper Lee", "1960"));

    // Start user interaction through Menu
    Menu menu(library, user);
    menu.displayMenu();

    return 0;
}
