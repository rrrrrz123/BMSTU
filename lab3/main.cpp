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