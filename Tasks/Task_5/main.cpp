#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <clocale>

using namespace std;

struct VideoCard {
    string name;
    int power;
    int year;
    string type;
    string company;
};

void addVideoCard() {
    VideoCard vc;
    cout << "\nВведіть назву: ";
    cin.ignore();
    getline(cin, vc.name);
    cout << "Введіть потужність (Вт): ";
    cin >> vc.power;
    while (true) {
        cout << "Введіть рік випуску (1990-2026): ";
        cin >> vc.year;

        if (vc.year >= 1990 && vc.year <= 2026)
            break;
        else 
            cout << "Помилка! Рік має бути в межах від 1990 до 2026." << endl;
    }
    cout << "Введіть орієнтацію (ПК/Мобільна): ";
    cin.ignore();
    getline(cin, vc.type);
    cout << "Введіть компанію: ";
    getline(cin, vc.company);

    ofstream file("cards.txt", ios::app);
    if (file.is_open()) {
        file << vc.name << endl;
        file << vc.power << endl;
        file << vc.year << endl;
        file << vc.type << endl;
        file << vc.company << endl;
        file.close();
        cout << "Дані успішно збережено!\n" << endl;
    }
}

void showVideoCards(bool filterByYear = false) {
    ifstream file("cards.txt");
    if (!file.is_open()) {
        cout << "Файл порожній або не знайдений!" << endl;
        return;
    }

    VideoCard temp;
    bool found = false;
    cout << "\n--- Результат ---" << endl;

    while (getline(file, temp.name)) {
        file >> temp.power;
        file >> temp.year;
        file.ignore();
        getline(file, temp.type);
        getline(file, temp.company);

        if (filterByYear) {
            if (temp.year >= 2020 && temp.year <= 2022) {
                cout << temp.company << " " << temp.name << " - " << temp.year << " р." << endl;
                found = true;
            }
        }
        else {
            cout << temp.company << " " << temp.name << " - " << temp.year << " р. | " << temp.type << endl;
            found = true;
        }
    }
    file.close();

    if (!found)
        cout << "Даних не знайдено." << endl;
    cout << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Ukrainian");

    int choice = 0;

    while (true) {
        cout << "--- VideoCards ---" << endl;
        cout << "1. Додати нову відеокарту" << endl;
        cout << "2. Переглянути всі відеокарти" << endl;
        cout << "3. Вивести відеокарти 2020-2022 років" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        if (choice == 0) 
            break;

        switch (choice) {
        case 1:
            addVideoCard();
            break;
        case 2:
            showVideoCards();
            break;
        case 3:
            showVideoCards(true);
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n" << endl;
            break;
        }
    }

    cout << "Програму завершено." << endl;
    return 0;
}