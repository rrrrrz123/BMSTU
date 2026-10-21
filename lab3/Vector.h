#pragma once
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
