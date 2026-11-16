#include "Book.h"

Book::Book() : title("Untitled"), author("Unknown") {}

Book::Book(const std::string& t, const std::string& a) : title(t), author(a) {}

void Book::setTitle(const std::string& t) {
    title = t;
}

std::string Book::getTitle() const {
    return title;
}

void Book::setAuthor(const std::string& a) {
    author = a;
}

std::string Book::getAuthor() const {
    return author;
}

void Book::setPageDetails(int pageNum, const std::string& pageContent) {
    currentPage.setPageNumber(pageNum);
    currentPage.setContent(pageContent);
}

int Book::getCurrentPageNumber() const {
    return currentPage.getPageNumber();
}

std::string Book::getCurrentPageContent() const {
    return currentPage.getContent();
}
