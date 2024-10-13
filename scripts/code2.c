/* Author: Aidan P
 * Lab: Lab5
 * Purpose: Create matrix functions using 2D arrays that can be implemented into larger programs
 * Created: 10/12/24
 * Last Edited: 10/13/24
 */

#include <stdio.h>

#define SIZE 5

/* Most of the functions are implemented using this struct.
   Contains the use of SIZE to define the max size of each matrix.
   row and col size are defined for error checking with various inputs. */
struct Matrix
{
	int data[SIZE][SIZE];
	int rowSize;
	int colSize;
};


// Function prototypes
struct Matrix addMatrices(struct Matrix m1, struct Matrix m2);
struct Matrix multiplyMatrices(struct Matrix m1, struct Matrix m2);
struct Matrix transposeMatrix(struct Matrix m);
void printMatrix(struct Matrix m);
struct Matrix createMatrix(int matrixArray[SIZE][SIZE], int rowSize, int colSize);

int main()
{
	// Define the 2D arrays that make up the matrices
	int m1[SIZE][SIZE] ={
	{1, 2, 3, 4, 5},
	{6, 7, 8, 9, 10},
	{11, 12, 13, 14, 15},
	{16, 17, 18, 19, 20},
	{21, 22, 23, 24, 25}
	};
	int m2[SIZE][SIZE] = {
	{25, 24, 23, 22, 21},
	{20, 19, 18, 17, 16},
	{15, 14, 13, 12, 11},
	{10, 9, 8, 7, 8},
	{5, 4, 3, 2, 1}
	};

	// Create Matrix structures to use (I used these to bundle all error checking information in an easily accessible object and clean up the code)
	struct Matrix matrix1 = createMatrix(m1, SIZE, SIZE);
	struct Matrix matrix2 = createMatrix(m2, SIZE, SIZE);
	printf("Matrix 1\n");
	printMatrix(matrix1);
	printf("\nMatrix 2\n");
	printMatrix(matrix2);

	// Add matrices and print
	printf("\nAdded Matrix Result\n");
	printMatrix(addMatrices(matrix1, matrix2));

	// Multiply matrices and print
	printf("\nMultiplied Matrix Result\n");
	printMatrix(multiplyMatrices(matrix1, matrix2));
	
	// Transpose a matrix and print
	printf("\nTranspose of Matrix Result\n");
	printMatrix(transposeMatrix(matrix2));
}

struct Matrix addMatrices(struct Matrix m1, struct Matrix m2)
{
	int outputMat[SIZE][SIZE];
	// Checks if input bounds for matrices are valid for adding
	if (m1.rowSize != m2.rowSize || m1.colSize != m2.colSize)
	{
		printf("Invalid dimensions: Unable to add\n");
		return createMatrix(outputMat, 0, 0);
	}
	else
	{
		// Run code if matrices follow matrix addition rules
		for (int row = 0; row < m1.rowSize; row++)
		{
			for (int col = 0; col < m1.colSize; col++)
			{
				// Add the two values of original matrices together and save to create an output matrix struct 
				outputMat[row][col] = (m1.data[row][col] + m2.data[row][col]);
			}
		}
		return createMatrix(outputMat, m1.rowSize, m1.colSize);
	}
		
}

void printMatrix(struct Matrix m)
{
	for (int row = 0; row < m.rowSize; row++)
	{
		for (int col = 0; col < m.colSize; col++)
		{
			printf("%5d ", m.data[row][col]);
		}
		printf("\n");
	}
}

struct Matrix multiplyMatrices(struct Matrix m1, struct Matrix m2)
{
	int outputMat[SIZE][SIZE];
	// Check if matrices follow multiplication rules
	if (m1.colSize != m2.rowSize)
	{
		printf("Invalid dimensions: Unable to multiply\n");
		return createMatrix(outputMat, 0, 0);
	}
	else
	{
		for (int row = 0; row < m1.rowSize; row++)
		{
			for (int col = 0; col < m2.colSize; col++)
			{
				int sum = 0;
				for (int product = 0; product < m2.rowSize; product++)
				{
					// Find the sum of the cross products
					sum += (m1.data[row][product] * m2.data[product][col]);
				}
				// Assign each sum to the respective position within the output
				outputMat[row][col] = sum;
			}
		}
		return createMatrix(outputMat, m1.rowSize, m2.colSize);
	}
}

struct Matrix transposeMatrix(struct Matrix m)
{
	int outputMat[SIZE][SIZE];	
	for (int row = 0; row < m.rowSize; row++)
	{
		for (int col = 0; col < m.colSize; col++)
		{
			// Inverse the matrix by assigning the value of the original to the inverse position of the new matrix
			outputMat[col][row] = m.data[row][col];
		}
	}
	return createMatrix(outputMat, m.colSize, m.rowSize);
}

struct Matrix createMatrix(int matrixArray[SIZE][SIZE], int rowSize, int colSize)
{
	// Initialize a new matrix to assign variables to
	struct Matrix newMatrix;

	//Check to make sure the array input is not empty/invalid
	if (matrixArray != NULL)
	{
		for (int row = 0; row < SIZE; row++)
		{
			for (int col = 0; col < SIZE; col++)
			{
				newMatrix.data[row][col] = matrixArray[row][col];
			}
		}
	}
	// Add row and column bounds to assist with error checking, running operations in  other functions, and clean up inputs
	// That was the main reason I decided to use structs encasing the matrix information
	newMatrix.rowSize = rowSize;
	newMatrix.colSize = colSize;
	return newMatrix;
}
