//
// Created by radiationx on 10.05.17.
//

#ifndef PROG_LAB_4_2_MATRIXRANK_H
#define PROG_LAB_4_2_MATRIXRANK_H

#include "iostream"

using namespace std;

class MatrixRank {
public:
    void PrintMatr(int **mas, int m) {
        int i, j;
        for (i = 0; i < m; i++) {
            for (j = 0; j < m; j++)
                cout << mas[i][j] << " ";
            cout << endl;
        }
    }

// Получение матрицы без i-й строки и j-го столбца
    void GetMatr(int **mas, int **p, int i, int j, int m) {
        int ki, kj, di, dj;
        di = 0;
        for (ki = 0; ki < m - 1; ki++) { // проверка индекса строки
            if (ki == i) di = 1;
            dj = 0;
            for (kj = 0; kj < m - 1; kj++) { // проверка индекса столбца
                if (kj == j) dj = 1;
                p[ki][kj] = mas[ki + di][kj + dj];
            }
        }
    }

// Рекурсивное вычисление определителя
    int Determinant(int **mas, int m) {
        int i, j, d, k, n;
        int **p;
        p = new int *[m];
        for (i = 0; i < m; i++)
            p[i] = new int[m];
        j = 0;
        d = 0;
        k = 1; //(-1) в степени i
        n = m - 1;
        if (m < 1) cout << "Определитель вычислить невозможно!";
        if (m == 1) {
            d = mas[0][0];
            return (d);
        }
        if (m == 2) {
            d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
            return (d);
        }
        if (m > 2) {
            for (i = 0; i < m; i++) {
                GetMatr(mas, p, i, 0, m);
                cout << mas[i][j] << endl;
                PrintMatr(p, n);
                d = d + k * mas[i][0] * Determinant(p, n);
                k = -k;
            }
        }
        return (d);
    }

    int suka[16] = {2, 3, 5, 6, 7, 1, 0, 6, 7, 8, 0, 1, 2, 3, 4, 6};

// Основная функция
    int main() {
        int m, i, j, d;
        int **mas;
        cout << "Введите размерность квадратной матрицы: ";
        cin >> m;
        mas = new int *[m];
        for (i = 0; i < m; i++) {
            mas[i] = new int[m];
            for (j = 0; j < m; j++) {

                //cin >> mas[i][j];
                mas[i][j] = suka[m * i + j];
                cout << "mas[" << i << "][" << j << "]= " << mas[i][j] << endl;
            }
        }
        PrintMatr(mas, m);
        d = Determinant(mas, m);
        cout << "Определитель матрицы равен " << d;
        return 0;
    }
};


#endif //PROG_LAB_4_2_MATRIXRANK_H