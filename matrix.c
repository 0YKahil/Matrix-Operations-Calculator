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
 * Reduces the given fraction f to its lowest terms
 */
Fraction reduce(Fraction f);

/**
 * Adds fraction a to fraction b and returns the reduced result
 */
Fraction addFractions(Fraction a, Fraction b);

/**
 * Subtracts fraction b from fraction a and returns the reduced result
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

    // Handle all possible special cases of fractions for better output
    if (f.den == 0) {
        printf("Undefined (division by zero)");
    } else if (f.num == f.den) { // x/x = 1
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
    // TODO: Implement matrix parsing logic
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

        // ensure the pivot element is not zero
        if ((*(matrix + curr) + curr)->num == 0) {
            // Skip 0 elements since they are already reduced
            curr++;
            continue;
        }

        for (int r = 0; r < rows; r++) {
            // calculate divisor and multiplier for this step
            d = *(*(matrix + curr) + curr);
            if (d.num == 0 || d.den == 0) {
                // Skip 0 devision
                continue;
            }

            m = divFractions(*(*(matrix + r) + curr), *(*(matrix + curr) + curr));

            // iterate through columns 
            for (int c = 0; c < cols; c++) {
                if (r == curr) {
                    // divide pivot by divisor to equal 1
                    *(*(matrix + r) + c) = divFractions(*(*(matrix + r) + c), d);
                } else {
                    // subtract multiple of pivot to make element equal 0
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
 * Takes 2 matrix pointers and adds the matrices A and B, storing the new matrix in A
 */
void addMatrices(int rows, int cols, Fraction **matrixA, Fraction **matrixB) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrixA[i][j] = addFractions(matrixA[i][j], matrixB[i][j]);
        }
    }
}

int main() {
    /**
     * Small demonstration of the functions and possibilities for now,
     * since the application is not developed with user input and UI
     */

    int rows = 3, cols = 3; // statically defined rows and cols for now

    // allocating memory for the matrices
    Fraction **A = (Fraction **)malloc(rows * sizeof(Fraction *));
    Fraction **B = (Fraction **)malloc(rows * sizeof(Fraction *));
    for (int i = 0; i < rows; i++) {
        A[i] = (Fraction *)malloc(cols * sizeof(Fraction));
        B[i] = (Fraction *)malloc(cols * sizeof(Fraction));
    }

    // Initialize the matrix with predefined values (to be replaced by user input)
    int initA[3][3][2] = {
        {{1, 2}, {2, 3}, {3, 4}},
        {{4, 5}, {5, 6}, {6, 7}},
        {{7, 8}, {8, 9}, {9, 10}}
    };
    int initB[3][3][2] = {
        {{1, 2}, {1, 3}, {1, 4}},
        {{1, 5}, {1, 6}, {1, 7}},
        {{1, 8}, {1, 9}, {1, 10}}
    };
    // initialize dynamic array with the given values from initA and initB
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A[i][j].num = initA[i][j][0];
            A[i][j].den = initA[i][j][1];
            B[i][j].num = initB[i][j][0];
            B[i][j].den = initB[i][j][1];
        }
    }

    printf("Adding 2 Matrices: \n");
    printf("Matrix A: \n");
    printMatrix(rows, cols, A);
    printf("Matrix B: \n");
    printMatrix(rows, cols, B);
    // add A and B and store it in A
    addMatrices(rows, cols, A, B);

    printf("\n\nRESULT: \n");

    // print the result matrix (which is now in A)
    printMatrix(rows, cols, A);

    rowReduce(rows, cols, A);

    // Row Reduce
    printf("\n\nReduced RESULT: \n");
    printMatrix(rows, cols, A);

    // free the memory used by the allocated rows
    for (int i = 0; i < rows; i++) {
        free(A[i]);
        free(B[i]);
    }

    // free the Matrices
    free(A);
    free(B);

    return 0;
}
