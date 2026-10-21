<div align="center">

# ОТЧЕТ
**по лабораторной работе №2 по курсу «Алгоритмизация и программирование»**

</div>


**Тема работы:** Изучение классов, перегрузки стандартных операций и наследования в языке C++.  
**Вариант:** №20

**Выполнил:** Студент группы ИУ8-14/6 | Решетникова Таисия Сергеевна  
**Проверил:** Преподаватель Барыкин Дмитрий Васильевич

<div align="center">
Москва, МГТУ — 2026
</div>
---

## 1. Часть 1. Классы и перегрузка операций в C++

### 1.1. Цель работы

Овладение навыками разработки программ на языке C++, использующих классы
и перегрузку стандартных операций.

### 1.2. Условие задачи (Вариант 20)

Дан класс Vector, задающий логический вектор размерности \$n\$.

-   Поля класса: динамический массив элементов типа bool (bool \*p),
    размерность вектора (int n).

-   Конструкторы и деструктор:

    -   Конструктор без параметров (пустой вектор, n = 0);

    -   Конструкторы для инициализации по размеру и на основе обычного
        одномерного массива;

    -   Конструктор копирования;

    -   Конструктор перемещения;

    -   Деструктор.

-   Перегружаемые операции:

    -   Обращение по индексу \[\];

    -   Присваивание с копированием operator=;

    -   Присваивание с перемещением operator=;

    -   Ввод/вывод в поток (\>\>, \<\<);

    -   Логическая операция XOR (\^) над объектом Vector (первый
        операнд) и массивом bool\* (второй операнд) одинаковой
        размерности.

-   Требования к вводу-выводу: чтение данных из файла input.txt, запись
    результатов в output.txt.

### 1.3. Исходный код программы

#### Файл Vector.h
```cpp#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Vector {
    bool *p;
    int n;
public:
    Vector() {
        p = nullptr;
        n = 0;
    }
    Vector(int size) {
        n = size;
        if (n > 0) {
            p = new bool[n];
            for (int i = 0; i < n; i++) p[i] = false;
        } else {
            p = nullptr;
            n = 0;
        }
    }
    Vector(const bool *arr, int size) {
        n = size;
        if (n > 0 && arr != nullptr) {
            p = new bool[n];
            for (int i = 0; i < n; i++) {
                p[i] = arr[i];
            }
        } else {
            p = nullptr;
            n = 0;
        }
    }
    Vector(const Vector &V) {
        n = V.n;
        if (n > 0) {
            p = new bool[n];
            for (int i = 0; i < n; i++) {
                p[i] = V.p[i];
            }
        } else {
            p = nullptr;
            n = 0;
        }
    }
    Vector(Vector &&V) {
        p = V.p;
        n = V.n;
        V.p = nullptr;
        V.n = 0;
    }
    ~Vector() {
        if (p != nullptr) {
            delete[] p;
        }
    }
    int getSize() const {
        return n;
    }
    bool& operator[](int index) {
        return p[index];
    }
    Vector& operator=(const Vector &v2) {
        if (this != &v2) {
            if (p != nullptr) delete[] p;
            n = v2.n;
            if (n > 0) {
                p = new bool[n];
                for (int i = 0; i < n; i++) {
                    p[i] = v2.p[i];
                }
            } else {
                p = nullptr;
                n = 0;
            }
        }
        return *this;
    }
    Vector& operator=(Vector &&v2) {
        if (this != &v2) {
            if (p != nullptr) delete[] p;
            p = v2.p;
            n = v2.n;
            v2.p = nullptr;
            v2.n = 0;
        }
        return *this;
    }

    friend Vector operator^(const Vector &v1, const bool *arr);
    friend ostream& operator<<(ostream &os, const Vector &v);
    friend istream& operator>>(istream &is, Vector &v);
};

Vector operator^(const Vector &v1, const bool *arr) {
    Vector result(v1.n);
    for (int i = 0; i < v1.n; i++) {
        result.p[i] = v1.p[i] ^ arr[i];
    }
    return result;
}

ostream& operator<<(ostream &os, const Vector &v) {
    os << v.n << endl;
    for (int i = 0; i < v.n; i++) {
        os << v.p[i] << " ";
    }
    return os;
}

istream& operator>>(istream &is, Vector &v) {
    int size;
    if (!(is >> size)) return is;

    if (v.p != nullptr) delete[] v.p;
    v.n = size;
    if (v.n > 0) {
        v.p = new bool[v.n];
        for (int i = 0; i < v.n; i++) {
            int val;
            is >> val;
            v.p[i] = (val != 0);
        }
    } else {
        v.p = nullptr;
        v.n = 0;
    }
    return is;
}

```
#### Файл main.cpp (Часть 1)

