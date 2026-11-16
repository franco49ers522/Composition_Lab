#ifndef PAGE_H
#define PAGE_H

#include <string>

class Page {
public:
    Page();
    Page(int num, const std::string& text);
    void setPageNumber(int num);
    int getPageNumber() const;
    void setContent(const std::string& text);
    std::string getContent() const;

private:
    int pageNumber;
    std::string content;
};

#endif
