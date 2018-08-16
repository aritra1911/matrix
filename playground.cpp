#include "matrix.h"

#include <iostream>
#include <cstdlib>
using namespace std;

class Playground {
private:
    double *a, *transposed, *adjoint, *inverse, *solution, det;
    size_t rows, cols;
    bool switch_a, switch_transposed, switch_adjoint,
         switch_inverse, switch_solution, switch_determinant;

public:
    Playground();
    void reset_switches();
    void set_switch_a();
    void set_switch_transposed();
    void set_switch_adjoint();
    void set_switch_inverse();
    void set_switch_solution();
    void set_switch_determinant();
    bool get_switch_a();
    bool get_switch_transposed();
    bool get_switch_adjoint();
    bool get_switch_inverse();
    bool get_switch_solution();
    bool get_switch_determinant();
    void get_matrix(char);
    char check_augmented();
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
    switch_transposed = false;
    switch_adjoint = false;
    switch_inverse = false;
    switch_solution = false;
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
    size_t n;
    cout << "Enter dimensions of matrix: ";
    cin >> n; rows = n;

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
            } break;

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
            } break;

        case 'a':
        case 'i':
            // augmented with identity
            a = new double[n * 2*n];
            cols = 2*n;

            for (size_t i=0; i<n; i++) {
                for (size_t j=0; j<n; j++) {
                    cout << "Enter Matrix element["<<i<<"]["<<j<<"]: ";
                    cin >> a[i * cols + j];
                }
                cout << endl;
            }

            // fill identity matrix
            for (size_t i=0; i<rows; i++)
                for (size_t j=rows; j<cols; j++)
                    a[i * cols + j] = (i==j%rows)? 1 : 0;
            break;

        default:
            cout << "Invalid argument '" << arg << "'supplied!\n";
            exit(0);
    }
}

char Playground::check_augmented() {
    if (cols > rows) {
        if (cols > (rows + 1)) return 'i';
        return 's';
    }
    return '\0';
}

void Playground::solve() {
    double *temp = new double[rows * cols];
    Matrix().copy_matrix(temp, a, rows, cols);
    solution = new double[rows];
    Matrix().eliminate(temp, rows, cols, det);
    Matrix().back_substitute(temp, solution, rows, cols);
    set_switch_determinant();
    set_switch_solution();
}

void Playground::transpose() {
    transposed = new double[rows*cols];
    for (size_t i=0; i<cols; i++)
        for (size_t j=0; j<rows; j++)
            transposed[i * rows + j] = a[j * cols + i];
    set_switch_transposed();
}

void Playground::calculate_determinant() {
    double *temp = new double[rows * cols];
    Matrix().copy_matrix(temp, a, rows, cols);
    Matrix().eliminate(temp, rows, cols, det);
    set_switch_determinant();
}

void Playground::invert() {
    double *temp = new double[rows * cols];
    Matrix().copy_matrix(temp, a, rows, cols);
    Matrix().eliminate(temp, rows, cols, det);
    Matrix().reduce(temp, rows, cols);
    inverse = new double[rows*rows];
    Matrix().filter_inverse(temp, inverse, rows, cols);
    set_switch_determinant();
    set_switch_inverse();
}

void Playground::fetch_adjoint_from_inverse() {
    size_t n = rows; // dimensions
    adjoint = new double[n*n];
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
}

void Playground::show_determinant() {
    cout << "Determinant : " << det << endl;
}

int main() {
    Playground ground;

    do {
        if (!ground.get_switch_a()) {
            // cout << ground.get_switch_a() << endl;
            cout << " 1 >> ENTER SIMPLE SQUARE MATRIX\n";
            cout << " 2 >> ENTER AUGMENTED MATRIX\n";
            // TODO: Remove this
            cout << " 3 >> ENTER MATRIX TO BE INVERTED\n";
        } else {
            cout << " 1 >> CHANGE MATRIX\n";
            cout << " 2 >> TRANSPOSE\n";
            cout << " 3 >> FIND DETERMINANT\n";
            char aug = ground.check_augmented();
            if (aug == 'i') {
                cout << " 4 >> FIND DETERMINANT & INVERSE\n";
                cout << " 5 >> FIND DETERMINANT, INVERSE & ADJOINT\n";
            } else if (aug == 's')
                cout << " 4 >> FIND SOLUTION & DETERMINANT\n";
        }
        cout << "99 >> QUIT\n";

        int choice;
        cout << "Enter menu item index: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (!ground.get_switch_a()) {
                    ground.get_matrix('n');
                    ground.set_switch_a();
                }
                else {
                    ground.reset_switches();
                    continue;
                } break;

            case 2:
                if (!ground.get_switch_a()) {
                    ground.get_matrix('s');
                    ground.set_switch_a();
                }
                else {
                    ground.transpose();
                    ground.show_matrix('t');
                } break;

            case 3:
                if (!ground.get_switch_a()) {
                    ground.get_matrix('i');
                    ground.set_switch_a();
                }
                else {
                    ground.calculate_determinant();
                    ground.show_determinant();
                } break;

            case 4:
                if (ground.check_augmented() == 's') {
                    ground.solve();
                    ground.show_matrix('s');
                    ground.show_determinant();
                } else {
                    ground.invert();
                    ground.show_determinant();
                    ground.show_matrix('i');
                } break;

            case 5:
                ground.invert();
                ground.fetch_adjoint_from_inverse();
                ground.show_determinant();
                ground.show_matrix('i');
                ground.show_matrix('j');
                break;

            default : exit(0);
        }
    } while (true);

    return 0;
}
