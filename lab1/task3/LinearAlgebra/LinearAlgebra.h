#ifndef LAB1INVERT_LINEARALGEBRA_H
#define LAB1INVERT_LINEARALGEBRA_H

double computeDeterminant(const double (&matrix)[2][2]);
double computeDeterminant(const double (&matrix)[3][3]);
void computeInvertMatrix(const double (&inputMatrix)[3][3], double (&invertMatrix)[3][3]);

#endif //LAB1INVERT_LINEARALGEBRA_H
