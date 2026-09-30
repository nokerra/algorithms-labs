#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Route {
private:
    string pointA;
    string pointB;
    string pointC;

public:
    Route(const string& a, const string& b, const string& c) 
        : pointA(a), pointB(b), pointC(c) {
        cout << "Точки маршрута заданы" << endl;
    }

    ~Route() {
        cout << "Маршрут удалён" << endl;
    }
};

class Bus {
private:
    int number;
    Route* busRoute;

public:
    Bus(int n) : number(n), busRoute(nullptr) {
        cout << "Автобус с номером " << n << " создан" << endl;
    }

    ~Bus() {
        cout << "Автобус удалён" << endl;
    }

    void setBusRoute(Route* r) {
        busRoute = r;
    }

    Route* getBusRoute() const {
        return busRoute;
    }
};

class Depot {
private:
    static Depot* instance;
    vector<Bus*> buses;

    Depot() {}

public:
    Depot(const Depot&) = delete;
    Depot& operator=(const Depot&) = delete;

    static Depot* getInstance() {
        if (instance == nullptr) {
            instance = new Depot();
        }
        return instance;
    }

    void addBus(Bus* b) {
        buses.push_back(b);
    }
};

Depot* Depot::instance = nullptr;

int main() {
    setlocale(LC_ALL, "ru");
    
    Route route("Макарова", "Юности", "Кулакова");
    Bus bus(101);

    bus.setBusRoute(&route);

    Depot* depot = Depot::getInstance();
    depot->addBus(&bus);

    return 0;
}
