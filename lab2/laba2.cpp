#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct item
{
    string title;
    int quantity;
    double price;
};

void print_goods(ostream & out, vector<item> & Goods)
{
    for (auto & pos : Goods)
       out << "Title: " << pos.title << ", Quantity: " << pos.quantity << ", Price: " << pos.price << endl;
}

int main(int argc, const char* argv[]) {

    if (argc != 4) {
       cerr << "Error: Use four parameters\n";
       return 5;
    }

    const string mode(argv[1]);
    const string open_mode(argv[2]);
    const string file_name(argv[3]);

    int n;
    vector<item> Goods;

    if (mode == "write") {
       //ввод данных с клавиатуры
       cout << "n = "; cin >> n;
       Goods.resize(n);

       for (int i = 0; i < n; i++)
       {
          cout << "N = " << (i + 1) << endl;
          cout << "Title: ";
          cin.ignore();
          getline(cin, Goods[i].title);
          cout << "Quantity: "; cin >> Goods[i].quantity;
          cout << "Price: "; cin >> Goods[i].price;
       }

       if (open_mode == "text")
       {
          ofstream foutt(file_name);
          foutt << n << endl;
          for (auto & pos : Goods) {
             foutt << pos.title << endl;
             foutt << pos.quantity << ' ' << pos.price << endl;
          }
          foutt.close();
       }
       else if (open_mode == "binary")
       {
          //работа в двоичном режиме
          ofstream foutb(file_name, ios::binary);
          foutb.write((char *)&n, sizeof(n));
          for (auto pos : Goods) {
             foutb << pos.title << ends;
             foutb.write((char *)&pos.quantity, sizeof(pos.quantity));
             foutb.write((char *)&pos.price, sizeof(pos.price));
          }
          foutb.close();
       }
    }
    else if (mode == "read") {
       if (open_mode == "text")
       {
          ifstream fint(file_name);
          if (!fint)
          {
             cout << endl << "Error, file not found" << endl;
             system("pause");
             return 1;
          }
          fint >> n;
          Goods.resize(n);
          for (auto & pos : Goods) {
             fint.ignore(2, '\n');
             getline(fint, pos.title);
             fint >> pos.quantity;
             fint >> pos.price;
          }
          fint.close();
       }
       else if (open_mode == "binary")
       {
          ifstream finb(file_name, ios::binary);
          if (!finb)
          {
             cout << endl << "Error, file not found" << endl;
             system("pause");
             return 1;
          }
          finb.read((char *)&n, sizeof(n));
          Goods.resize(n);
          for (auto & pos : Goods) {
             getline(finb, pos.title, '\0');
             finb.read((char *)&pos.quantity, sizeof(pos.quantity));
             finb.read((char *)&pos.price, sizeof(pos.price));
          }
          finb.close();
       }

       //печать данных, прочитанных из файла
       print_goods(cout, Goods);
    }
    return 0;
}