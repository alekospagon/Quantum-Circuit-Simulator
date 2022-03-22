#include <stdio.h>

// COMPLEX NUMBER PAIR
typedef struct complex__{
	double real;
	double imag;
} comp;

// make, z+w, zw, z*w
inline comp c			(double real, double imag);
inline comp add			(comp a, comp b);
inline comp mul			(comp a, comp b);
inline comp mul_conj	(comp a, comp b);
void   print_comp		(comp a);

// Fast constructor
inline comp c(double real, double imag) {
	comp res;
	res.real = real;
	res.imag = imag;

	return res;
}


// COMPLEX ADDITION a+b
inline comp add(comp a, comp b) {
	comp res;
	res.real = a.real + b.real;
	res.imag = a.imag + b.imag;

	return res;
}

// COMPLEX MULTIPLICATION a*b
inline comp mul(comp a, comp b) {
	comp res;
	// compute mul
	res.real = a.real*b.real - a.imag*b.imag;
	res.imag = a.real*b.imag + a.imag*b.real;
	return res;
}

// COMPLEX MULTIPLICATION a*b
inline comp mul_conj(comp a, comp b) {
	comp res;
	// compute mul with a conjugate
	res.real = a.real*b.real + a.imag*b.imag;
	res.imag = a.real*b.imag - a.imag*b.real;
	return res;
}

void print_comp (comp a) {
	printf("(%lf,%lf)", a.real, a.imag);
}
