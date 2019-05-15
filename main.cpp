#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

class Book {
    char* title;
    int numOfPages;

    void copy(const Book& other){
        title = new char[strlen(other.title) + 1];
        strcpy(other.title, title);
        numOfPages = other.numOfPages;
    }

public:
    Book(char* _t=nullptr, int _n=0){
        title = new char[strlen(_t) + 1];
        strcpy(_t, title);
        numOfPages = _n;
    }

    char* getTitle() const {
        return title;
    }

    int getNumberOfPages() const {
        return numOfPages;
    }

    void setTitle(char* _t) {
        title = new char[strlen(_t) + 1];
        strcpy(_t, title);
    }

    void setNumberOfPages(int n) {
        numOfPages = n;
    }

    bool operator<(const Book& b2){
        return strcmp(this->title, b2.title) < 0;
    }

    bool operator>(const Book& b2){
        return strcmp(this->title, b2.title) > 0;
    }
};

std::ostream &operator<<(std::ostream &os, const Book &book){
    os << book.getTitle() << ": Pages: " << book.getNumberOfPages() << endl;
}

class EBook : public Book{
    int bytes;
    int views;

public:
    EBook(char* _t, int _n, int _b, int _v) : Book(_t, _n){
        bytes = _b;
        views = _v;
    }

    int getBytes() const {
        return bytes;
    }

    int getViews() const {
        return views;
    }

    int getRating() const {
        if(views > 200) {
            return 5;
        } else {
            return views/40;
        }
    }
};

class Library {
    Book* books;
    int length;
    int current;

    void copyBooks(Book* from, Book* to){
        for(int i = 0; i < length; i++){
            to[i] = from[i];
        }
    }

    void _resize(){
        Book* temp = new Book[length];
        copyBooks(books, temp);

        delete[] books;
        length *= 2;

        books = new Book[length];
        copyBooks(temp, books);
    }

public:
    Library(int _size = 10){
        length = _size;
        current = 0;
        books = new Book[length];
    }

    void add(Book* book){
        current++;
        if(current == length){
            length *= 2;
        }

    }
};

std::ostream &operator<<(std::ostream &os, const EBook &book){
    os << book.getTitle() << ": Pages: " << book.getNumberOfPages() << " , Size: " << book.getBytes() << ", Views: " << book.getViews() << endl;
}

int main(){
    return 0;
}