```cpp
#include <iostream>
#include <fstream>
#include "Vector.h"

using namespace std;

int main() {
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        return 1;
    }
    Vector v1;
    fin >> v1;
    int size = v1.getSize();
    bool *arr = new bool[size];
    for (int i = 0; i < size; i++) {
        int temp;
        fin >> temp;
        arr[i] = (temp != 0);
    }
    fin.close();
    Vector v3 = v1 ^ arr;
    ofstream fout("output.txt");
    if (!fout.is_open()) {
        delete[] arr;
        return 1;
    }
    fout << "Result of v1 ^ arr:\n";
    fout << v3;
    fout.close();

    delete[] arr;

    return 0;
}
```

### 1.4. Контрольный пример и ручной расчет

#### Входные данные (input.txt):

3
1 0 1
0 1 0

Разъяснение данных:

-   3 --- размерность вектора (n = 3).

-   1 0 1 --- значения логического вектора v1.

-   0 1 0 --- значения динамического массива arr.

#### Ручной расчет операции XOR (v1 (+) arr): {#ручной-расчет-операции-xor-v1-arr .unnumbered}

-   V3\[0\] = v1 \[0\] (+) arr\[0\] = 1 (+) 0 = 1

-   v3\[1\] =v1\[1\] (+) arr\[1\] = 0 (+) 1 = 1

-   v3\[2\] = v1\[2\] (+) arr\[2\] = 1 (+) 0 = 1

Ожидаемый результат: размерность 3, элементы 1 1 1.

#### Выходные данные (output.txt):

Result of v1 \^ arr:

3

1 1 1

Вывод: Результат выполнения программы полностью совпадает с ручным
расчетом.

## 2. Часть 2. Наследование классов

### 2.1. Цель работы

Овладение навыками разработки программ на языке C++, использующих
возможности наследования классов, переопределения методов, виртуальных
функций, а также статического и динамического полиморфизма.

### 2.2. Условие задачи (Вариант 20)

-   Базовый класс: Car («автомобиль»).

    -   Поля: modelName (string), maxSpeed (int, статус доступа
        protected).

    -   Методы: конструкторы, виртуальный деструктор, виртуальная
        функция printf() для печати параметров, перегруженный метод
        printf(bool).

-   Производный класс: Truck («грузовой автомобиль»).

    -   Дополнительное поле: loadCapacity (double, грузоподъемность в
        тоннах).

    -   Методы: конструкторы с вызовом конструктора базового класса,
        переопределенная виртуальная функция printf(), перегруженный
        метод printf(string).

-   Требования к демонстрации:

    -   Создать по одному объекту каждого класса и вызвать их функции.

    ```{=html}
    <!-- -->
    ```
    -   Продемонстрировать статический полиморфизм (перегруженные методы
        printf).

    -   Продемонстрировать динамический полиморфизм (вызов
        переопределенного метода через указатель на базовый класс).

    -   Создать вектор указателей vector\<Car\*\> на объекты базового и
        производного классов и вывести данные всех объектов.

### 2.3. Исходный код программы

#### Файл Car.h
```cpp
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
```
#### Файл mainn.cpp (Часть 2)
```cpp
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
```
### 2.4. Результаты работы программы

Вывод программы в консоль:

Car object: Model: Sedan Toyota, max speed: 200 km/h

Truck object: Model: Kamaz Cargo, max speed: 120 km/h, load capacity:
15.5 tons

\[Car Details\] Model: Sedan Toyota, max speed: 200 km/h

\[Truck Info\] Model: Kamaz Cargo, max speed: 120 km/h, load capacity:
15.5 tons

Pointer to car (Car): Model: Sedan Toyota, max speed: 200 km/h

Pointer to car (Truck): Model: Kamaz Cargo, max speed: 120 km/h, load
capacity: 15.5 tons

Vehicle #1: Model: Sedan Toyota, max speed: 200 km/h

Vehicle #2: Model: Kamaz Cargo, max speed: 120 km/h, load capacity: 15.5
tons

## Выводы

В ходе выполнения лабораторной работы:

1.  Разработан класс Vector для работы с логическими векторами
    произвольной размерности, использующий динамическое выделение
    памяти. Перегружены операторы обращения по индексу \[\],
    присваивания с копированием и перемещением =, потокового
    ввода/вывода \>\> и \<\<, а также логический оператор XOR \^.
    Правильность работы программы при файловом вводе/выводе (input.txt /
    output.txt) подтверждена контрольным ручным расчетом.

2.  Изучен механизм наследования и виртуальных функций на примере
    базового класса Car и производного класса Truck. На практике
    продемонстрированы статический полиморфизм (перегрузка методов) и
    динамический полиморфизм (вызов виртуальной функции через указатель
    базового класса и обработка элементов в контейнере
    std::vector\<Car\*\>).
