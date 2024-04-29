#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Razvetvitel {
    string marka;
    string naznachenie;
    double dlinaKabelya;
    string materialProvodnika;
    int kolichestvoPortov;

    void serialize(ofstream& outFile) const {
        size_t size = marka.size();
        outFile.write((char*)&size, sizeof(size));
        outFile.write(marka.c_str(), size);

        size = naznachenie.size();
        outFile.write((char*)&size, sizeof(size));
        outFile.write(naznachenie.c_str(), size);

        outFile.write((char*)&dlinaKabelya, sizeof(dlinaKabelya));

        size = materialProvodnika.size();
        outFile.write((char*)&size, sizeof(size));
        outFile.write(materialProvodnika.c_str(), size);

        outFile.write((char*)&kolichestvoPortov, sizeof(kolichestvoPortov));
    }

    void deserialize(ifstream& inFile) {
        size_t size;

        inFile.read((char*)&size, sizeof(size));
        marka.resize(size);
        inFile.read(&marka[0], size);

        inFile.read((char*)&size, sizeof(size));
        naznachenie.resize(size);
        inFile.read(&naznachenie[0], size);

        inFile.read((char*)&dlinaKabelya, sizeof(dlinaKabelya));

        inFile.read((char*)&size, sizeof(size));
        materialProvodnika.resize(size);
        inFile.read(&materialProvodnika[0], size);

        inFile.read((char*)&kolichestvoPortov, sizeof(kolichestvoPortov));
    }
};

void showMenu() {
    cout << "\nВыберите действие:" << endl;
    cout << "1. Поиск по марке разветвителя" << endl;
    cout << "2. Поиск по назначению" << endl;
    cout << "3. Поиск по длине кабеля" << endl;
    cout << "4. Поиск по материалу проводника" << endl;
    cout << "5. Поиск по количеству портов" << endl;
    cout << "6. Закрыть программу" << endl;
}

