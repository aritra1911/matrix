#include "matrix.h"

#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

class Playground {
private:
    double *a, *augmented, *transposed, *adjoint, *inverse, *solution, det;
    size_t rows, cols;
    bool switch_a, switch_transposed, switch_adjoint, flag_singular,
         switch_inverse, switch_solution, switch_determinant;

    void set_switch_a();
    void set_switch_transposed();
    void set_switch_adjoint();
    void set_switch_inverse();
    void set_switch_solution();
    void set_switch_determinant();
    void augment_with_identity();

public:
    Playground();
    void reset_switches();
    bool get_switch_a();
    bool get_switch_transposed();
    bool get_switch_adjoint();
    bool get_switch_inverse();
    bool get_switch_solution();
    bool get_switch_determinant();
    void get_matrix(char);
    bool is_augmented_with_constants();
    bool is_augmented_with_identity();
    bool is_singular();
    void solve();
    void transpose();
    void calculate_determinant();
    void invert();
    void fetch_adjoint_from_inverse();
    void show_matrix(char);
    void show_determinant();
};

Playground::Playground() {
    reset_switches();
}

void Playground::reset_switches() {
    switch_a = false;
    flag_singular = false;
    switch_transposed = false;
    switch_adjoint = false;
    switch_inverse = false;
    switch_solution = false;
    switch_determinant = false;
}

void Playground::set_switch_a() { switch_a = true; }
void Playground::set_switch_transposed() { switch_transposed = true; }
void Playground::set_switch_adjoint() { switch_adjoint = true; }
void Playground::set_switch_inverse() { switch_inverse = true; }
void Playground::set_switch_solution() { switch_solution = true; }
void Playground::set_switch_determinant() { switch_determinant = true; }

bool Playground::get_switch_a() { return switch_a; }
bool Playground::get_switch_transposed() { return switch_transposed; }
bool Playground::get_switch_adjoint() { return switch_adjoint; }
bool Playground::get_switch_inverse() { return switch_inverse; }
bool Playground::get_switch_solution() { return switch_solution; }
bool Playground::get_switch_determinant() { return switch_determinant; }

void Playground::get_matrix(char arg) {
    if (switch_a) return;
    size_t n;

    do {
        cout << "Enter dimensions of matrix: ";
        cin >> n;
        if (n < 2) cout << "Least possible dimensions are 2.\n";
    } while (n < 2);
    rows = n;

    switch (arg) {
        case 'n':
            // simple square matrix
            a = new double[n * n];
            cols = n;

            for (size_t i=0; i<n; i++) {
                for (size_t j=0; j<n; j++) {
                    cout << "Enter Matrix element["<<i<<"]["<<j<<"]: ";
                    cin >> a[i * n + j];
                }
                cout << endl;
            }
            set_switch_a(); break;

        case 's':
            // augmented linear equation constants
            a = new double[n * (n+1)];
            cols = n+1;

            for (size_t i=0; i<n; i++) {
                for (size_t j=0; j<n+1; j++) {
                    cout << "Enter Matrix element["<<i<<"]["<<j<<"]: ";
                    cin >> a[i * (n+1) + j];
                }
                cout << endl;
            }
            set_switch_a(); break;

        default:
            cout << "Invalid argument '" << arg << "'supplied!\n";
            exit(0);
    }
}

bool Playground::is_augmented_with_constants() {
    return (cols == (rows+1))? true : false;
}

bool Playground::is_augmented_with_identity() {
    return (cols == 2*rows)? true : false;
}

bool Playground::is_singular() {
    return flag_singular;
}

void Playground::augment_with_identity() {
    augmented = new double[rows * 2*rows];
    Matrix().copy_matrix(augmented, a, rows, rows, 2*rows);

    // fill identity matrix
    for (size_t i=0; i<rows; i++)
        for (size_t j=rows; j<2*rows; j++)
            augmented[i * 2*rows + j] = (i==j%rows)? 1 : 0;
}

void Playground::solve() {
    if (switch_solution) return;
    double* temp = new double[rows * cols];
    Matrix().copy_matrix(temp, a, rows, cols);
    solution = new double[rows];
    Matrix().eliminate(temp, rows, cols, det, flag_singular);
    set_switch_determinant();
    if (is_singular()) {
        cout << "Matrix is singular.\n";
        return;
    }

    Matrix().back_substitute(temp, solution, rows, cols);
    set_switch_solution();
}

