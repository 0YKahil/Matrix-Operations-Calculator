/**
 * @file matrix.c
 * @author 0YKahil
 * 
 * Implementation of a matrix calculator using 2D dynamic arrays and pointers 
 * to allow row reduction, matrix arithmetic, calculations of determinants, and transpose computation
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Maximum will be capped at 7 as going higher than that would 
 * exponentially increase the time needed to calculate
 */
#define MAX_ROWS 7
#define MAX_COLS 7

/**
 * Fraction struct will be used in place of decimals to allow clarity in the final results.
 */
typedef struct {
    int num;
    int den;
} Fraction;

/**
 * Reduced the given fraction f to its lowest
 */
Fraction reduce(Fraction f);

/**
 * Adds fraction a to fraction b and returns the reduced result
 */
Fraction addFractions(Fraction a, Fraction b);

/**
 * subtracts fraction b from fraction a and returns the reduced result
 */
Fraction subFractions(Fraction a, Fraction b);

/**
 * Multiplies the fraction a with b and returns the reduced result
 */
Fraction mulFractions(Fraction a, Fraction b);

/**
 * Divides the fraction a by the fraction b and returns the reduced result
 */
Fraction divFractions(Fraction a, Fraction b);

/**
 * Prints the given fraction f or a whole number if applicable
 */
void printFraction(Fraction f);

/**
 * Calculates the greatest common divisor of the given two integers using the 
 * Euclidean algorithm (https://en.wikipedia.org/wiki/Euclidean_algorithm)
 */
int gcd(int a, int b);

Fraction reduce(Fraction f) {
    int g = gcd(f.num, f.den);
    f.num /= g;
    f.den /= g;

    // ensure positive denominator
    if (f.den < 0) { 
        f.num = -f.num;
        f.den = -f.den;
    }
    return f;
}

Fraction addFractions(Fraction a, Fraction b) {
    Fraction result; // new fraction to represent the results
    result.num = a.num * b.den + b.num * a.den;
    result.den = a.den * b.den;
    return reduce(result);
}

Fraction subFractions(Fraction a, Fraction b) {
    Fraction result;
    result.num = a.num * b.den - b.num * a.den;
    result.den = a.den * b.den;
    return reduce(result);
}

Fraction mulFractions(Fraction a, Fraction b) {
    Fraction result;
    // cross multiply and reduce
    result.num = a.num * b.num;
    result.den = a.den * b.den;
    return reduce(result);
}

Fraction divFractions(Fraction a, Fraction b) {
    Fraction result;
    // multiply a by the reciprocal of b
    result.num = a.num * b.den;
    result.den = a.den * b.num;
    return reduce(result);
}

void printFraction(Fraction f) {
    // Reduce the fraction first
    f = reduce(f);

    if (f.num == f.den) { // x/x = 1
        printf("1");
    } else if (f.num == 0) { // 0/x = 0
        printf("0");
    } else if (f.den == 1) { // x/1 = x
        printf("%d", f.num);
    } else if (f.num % f.den == 0) { // x % y = 0 -> whole number 'z'
        printf("%d", f.num / f.den);
    } else { // print fraction
        printf("%d/%d", f.num, f.den);
    }
}

int gcd(int a, int b) {
    // Euclidean Algorithm for GCD
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}

/*
 * Takes a m x n matrix inputted by the user in the form {{a11, a12, a13}, {a21, a22, a23}, {a31, a32, a33}}
 * representing the matrix:  a11 a12 a13
 *                           a21 a22 a23
 *                           a31 a32 a33
 */

void parse_matrix() {
    // Todo
}



/*
 * Takes a row x columns 2D array pointer (matrix)
 * and prints it in the form:   a11 a12 a13
 *                              a21 a22 a23
 *                              a31 a32 a33
 * 
 */
void printMatrix(int rows, int cols, Fraction **matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printFraction(*(*(matrix + i) + j));
            printf(" ");
        }
        printf("\n"); // new line after each row
    }
    printf("\n");
}
/*
 * Takes a row x columns fraction matrix and row reduces it to Reduced Row Echelon Form
 */
void rowReduce(int rows, int cols, Fraction **matrix) {
    int curr = 0;

    while (curr < rows) {
        Fraction d, m;
        
        for (int r = 0; r < rows; r++) {
            // calculate divisor and multiplier for this step
            d = *(*(matrix + curr) + curr);
            m = divFractions(*(*(matrix + r) + curr), *(*(matrix + curr) + curr));

            // iterate through columns 
            for (int c = 0; c < cols; c++) {
                if (r == curr) {
                    // divide pivot by divisor to = 1
                    *(*(matrix + r) + c) = divFractions(*(*(matrix + r) + c), d);
                } else {
                    // subtract multiple of pivot to make element = 0
                    *(*(matrix + r) + c) = subFractions(*(*(matrix + r) + c), 
                    mulFractions(*(*(matrix + curr) + c), m));
                }
            }
        }

        curr++;
        printf("Step %d\n", curr);
        printMatrix(rows, cols, matrix);
    }
}

/**
 * Takes 2 matrix pointers and adds the matrices A and B
 */
void addMatrices(int rows, int cols, Fraction **matrixA, Fraction **matrixB, Fraction **result) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrixA[i][j] = addFractions(matrixA[i][j], matrixB[i][j]);
        }
    }
}

int main() {
    int rows = 3, cols = 4; // Statically defined rows and cols

    // Allocate memory for the matrix
    Fraction **A = (Fraction **)malloc(rows * sizeof(Fraction *));
    for (int i = 0; i < rows; i++) {
        A[i] = (Fraction *)malloc(cols * sizeof(Fraction));
    }

    // Initialize the matrix
    int init[3][4][2] = {
        {{5, 1}, {-6, 1}, {-7, 1}, {7, 1}},
        {{3, 1}, {-2, 1}, {5, 1}, {-17, 1}},
        {{2, 1}, {4, 1}, {-3, 1}, {29, 1}}
    };

    // Initialize dynamic array with the given values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A[i][j].num = init[i][j][0];
            A[i][j].den = init[i][j][1];
        }
    }

    printMatrix(rows, cols, A);
    rowReduce(rows, cols, A);

    // Free the memory used by the allocated rows
    for (int i = 0; i < rows; i++) {
        free(A[i]);
    }

    // Free the Matrix
    free(A);

    return 0;
}