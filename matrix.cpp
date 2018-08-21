#include "matrix.h"
#include <stdio.h>

#define MIN 5e-4

void Matrix::copy_matrix(double * const dest, const double * const src,
                         const size_t rows, const size_t cols, size_t col_size)
{
    if (col_size == -1) col_size = cols;
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            dest[i * col_size + j] = src[i * cols + j];
}

void Matrix::swap_rows(double * const a, size_t i, size_t pivot, size_t cols) {
    // Swap each column of the rows one by one.
    // Here, i and pivot rows are being swapped with each other.
    for (size_t j = 0; j < cols; j++) {
        double tmp = a[i * cols + j];
        a[i * cols + j] = a[pivot * cols + j];
        a[pivot * cols + j] = tmp;
    }
}

void Matrix::filter_inverse(const double * const a, double * const x,
                            const size_t rows, const size_t cols) {
    for (size_t i=0; i<rows; i++)
        for (size_t j=rows; j<cols; j++)
            x[i * rows + (j-rows)] = a[i * cols + j];
}

void Matrix::eliminate(double* a, const size_t rows, const size_t cols,
                       double &det, bool &singular) {
    // Applying Gaussian Elimination
    size_t dimensions = (rows < cols)? rows : cols;
    det = 1.0; // Assuming positive

    // Main loop going through all columns
    for(size_t k=0; k<dimensions; k++) {
        size_t pivot = k; // pivot represents the current row
                          // k     represents the current column

        // Step #1 : Find maximum element for each column
        for (size_t i = k + 1; i < rows; i++)
            if (fabs(a[i * cols + k]) > fabs(a[pivot * cols + k]))
                pivot = i;

        // Check to make sure matrix is good!
        if (fabs(a[pivot * cols + k]) < MIN) {
            singular = true;
            det = 0;
            return;
        }

        // Step #2 : Swap row with highest value for that column to the top
        if (k != pivot) {
            swap_rows(a, k, pivot, cols);
            det = -det; // Invert sign for each rows swap
        }

        // Loop for all remaining rows
        for (size_t i=k+1; i<rows; i++) {

            // Step #3 : Finding fraction
            double scale = a[i * cols + k] / a[k * cols + k];

            // Loop through columns for that row
            for (size_t j = k + 1; j < cols; j++)

                // Step #4 : Re-evaluate each element
                a[i * cols + j] -= a[k * cols + j] * scale;

            // Step #5 : Set lower elements to 0
            a[i * cols + k] = 0;
        }
    }

    // calculate determinant by taking product of pivot of each row
    for(size_t i=0; i<rows; i++)
        for(size_t j=0; j<cols; j++)
            if(a[i *cols+ j] != 0) {
                det *= a[i *cols+ j];
                break;
            }

}

void Matrix::back_substitute(const double * const a, double * const x,
                     const size_t rows, const size_t cols) {
    // Solve for solution vector x by back substitution
    // *a expected an identity or upper triangular matrix

    for (int i = rows - 1; i >= 0; --i) {
        double sum = 0.0;

        for (size_t j = cols - 2; j > i; --j)
            sum += x[j] * a[i * cols + j];

        x[i] = (a[i * cols + cols - 1] - sum) / a[i * cols + i];
    }
}

void Matrix::reduce(double *a, const size_t rows, const size_t cols) {
    // Applying Gauss-Jordan Elimination
    size_t dimensions = (rows < cols)? rows : cols;

    // After this, we know what row to start on (r-1)
    // to go back through the matrix
    size_t row = 0;
    for (int col=0; col<dimensions; col++) {
        if (a[row *cols+ col] != 0) {

            // divide row by pivot and leaving pivot as 1
            for (int i=cols-1; i>=col; i--)
                a[row *cols+ i] /= a[row *cols+ col];

            // subtract value from above row and set values above pivot to 0
            for (size_t i=0; i<row; i++)
                for (size_t j=cols-1; j>=col; j--)
                    a[i *cols+ j] -= a[i *cols+ col] * a[row *cols+ j];

            row++;
        }
    }
}