void Playground::transpose() {
    if (switch_transposed) return;
    transposed = new double[rows*cols];
    for (size_t i=0; i<cols; i++)
        for (size_t j=0; j<rows; j++)
            transposed[i * rows + j] = a[j * cols + i];
    set_switch_transposed();
}

void Playground::calculate_determinant() {
    if (switch_determinant) return;
    double *temp = new double[rows * cols];
    Matrix().copy_matrix(temp, a, rows, cols);
    Matrix().eliminate(temp, rows, cols, det, flag_singular);
    set_switch_determinant();
}

void Playground::invert() {
    if (switch_inverse) return;
    augment_with_identity();
    double* temp = new double[rows * 2*rows];
    Matrix().copy_matrix(temp, augmented, rows, 2*rows);
    Matrix().eliminate(temp, rows, 2*rows, det, flag_singular);
    set_switch_determinant();
    if (flag_singular) {
        cout << "Inverse matrix doesn't exist\n";
        return;
    }

    Matrix().reduce(temp, rows, 2*rows);
    inverse = new double[rows * rows];
    Matrix().filter_inverse(temp, inverse, rows, 2*rows);
    set_switch_inverse();
}

void Playground::fetch_adjoint_from_inverse() {
    if (switch_adjoint) return;
    size_t n = rows; // dimensions
    adjoint = new double[n * n];
    for (size_t i=0; i<n; i++)
        for (size_t j=0; j<n; j++)
            adjoint[i * n + j] = inverse[i * n + j] * det;
    set_switch_adjoint();
}

void Playground::show_matrix(char arg) {
    double* matrix;
    size_t r, c;

    switch(arg) {
        default:
        case 'a': matrix = a; r = rows; c = cols; break;
        case 't': matrix = transposed; r = cols; c = rows; break;
        case 'j': matrix = adjoint; r = rows; c = rows; break;
        case 'i': matrix = inverse; r = rows; c = rows; break;
        case 's': matrix = solution; r = 1; c = rows; break;
    }

    for (size_t i=0; i<r; ++i) {
        cout << "[";
        for (size_t j=0; j<c; ++j)
            cout << matrix[i * c + j] << " ";
        cout << "]\n";
    }

    cout << endl;
}

void Playground::show_determinant() {
    cout << "Determinant : " << det << endl;
}

int main() {
    Playground ground;
    bool avail_34 = false, avail_5 = false; // available options

    do {
        if (!ground.get_switch_a()) {
            cout << " 1 >> ENTER SQUARE MATRIX\n";
            cout << " 2 >> ENTER AUGMENTED MATRIX\n";
        } else {
            cout << " 1 >> CHANGE MATRIX\n";
            cout << " 2 >> TRANSPOSE\n";
            cout << " 3 >> FIND DETERMINANT\n";
            avail_34 = true;
            if (ground.is_augmented_with_constants())
                cout << " 4 >> FIND SOLUTION & DETERMINANT\n";
            else {
                cout << " 4 >> FIND DETERMINANT & INVERSE\n";
                cout << " 5 >> FIND DETERMINANT, INVERSE & ADJOINT\n";
                avail_5 = true;
            }
        }
        cout << "99 >> QUIT\n";

        int choice;
        cout << "Enter menu item index: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (!ground.get_switch_a())
                    ground.get_matrix('n');
                else
                    ground.reset_switches();
                break;

            case 2:
                if (!ground.get_switch_a())
                    ground.get_matrix('s');
                else {
                    ground.transpose();
                    ground.show_matrix('t');
                } break;

            case 3:
                if (!avail_34) exit(0);
                ground.calculate_determinant();
                ground.show_determinant();
                cout << endl;
                break;

            case 4:
                if (!avail_34) exit(0);
                if (ground.is_augmented_with_constants()) {
                    ground.solve();
                    ground.show_determinant();
                    if (ground.is_singular()) break;
                    cout << "\nSolution :\n";
                    ground.show_matrix('s');
                } else {
                    ground.invert();
                    ground.show_determinant();
                    if (ground.is_singular()) break;
                    cout << "\nInverse :\n";
                    ground.show_matrix('i');
                } break;

            case 5:
                if (!avail_5) exit(0);
                ground.invert();
                ground.show_determinant();
                if (ground.is_singular()) break;
                ground.fetch_adjoint_from_inverse();
                cout << "\nInverse :\n";
                ground.show_matrix('i');
                cout << "\nAdjoint :\n";
                ground.show_matrix('j');
                break;

            default : exit(0);
        } cout << endl;
    } while (true);

    return 0;
}
