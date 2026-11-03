<div align="center">

# ОТЧЕТ
### по лабораторной работе №3 по курсу «Алгоритмизация и программирование»

**Тема работы:**  
Изучение функций и стандартных средств ввода-вывода в языке Си++.

**Вариант №20**

<br>

**Выполнил:** Студент группы ИУ8-14/6 | Решетникова Таисия Сергеевна  
**Проверил:** Преподаватель Барыкин Дмитрий Васильевич  

<br>

Москва, МГТУ — 2026

</div>

---

## 1. ИЗУЧЕНИЕ СТАНДАРТНЫХ СРЕДСТВ ВВОДА-ВЫВОДА И РАБОТЫ С ФАЙЛАМИ В СИ++

### 1.1. Цель работы
Овладение навыками разработки программ на языке Си++, использующих ввод-вывод в файлы в текстовом и двоичном режимах, а также обработку аргументов командной строки.

### 1.2. Условие задачи
Создать массив (вектор) объектов структурного типа `item` размерности $n$. Структура «товар в магазине (на складе)» содержит поля: название (`title`), число единиц в наличии (`quantity`), стоимость одной единицы (`price`).

Сохранить вектор в файле в текстовом и двоичном режимах, обеспечить чтение данных из файла. Режимы приложения задаются как параметры командной строки (`mode`, `open_mode`, `file_name`). Сделать выводы о сравнительных размерах двух файлов с данными.

### 1.3. Текст программы с комментариями

```cpp
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
```

### 1.4. Контрольный пример и результаты работы программы

**Результаты работы программы при чтении бинарного файла (read binary goods.dat), изначально данные введены в "write binary goods.txt":**
```text
Title: Water, Quantity: 122, Price: 100 
Title: Juice, Quantity: 23, Price: 345 
```

**Результаты работы программы при чтении текстового файла (read text goods.txt), изначально данные введены в "write text goods.txt":**
```text
Title: Milk, Quantity: 23, Price: 234 
Title: Cheese, Quantity: 67, Price: 6767 
```

---

## 2. СРАВНИТЕЛЬНЫЙ АНАЛИЗ ФАЙЛОВ

| Формат файла | Имя файла | Размер на диске | Особенности хранения |
| :--- | :--- | :--- | :--- |
| **Текстовый (text)** | `goods.txt` | 41 байт | Символьное представление чисел и строк, разделение символами перевода строки. |
| **Двоичный (binary)** | `goods.dat` | 38 байт | Числовые данные хранятся в байтовом виде (через `sizeof`), строки завершаются нулевым байтом. |

---

## 3. ВЫВОДЫ ПО РАБОТЕ

1. В ходе выполнения лабораторной работы были изучены и применены на практике стандартные файловые потоки C++ (`ofstream`, `ifstream`) для реализации чтения и записи данных структурного типа `item`.
2. Реализована обработка 3 параметров командной строки через аргументы `main(argc, argv)` для гибкой настройки режимов работы приложения (`write/read`) и выбора формата (`text/binary`).
3. Проведен анализ структуры файлов: двоичный формат хранит числовые типы данных без преобразования в символы, что обеспечивает отсутствие погрешностей при округлении и экономию дискового пространства.