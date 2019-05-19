#include <iostream>
#include <cstring>

using namespace std;

class Device {
    protected:
        char* manufacturer;

    public:
        virtual void print() = 0;
        virtual int getPerf() = 0;
};

class Laptop : public Device {
    int speed;

    public:
        Laptop(char* _m="None", int _s=0){
            manufacturer = new char[strlen(_m) + 1];
            strcpy(manufacturer, _m);
            speed = _s;
        }

        void print(){
            cout << "Manufacturer: " << manufacturer << ", Speed: " << speed << endl;
        }

        int getPerf(){
            return speed;
        }
};

class Car : public Device {
    int kw;
    int volume;

    public:
        Car(char* _m="None", int _k=0, int _v=0){
            manufacturer = new char[strlen(_m) + 1];
            strcpy(manufacturer, _m);
            kw = _k;
            volume = _v;
        }

        void print(){
            cout << "Manufacturer: " << manufacturer << ", Power: " << kw << ", Volume: " << volume << endl;
        }

        int getPerf(){
            return kw;
        }
};

class Inventory {
    const int MAX_ITEMS = 100;
    Device** devices;
    int current;

    public:
        Inventory(){
            devices = new Device*[MAX_ITEMS];
            current = 0;
        }

        void printItems(){
            for(int i = 0; i<current; i++){
                devices[i]->print();
            }
        }

        bool add(Device* device){
            if(current < MAX_ITEMS){
                devices[current++] = device;
                return true;
            }
            return false;
        }

        bool isSorted(){
            for(int i = 0; i < current - 1; i++){
                if(devices[i]->getPerf() >= devices[i + 1]->getPerf()){
                    return false;
                }
            }
            return false;
        }
};

int main(){
    Laptop l;
    Laptop l2("Lenovo", 1600);

    Car c;
    Car c2("Opel", 100, 3000);

    Inventory inv;
    inv.add(&l);
    inv.add(&c);
    inv.add(&c2);
    inv.add(&l2);

    inv.printItems();
    cout << "Items are sorted? " << inv.isSorted() << endl;

    return 0;
}