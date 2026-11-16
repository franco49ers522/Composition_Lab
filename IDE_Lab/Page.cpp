#include "Page.h"

Page::Page() : pageNumber(0), content("Empty Page") {}

Page::Page(int num, const std::string& text) : pageNumber(num), content(text) {}

void Page::setPageNumber(int num) {
    pageNumber = num;
}

int Page::getPageNumber() const {
    return pageNumber;
}

void Page::setContent(const std::string& text) {
    content = text;
}

std::string Page::getContent() const {
    return content;
}
