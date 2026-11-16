#ifndef BOOK_H
#define BOOK_H

#include "Page.h"
#include <string>

class Book {
public:
    Book();
    Book(const std::string& t, const std::string& a);
    void setTitle(const std::string& t);
    std::string getTitle() const;
    void setAuthor(const std::string& a);
    std::string getAuthor() const;
    void setPageDetails(int pageNum, const std::string& pageContent);
    int getCurrentPageNumber() const;
    std::string getCurrentPageContent() const;

private:
    std::string title;
    std::string author;
    Page currentPage;
};

#endif