int main() {
    ofstream outFile("razvilka.dat", ios::binary);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return 1;
    }

    vector<Razvetvitel> razvetviteli = {
        {"Belkin", "USB-C док-станция", 1.0, "Медь", 7},
        {"Ugreen", "HDMI сплиттер", 0.5, "Медь", 2},
        {"Anker", "USB 3.0 хаб", 0.2, "Медь", 4},
        {"Cable Matters", "DisplayPort разветвитель", 2.0, "Медь", 2},
        {"StarTech.com", "VGA разветвитель", 1.8, "Медь", 2},
        {"Amazon Basics", "Ethernet сплиттер", 0.15, "Алюминий", 2},
        {"TP-Link", "USB 2.0 хаб", 1.5, "Медь", 7},
        {"Sabrent", "USB-C хаб с HDMI", 0.3, "Медь", 4},
        {"Baseus", "Lightning разветвитель", 0.2, "Медь", 2},
        {"Orico", "SATA разветвитель", 0.5, "Медь", 4},
        {"Vention", "USB-C к двойному HDMI адаптер", 0.15, "Медь", 2},
        {"D-Link", "USB 3.0 хаб с Ethernet", 1.0, "Медь", 5},
        {"Satechi", "USB-C хаб с кардридером", 0.2, "Алюминий", 6},
        {"HyperDrive", "USB-C док-станция для MacBook", 0.0, "Медь", 8},
        {"Plugable", "USB 3.0 хаб с питанием", 1.5, "Медь", 7},
        {"Wavlink", "USB-C хаб с DisplayPort", 0.2, "Медь", 5},
        {"j5create", "USB-C к HDMI адаптер", 0.15, "Медь", 1},
        {"Kensington", "USB-C док-станция с зарядкой", 1.0, "Медь", 6},
        {"CalDigit", "Thunderbolt 4 док-станция", 0.8, "Медь", 18},
        {"Aukey", "USB-C хаб с Power Delivery", 0.2, "Медь", 4}
    };

    for (const auto& item : razvetviteli) {
        item.serialize(outFile);
    }
    outFile.close();

    ifstream inFile("razvilka.dat", ios::binary);
    if (!inFile) {
        cerr << "Не удалось открыть файл для чтения." << endl;
        return 1;
    }

    Razvetvitel r;
    bool found;

    int choice;
    do {
        ifstream inFile("razvilka.dat", ios::binary);
        found = false;
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string marka;
                cout << "Введите марку разветвителя для поиска: ";
                cin.ignore();
                getline(cin, marka);
                
                while (inFile.peek() != EOF) {
                    r.deserialize(inFile);
                    if (r.marka == marka) {
                        cout << "Марка: " << r.marka << ", Назначение: " << r.naznachenie
                            << ", Длина кабеля: " << r.dlinaKabelya << " м, Материал проводника: "
                            << r.materialProvodnika << ", Количество портов: " << r.kolichestvoPortov << endl;
                        found = true;
                    }
                }

                if (!found) {
                    cout << "Разветвитель с маркой разветвителя " << marka << " не найден." << endl;
                }

                inFile.close();
                break;
                }

            case 2: {
                string naznachenie;
                cout << "Введите назначение для поиска: ";
                cin.ignore();
                getline(cin, naznachenie);
                
                while (inFile.peek() != EOF) {
                    r.deserialize(inFile);
                    if (r.naznachenie == naznachenie) {
                        cout << "Марка: " << r.marka << ", Назначение: " << r.naznachenie
                            << ", Длина кабеля: " << r.dlinaKabelya << " м, Материал проводника: "
                            << r.materialProvodnika << ", Количество портов: " << r.kolichestvoPortov << endl;
                        found = true;
                    }
                }

                if (!found) {
                    cout << "Разветвитель с назначением " << naznachenie << " не найден." << endl;
                }

                inFile.close();
                break;
                }

            case 3: {
                double dlina;
                cout << "Введите длину кабеля для поиска: ";
                cin >> dlina;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод. Пожалуйста, введите число." << std::endl;
                    inFile.close();
                    break;
                }
                
                while (inFile.peek() != EOF) {
                    r.deserialize(inFile);
                    if (r.dlinaKabelya == dlina) {
                        cout << "Марка: " << r.marka << ", Назначение: " << r.naznachenie
                            << ", Длина кабеля: " << r.dlinaKabelya << " м, Материал проводника: "
                            << r.materialProvodnika << ", Количество портов: " << r.kolichestvoPortov << endl;
                        found = true;
                    }
                }

                if (!found) {
                    cout << "Разветвитель с длиной кабеля " << dlina << " не найден." << endl;
                }

                inFile.close();
                break;
                }

            case 4: {
                string materialProvodnika;
                cout << "Введите материал проводника для поиска: ";
                cin.ignore();
                getline(cin, materialProvodnika);
                
                while (inFile.peek() != EOF) {
                    r.deserialize(inFile);
                    if (r.materialProvodnika == materialProvodnika) {
                        cout << "Марка: " << r.marka << ", Назначение: " << r.naznachenie
                            << ", Длина кабеля: " << r.dlinaKabelya << " м, Материал проводника: "
                            << r.materialProvodnika << ", Количество портов: " << r.kolichestvoPortov << endl;
                        found = true;
                    }
                }

                if (!found) {
                    cout << "Разветвитель с материалом проводника " << materialProvodnika << " не найден." << endl;
                }

                inFile.close();
                break;
                }

            case 5: {
                int kolichestvoPortov;
                cout << "Введите количество портов для поиска: ";
                cin >> kolichestvoPortov;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод. Пожалуйста, введите число." << std::endl;
                    inFile.close();
                    break;
                }
                
                while (inFile.peek() != EOF) {
                    r.deserialize(inFile);
                    if (r.kolichestvoPortov == kolichestvoPortov) {
                        cout << "Марка: " << r.marka << ", Назначение: " << r.naznachenie
                            << ", Длина кабеля: " << r.dlinaKabelya << " м, Материал проводника: "
                            << r.materialProvodnika << ", Количество портов: " << r.kolichestvoPortov << endl;
                        found = true;
                    }
                }

                if (!found) {
                    cout << "Разветвитель с количеством портов " << kolichestvoPortov << " не найден." << endl;
                }

                inFile.close();
                break;
                }

            case 6:{
                cout << "Программа закрыта." << endl;
                break;
                }

            default:{
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод. Пожалуйста, введите число." << std::endl;
                    inFile.close();
                    break;
                }
                cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
                break;
                }
        }
    } while (choice != 6);

    return 0;


    
    return 0;
}
