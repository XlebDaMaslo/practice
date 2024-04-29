#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Razvetvitel {
    string marka;
    string naznachenie;
    int dlinaKabelya;
    string materialProvodnika;
    int kolichestvoPortov;
};

int main() {
    // Создание и запись в файл razvilka.dat
    ofstream outFile("razvilka.dat", ios::binary);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return 1;
    }

    // Заполнение данных о разветвителях
    vector<Razvetvitel> razvetviteli(20);
    // ... Здесь должен быть код для заполнения вектора razvetviteli ...

    // Запись данных в файл
    for (const auto& item : razvetviteli) {
        outFile.write((char*)&item, sizeof(Razvetvitel));
    }
    outFile.close();

    // Чтение из файла и поиск по длине кабеля
    ifstream inFile("razvilka.dat", ios::binary);
    if (!inFile) {
        cerr << "Не удалось открыть файл для чтения." << endl;
        return 1;
    }

    int dlina;
    cout << "Введите длину кабеля для поиска: ";
    cin >> dlina;

    bool found = false;
    Razvetvitel r;
    while (inFile.read((char*)&r, sizeof(Razvetvitel))) {
        if (r.dlinaKabelya == dlina) {
            cout << "Марка: " << r.marka << ", Назначение: " << r.naznachenie
                 << ", Длина кабеля: " << r.dlinaKabelya << ", Материал проводника: "
                 << r.materialProvodnika << ", Количество портов: " << r.kolichestvoPortov << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Разветвитель с длиной кабеля " << dlina << " не найден." << endl;
    }

    inFile.close();
    return 0;
}
