#include <iostream>
#include <ctime>
#include <chrono>
#include <future>
#include <windows.h>

using namespace std;
using namespace std::chrono;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) 
                min_index = j;
        }
        int tmp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = tmp;
    }
}

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) 
            return mid;
        else if (arr[mid] < key) 
            low = mid + 1;
        else 
            high = mid - 1;
    }
    return -1;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
	setlocale(LC_ALL, "Ukrainian");

    srand(time(0));
    cout.precision(7);
    cout << fixed;

    int userNum;
    cout << "Введіть кількість елементів в масиві: ";
    cin >> userNum;

    int* userArr = new int[userNum];
    for (int i = 0; i < userNum; i++) 
        userArr[i] = rand() % 1000;

    cout << "\nЗгенерований масив: " << endl;
    printArray(userArr, userNum);

    cout << "\nОберіть спосіб сортування:\n1 - Вставкою\n2 - Вибором\n3 - Шелла\nВаш вибір: ";
    int choice;
    cin >> choice;

    auto s1 = high_resolution_clock::now();
    if (choice == 1) 
        insertionSort(userArr, userNum);
    else if (choice == 2) 
        selectionSort(userArr, userNum);
    else 
        shellSort(userArr, userNum);
    auto e1 = high_resolution_clock::now();
    double t_sort = duration<double>(e1 - s1).count();

    cout << "\nВідсортований масив: " << endl;
    printArray(userArr, userNum);

    int searchKey;
    cout << "\nВведіть елемент для пошуку у відсортованому масиві: ";
    cin >> searchKey;

    auto s2 = high_resolution_clock::now();
    int pos = binarySearch(userArr, userNum, searchKey);
    auto e2 = high_resolution_clock::now();
    double t_search = duration<double>(e2 - s2).count();

    if (pos != -1) 
        cout << "Елемент знайдено на позиції: " << pos << endl;
    else 
        cout << "Елемент не знайдено." << endl;

    cout << "\n--- Час виконання вашого запиту ---" << endl;
    cout << "Час сортування: " << t_sort << " сек." << endl;
    cout << "Час пошуку:     " << t_search << " сек." << endl;

    delete[] userArr;

    cout << "\n----- Статистика часу сортування -----" << endl;
    int sizes[] = { 15, 150, 2000, 9000, 40000, 140000 };

    cout << "n\t\tInsertion\tSelection\tShell" << endl;
    cout << "------------------------------------------------------------" << endl;

    for (int i = 0; i < 6; i++) {
        int n = sizes[i];
        int* a1 = new int[n];
        int* a2 = new int[n];
        int* a3 = new int[n];
        for (int j = 0; j < n; j++) 
            a1[j] = a2[j] = a3[j] = rand() % 10000;

        auto start = high_resolution_clock::now();
        insertionSort(a1, n);
        double t1 = duration<double>(high_resolution_clock::now() - start).count();

        start = high_resolution_clock::now();
        selectionSort(a2, n);
        double t2 = duration<double>(high_resolution_clock::now() - start).count();

        start = high_resolution_clock::now();
        shellSort(a3, n);
        double t3 = duration<double>(high_resolution_clock::now() - start).count();

        cout << n << "\t\t" << t1 << "\t" << t2 << "\t" << t3 << endl;

        delete[] a1; delete[] a2; delete[] a3;
    }
}