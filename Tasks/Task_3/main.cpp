#include <iostream>
#include <windows.h>
#include <cmath>
#include <ctime>

using namespace std;

void setColor(int text, int background = 0) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((background << 4) | text));
}

int** generateMatrix(int n) {
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 71 - 35;
        }
    }
    return matrix;
}

void printCell(int num) {
    if (num >= 0 && num < 10)
        cout << "  ";
    else if ((num > -10 && num < 0) || (num >= 10))
        cout << " ";
    else if (num <= -10)
        cout << "";
    cout << num << "  ";
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printCell(matrix[i][j]);
        }
        cout << endl;
    }
}

int sumSector8(int** matrix, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= j) {
                if (matrix[i][j]!=0 && matrix[i][j] % 3 == 0) {
                    sum += matrix[i][j];
                    setColor(14, 1);
                }
                else 
                    setColor(11, 0);
            }
            printCell(matrix[i][j]);
            setColor(7, 0);
        }
        cout << endl;
    }
    return sum;
}


void findMinNum(int** matrix, int n, int& minNum, int& minI, int& minJ) {
    minNum = matrix[0][0];
    minI = 0; minJ = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (abs(matrix[i][j]) < abs(minNum)) {
                minNum = matrix[i][j];
                minI = i;
                minJ = j;
            }
        }
    }
}

int changeSector2(int** matrix, int n) {
    int count = 0;
    int minNum, minI, minJ;
    findMinNum(matrix, n, minNum, minI, minJ);
    cout << "\n--- Змінений сектор *2 (мінімальне число ["<<minNum<<"]) ---" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= j && i + j <= n - 1) {
                matrix[i][j] = minNum;
                count++;
            }

            if (i == minI && j == minJ) 
                setColor(0, 14);
            else if (i >= j && i + j <= n - 1)
                setColor(14, 0);

            printCell(matrix[i][j]);
            setColor(7, 0);
        }
        cout << endl;
    }
	return count;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Ukrainian");

    srand(time(0));

    int n;
    cout << "Введіть розмір квадратної матриці (n): "; 
    cin >> n;

    int** matrix = generateMatrix(n);

    cout << "\n--- Початкова матриця ---" << endl;
    printMatrix(matrix, n);

    cout << "\n--- Сектор *8 (виділені числа кратні 3) ---" << endl;
    int sum8 = sumSector8(matrix, n);
    cout << "\nСума кратних 3 у секторі *8: " << sum8 << endl;

    int count = changeSector2(matrix, n);
    cout << "\nКількість елементів у секторі *2: " << count << endl;

    for (int i = 0; i < n; i++) 
        delete[] matrix[i];
    delete[] matrix;
}