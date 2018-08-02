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

    void back_substitute(const double * const a, double * const x,
                           const size_t rows, const size_t cols) {
        // Solve for solution vector x by back substitution
        // *a must be in Row Echelon Form

        for (size_t i = rows - 1; i >= 0; i--) {
            double sum = 0.0;

            for (size_t j = cols - 2; j > i; j--)
                sum += x[j] * a[i *cols+ j];

            x[i] = (a[i *cols+ cols-1] - sum) / a[i *cols+ i];
        }
    }

    void reduce(double *a, const size_t rows, const size_t cols) {
        // Applying Gauss-Jordan Elimination
        // *a must be in Row Echelon Form

        // After this, we know what row to start on (r-1)
        // to go back through the matrix
        pivot = 1
        for(size_t k=1; k<cols; k++) {
            if (a[pivot * cols + k] != 0) {

                // divide row by pivot and leaving pivot as 1
                for(size_t i=cols-1; i>=k; i--)
                    a[pivot * cols + i] /= A[pivot * cols + k]

                // subtract value from above row and set values above pivot to 0
                for(size_t i=1; i<pivot; i++)
                    for(size_t j=cols-1; j>=k; j--)
                        a[i *cols+ j] -= a[i *cols+ k] * a[pivot *cols+ j]

                pivot++
            }
        }
    }

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
    Matrix().back_substitute((double *)a, x, 3, 4);

    cout << "(" << x[0] << ", " << x[1] << ", " << x[2] << ")" << endl;

    return 0;
}
