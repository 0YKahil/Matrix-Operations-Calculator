#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Maximum will be capped at 7 as going higher than that would 
 * exponentially increase the time needed to calculate
 */
#define MAX_ROWS 7
#define MAX_COLS 7


/*
 * Takes a m x n matrix inputted by the user in the form {{a11, a12, a13}, {a21, a22, a23}, {a31, a32, a33}}
 * representing the matrix:  a11 a12 a13
 *                           a21 a22 a23
 *                           a31 a32 a33
 */

void parse_matrix() {}



/*
 * Takes a row x columns matrix 
 * and prints it in the form:   a11 a12 a13
 *                              a21 a22 a23
 *                              a31 a32 a33
 * 
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

/*
 * Takes a row x columns matrix and row reduces it to Reduced Row Echelon Form
 */
void rowReduce(int rows, int cols, float matrix[rows][cols]) {
    const int nrows = rows;
    const int ncols = cols;
    int lead = 0;

    while (lead < nrows) {
        float d, m;

        for (int r = 0; r < nrows; r++) {
            // calculate divisor d and multiplier m
            d = matrix[lead][lead];
            m = matrix[r][lead] / matrix[lead][lead];

            // iterate through columns 
            for (int c = 0; c < ncols; c++) {
                if (r == lead) {
                    // divide pivot by divisor to = 1
                    matrix[r][c] /= d; 
                } else {
                    // subtract multiple of pivot to make element = 0
                    matrix[r][c] -= matrix[lead][c] * m; 
                }
            }
        }

        lead++;
        printmatrix(rows, cols, matrix);
    }
}

void add() {
    
}

int main() {
    float A[3][4] = {{5, -6, -7,   7},
                     {3, -2,  5, -17},
                     {2,  4, -3,  29}}; //answer should be {2, 4, -3}

    printmatrix(3, 4, A);
    rowReduce(3, 4, A);

}