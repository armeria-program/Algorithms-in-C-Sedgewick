#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct complex* complex_t;
complex_t complexInit(double re,double im);
double Re(complex_t z);
double Im(complex_t z);
complex_t complexMult(complex_t x,complex_t y);
complex_t complexAdd(complex_t x,complex_t y);

#endif
