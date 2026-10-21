#include <iostream>
#include <vector>
#include "Car.h"

using namespace std;

int main() {
    Car regularCar("Sedan Toyota", 200);
    Truck cargoTruck("Kamaz Cargo", 120, 15.5);
    cout << "Car object: ";
    regularCar.printf();
    cout << endl;

    cout << "Truck object: ";
    cargoTruck.printf();
    cout << endl << endl;

    //статический полиморфизм
    regularCar.printf(true);
    cout << endl;
    cargoTruck.printf("[Truck Info]");
    cout << endl << endl;

    //динамический полиморфизм
    Car *pCar1 = &regularCar;
    Car *pCar2 = &cargoTruck;

    cout << "Pointer to car (Car): ";
    pCar1->printf();
    cout << endl;

    cout << "Pointer to car (Truck): ";
    pCar2->printf();
    cout << endl << endl;
    //создание вектора указателей на объекты разных классов
    vector<Car*> vehicleVector;
    vehicleVector.push_back(&regularCar);
    vehicleVector.push_back(&cargoTruck);
    for (size_t i = 0; i < vehicleVector.size(); i++) {
        cout << "Vehicle #" << i + 1 << ": ";
        vehicleVector[i]->printf();
        cout << endl;
    }

    return 0;
}