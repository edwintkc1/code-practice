#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void flip(bool matrix[][10], int c, int row) {
    for (int i = 0; i < row; i++) {
        matrix[i][c] = !matrix[i][c];
    }
}

int computeSum(bool matrix[][10], int row, int col) {
    int totalSum = 0;
    for (int r = 0; r < row; r++) {
        int rowSum = 0;
        for (int c = 0; c < col; c++) {
            rowSum += matrix[r][c];
        }
        if (rowSum * 2 <= col) {
            totalSum += col - rowSum;
        }
        else {
            totalSum += rowSum;
        }
    }
    return totalSum;
}

int test(bool matrix[][10], int index, int col, int row) {
    int temp = index;
    for (int i = 0; i < col; i++) {
        if (index % 2 == 1) {
            flip(matrix, i, row);
        }
        index /= 2;
    }
    int sum = computeSum(matrix, row, col);
    for (int i = 0; i < col; i++) {
        if (temp % 2 == 1) {
            flip(matrix, i, row);
        }
        temp /= 2;
    }
    return sum;
}

int main() {
    int row, col;
    while (cin >> row >> col) {
        //get the input
        bool matrix[100][10];
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                char x;
                cin >> x;
                matrix[r][c] = x - 0x30;
            }
        }
        //test and try
        int max = 0;
        for (int i = 0; i < pow(2, col); i++) {
            int res = test(matrix, i, col, row);
            if (res > max) {
                max = res;
            }
            if (max == row * col) {
                break;
            }
        }
        //give the result
        cout << max << endl;
    }
    return 0;
}