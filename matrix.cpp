#include <iostream>
#include <math.h>
using namespace std;

class Matrix {
public:

    // Tip: Read a[i * cols + j] as a[i][j] just for ease of understanding

    void swap_rows(double * const a, size_t i, size_t pivot, size_t cols) {
        // Swap each column of the rows one by one.
        // Here, i and pivot rows are being swapped with each other.
        for (size_t j = 0; j < cols; j++) {
            double tmp = a[i * cols + j];
            a[i * cols + j] = a[pivot * cols + j];
            a[pivot * cols + j] = tmp;
        }
    }

    void eliminate(double *a, const size_t rows, const size_t cols) {
        // Applying Gaussian Elimination
        size_t dimensions = (rows < cols)? rows : cols;

        // Main loop going through all columns
        for(size_t k=0; k<dimensions; k++) {
            size_t pivot = k; // pivot represents the current row
                              // k     represents the current column

            // Step #1 : Find maximum element for each column
            for (size_t i = k + 1; i < rows; i++) {
                if (fabs(a[i * cols + k]) > fabs(a[pivot * cols + k])) {
                    pivot = i;
                }
            }

            // Check to make sure matrix is good!
            if (a[pivot * cols + k] == 0) {
                printf("The matrix is singular.\n");
                // there still can be a solution, do something!
                // exit(0);
            }

            // Step #2 : Swap row with highest value for that column to the top
            if (k != pivot)
                swap_rows(a, k, pivot, cols);

            // Loop for all remaining rows
            for(size_t i=k+1; i<rows; i++) {

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
    }

    void back_substitution(const double * const a, double * const x,
                           const size_t rows, const size_t cols) {
        // x is the solution Vector

        for (int i = rows - 1; i >= 0; i--) {
            double sum = 0.0;

            for (size_t j = cols - 2; j > i; j--) {
                sum += x[j] * a[i * cols + j];
            }

            x[i] = (a[i * cols + cols - 1] - sum) / a[i * cols + i];
        }
    }

    // TODO: Covert this Julia into C.
    //
    void reduce(double *a, const size_t rows, const size_t cols) {
    //
    //     # After this, we know what row to start on (r-1)
    //     # to go back through the matrix
    //     row = 1
    //     for col = 1:cols-1
    //         if (A[row, col] != 0)
    //
    //             # divide row by pivot and leaving pivot as 1
    //             for i = cols:-1:col
    //                 A[row,i] /= A[row,col]
    //             end
    //
    //             # subtract value from above row and set values above pivot to 0
    //             for i = 1:row-1
    //                 for j = cols:-1:col
    //                     A[i,j] -= A[i,col]*A[row,j]
    //                 end
    //             end
    //             row += 1
    //         end
    //     end
    }

    void invert() { return; }

    double determinant() { return 0.0; }

    void adjoint() { return; }

    void adjugate() { adjoint(); }
};

int main() {
    double a[3][4] = {{3.0, 2.0, -4.0, 3.0},
                      {2.0, 3.0, 3.0, 15.0},
                      {5.0, -3.0, 1.0, 14.0}};

    Matrix().eliminate((double *)a, 3, 4);

    for (size_t i = 0; i < 3; ++i) {
        cout << "[";
        for (size_t j = 0; j < 4; ++j)
            cout << a[i][j] << " ";
        cout << "]\n";
    }

    cout << endl;

    double x[3] = {0, 0, 0};
    Matrix().back_substitution((double *)a, x, 3, 4);

    cout << "(" << x[0] << ", " << x[1] << ", " << x[2] << ")" << endl;

    return 0;
}
