#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Maximum will be capped at 7 as going higher than that would 
 * exponentially increase the time needed to calculate
 */
#define MAX_ROWS 7
#define MAX_COLS 7

// parse string matrix

/*
 * Takes a m x n matrix inputted by the user in the form {{a11, a12, a13}, {a21, a22, a23}, {a31, a32, a33}}
 * representing the matrix:  a11 a12 a13
 *                           a21 a22 a23
 *                           a31 a32 a33
 */

void parse_matrix() {}

// Row Reduction RREF

/*
 *  Takes an row x columns and prints it in the form:   a11 a12 a13
 *                                                      a21 a22 a23
 *                                                      a31 a32 a33
 */
void printmatrix(int rows, int cols, float matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%7.4f  ", matrix[i][j]);
        }
        printf("\n"); // new line after each row
    }
    printf("\n");
}

int main() {
    float A[3][4] = {{5, -6, -7,   7},
                     {3, -2,  5, -17},
                     {2,  4, -3,  29}}; //answer should be {2, 4, -3}

    printmatrix(3 , 4, A);
}