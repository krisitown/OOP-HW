#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

class Book {
    char* title;
    int numOfPages;

    void copy(const Book& other){
        title = new char[strlen(other.title) + 1];
        strcpy(title, other.title);
        numOfPages = other.numOfPages;
    }

public:
    Book(char* _t="none", int _n=0){
        title = new char[strlen(_t) + 1];
        strcpy(title, _t);
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
        strcpy(title, _t);
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
    EBook(char* _t="none", int _n=10, int _b=1024, int _v=100) : Book(_t, _n){
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
    Book** books;
    int length;
    int current;

    void copyBooks(Book** from, Book** to){
        for(int i = 0; i < length; i++){
            to[i] = from[i];
        }
    }

    void _resize(){
        Book** temp = new Book*[length];
        copyBooks(books, temp);

        delete[] books;
        length *= 2;

        books = new Book*[length];
        copyBooks(temp, books);
    }

    int _get(Book* book){
        for(int i = 0; i < current; i++){
            if(books[i] == book){
                return i;   
            }
        }

        return -1;
    }

public:
    Library(int _size = 10){
        length = _size;
        current = 0;
        books = new Book*[length];
    }

    void add(Book* book){
        current++;
        if(current == length){
            _resize();
        }

        books[current] = book;
    }

    bool remove(Book* book){
        int index = _get(book);
        if(index == -1){return false;}
        length--;
        for(int i = index; i < current; i++){
            books[i] = books[i+1];
        }
        return true;
    }

    float averagePages() {
        int sum = 0;
        for(int i = 0; i < current; i++){
            sum += books[i]->getNumberOfPages();
        }
        return ((float)sum)/((float)current);
    }

    Book operator[](int index){
        return *(books)[index];
    }
};

ostream &operator<<(ostream &os, const EBook &book){
    os << book.getTitle() << ": Pages: " << book.getNumberOfPages() << " , Size: " << book.getBytes() << ", Views: " << book.getViews() << endl;
}

int main(){
    EBook b;
    Book lotr("LotR", 699);
    Library l;
    l.add(&lotr);
    l.add(&b);
    cout << l[1];

    if(lotr < b){
        cout << "LotR < none" << endl;
    } else {
        cout << "LotR >= none" << endl;
    }

    return 0;
}
