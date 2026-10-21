#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Car {
protected:
    string modelName;
    int maxSpeed;
public:
    //конструктор
    Car() : modelName("Unknown"), maxSpeed(0) {}
    Car(string name, int speed) : modelName(name), maxSpeed(speed) {}
    virtual ~Car() {} //виртуальный деструктор
    virtual void printf() const { //виртуальная функци
        cout << "Model: " << modelName << ", max speed: " << maxSpeed << " km/h";
    }
    void printf(bool showh) const {//статический полиморфизм
        if (showh) {
            cout << "[Car Details] ";
        }
        printf();
    }
};
class Truck : public Car {
private:
    double loadCapacity;
public:
    Truck() : Car(), loadCapacity(0.0) {}
    Truck(string name, int speed, double capacity) : Car(name, speed), loadCapacity(capacity) {}
    //переопределенная функция печати параметров
    void printf() const override {
        Car::printf();
        cout << ", load capacity: " << loadCapacity << " tons";
    }
    void printf(string prefix) const {
        cout << prefix << " ";
        printf();
    }
};