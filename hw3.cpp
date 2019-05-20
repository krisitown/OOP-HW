#include <iostream>
#include <cstring>

using namespace std;

class LauncherItem {
    protected:
        char* title;
        bool moveable;

    public:
        virtual char* getTitle() const = 0;
        virtual bool canMove() const = 0;
};

class MobileApp : public LauncherItem {
    public:
        MobileApp(char* _title="None"){
            title = new char[strlen(_title) + 1];
            strcpy(title, _title);
            moveable = true;
        }

        char* getTitle() const {
            return title;
        }

        bool canMove() const {
            return moveable;
        }
};

class SystemWidget : public LauncherItem {
    public:
        SystemWidget(){
            title = "System Widget";
            moveable = false;
        }

        char* getTitle() const {
            return title;
        }

        bool canMove() const {
            return moveable;
        }
};


class Launcher {
    LauncherItem*** screen;
    int n,m;

    public:
        Launcher(int _n=10, int _m=10){
            n = _n;
            m = _m;
            screen = new LauncherItem**[n];
            for(int i = 0; i < n; i++){
                screen[i] = new LauncherItem*[m];
                for(int j = 0; j < m; j++){
                    screen[i][j] = nullptr;
                }
            }
        }

        bool addElement(LauncherItem* el, int i, int j){
            if(screen[i][j] == nullptr){
                screen[i][j] = el;
                return true;
            }

            for(int row = 0; row < n; row++){
                for(int col = 0; col < m; col++){
                    if(screen[row][col] == nullptr){
                        screen[row][col] = el;
                        return true;
                    }
                }
            }

            return false;
        }

        bool removeElement(int i, int j){
            if(screen[i][j] != nullptr && !screen[i][j]->canMove()){
                return false;
            }
            if(screen[i][j] != nullptr){
                screen[i][j] = nullptr;
                return true;
            }
            return false;
        }

        bool moveElement(int i, int j, int k, int l){
            if(screen[i][j] != nullptr && screen[i][j]->canMove() && (screen[k][l] == nullptr ||
                (screen[k][l]->canMove()))){
                LauncherItem* temp = nullptr;
                temp = screen[i][j];
                screen[i][j] = screen[k][l];
                screen[k][l] = temp;
                return true;
            }
            return false;
        }

        int getN() const {
            return n;
        }
        int getM() const {
            return m;
        }

        LauncherItem* getElement(int i, int j) const {
            return screen[i][j];
        }
};

ostream& operator<<(ostream& os, const Launcher& l){
    for(int i = 0; i < l.getN(); i++){
        for(int j = 0; j < l.getM(); j++){
            if(l.getElement(i, j) != nullptr){
                os << "Cooridinates: (" << i << ", " << j << "): Title: " 
                    << l.getElement(i,j)->getTitle() << endl; 
            }
        }
    }
}

int main(){
    MobileApp app("XHamster");
    SystemWidget w;

    Launcher l(10, 5);
    l.addElement(&app, 1,2);
    cout << l;
    cout << "=========" << endl;
    
    l.addElement(&w, 3, 4);
    cout << l;
    cout << "=========" << endl;

    l.moveElement(1,2,3,4);
    cout << l;
    cout << "=========" << endl;

    l.removeElement(1,2);
    cout << l;
    cout << "=========" << endl;

    l.moveElement(3, 4, 1, 1);
    cout << l;
    cout << "=========" << endl;
}