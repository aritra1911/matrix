#include <cmath>
using namespace std;

class Matrix {
protected:
    void swap_rows(double * const, size_t, size_t, size_t);

public:
    void copy_matrix(double * const, const double * const,
                     const size_t, const size_t);
    void filter_inverse(const double * const, double * const,
                        const size_t, const size_t);
    void eliminate(double *, const size_t, const size_t, double&);
    void back_substitute(const double * const, double * const,
                         const size_t, const size_t);
    void reduce(double *, const size_t, const size_t);
};
