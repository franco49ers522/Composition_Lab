// Jareth Franco
#include "Book.h"
#include "Page.h"
#include <iostream>

int main() {
    Page p1(1, "Introduction to C++.");
    std::cout << "Page " << p1.getPageNumber() << ": " << p1.getContent() << std::endl;

    Book myBook("The C++ Journey", "Bjarne Stroustrup");
    myBook.setPageDetails(42, "Classes and Objects.");

    std::cout << "\nBook Title: " << myBook.getTitle() << std::endl;
    std::cout << "Book Author: " << myBook.getAuthor() << std::endl;
    std::cout << "Current Page: " << myBook.getCurrentPageNumber() << std::endl;
    std::cout << "Page Content: " << myBook.getCurrentPageContent() << std::endl;

    return 0;
}
