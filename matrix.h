#include <iostream>
#include <math.h>
using namespace std;

class Matrix {
public:
    void swap_rows(double * const, size_t, size_t, size_t);
    void eliminate(double *, const size_t, const size_t, double&);
    void back_substitute(const double * const, double * const,
                         const size_t, const size_t);
    void reduce(double *, const size_t, const size_t);
};
