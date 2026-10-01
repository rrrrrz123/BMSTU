#include <iostream>
#include <string>
#include <vector>
struct zhitel;
using namespace std;
struct address
{
    string street;
    int house;
    int flat;
};
struct zhitel
{
    string fullname;
    address Address;
    char gender;
    int age;
};
int main()
{
    int n;
    cout<<"Enter quantity of residents: "<<endl;
    cin>>n;
    vector<zhitel> database(n);
    for (int i = 0; i < n; i++)
    {
        cout<<"Enter for resident "<< i + 1<<endl;
        cin.ignore();
        cout<<"Enter fullname: "<<endl;
        getline(cin, database[i].fullname);
        cout<<"Enter street:"<< endl;
        getline(cin, database[i].Address.street);
        cout <<"Enter gender (M/m for male F/f for female): "<<endl;
        cin >> database[i].gender;
        cout <<"Enter age: "<< endl;
        cin>> database[i].age;
        cout <<"Enter number of house: "<< endl;
        cin >> database[i].Address.house;
        cout << "Enter number of flat: "<<endl;
        cin >> database[i].Address.flat;

    }

    cout << "List of all residents"<< endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << database[i].fullname
        << ", age: " << database[i].age
        << ", gender: " << database[i].gender
        << ", street: " << database[i].Address.street
        << ", house:  " << database[i].Address.house
        << ", flat:  " << database[i].Address.flat << endl;
    }
    cout<<endl;
    //Подсчет количества пенсионеров
    int pensioners = 0;

    for (int i = 0; i < n; i++) {
        if ((database[i].gender == 'M' || database[i].gender == 'm') && database[i].age >= 60) {
            pensioners++;
        }
        if ((database[i].gender == 'F' || database[i].gender == 'f') && database[i].age >= 55) {
            pensioners++;
        }
    }
    cout <<"Quantity of pensioners: " << pensioners << endl;
    return 0;
}