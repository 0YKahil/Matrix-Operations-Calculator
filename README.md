# Matrix Calculator

## Overview

The Matrix Calculator is a C-based application designed to perform various matrix operations using 2D dynamic arrays and pointers. This includes row reduction to Reduced Row Echelon Form (RREF), matrix addition, and more. Instead of using decimals, the project utilizes fractions created using structs to keep results clear and user friendly.

## Features

- **Matrix Addition**: Easily add two matrices and store the result.
- **Row Reduction**: Transform a matrix into its Reduced Row Echelon Form (RREF).
- **Fraction Arithmetic**: Perform operations on fractions for accuracy.
- **Dynamic Memory Allocation**: Handle matrices of different sizes using dynamic arrays.

## Fraction Structure

The `Fraction` struct represents fractions, ensuring clarity and precision in calculations.
- It consists of a numerator and denominator.
- Functions include: adding, subtracting, multiplying, dividing, finding gcd, and printing the fractions.

## Matrix Operations
**Functions implemented in the calculator include:**
- Printing Matrices in the form: <br>
   ```a00 a01 a02``` <br>
   ```a10 a11 a12``` <br>
   ```a20 a21 a22``` <br>

- Row Reducing matrices to RREF while showing each step of the calculations.
- Adding two matrices.
- Multiplying matrices **SOON**
- Parsing matrices from user text **SOON**
- Calculating determinants **SOON**
- Computing transposes **SOON**

## How to Use
**Currently the application has not been built for use using an executable and must be compiled on a machine.
### Prerequisites
- A C compiler (GCC on linux was used in development).

### Compiling and Running the Example Given in Main
- Type ```gcc -o matrix_calculator matrix.c``` into a terminal or shell to compile the c program using gcc.
- Run the executable using ```./matrix_calculator``` or how you usually would run one on your machine.

### Sample result
**Addition**  
![image](https://github.com/user-attachments/assets/af813358-b148-4de8-a296-af08930439d4)

<br>

**Row Reducing to RREF**  
![image](https://github.com/user-attachments/assets/03b0b8c5-bcf2-4320-83bf-51e758af10a7)


