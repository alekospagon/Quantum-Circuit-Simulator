#ifndef __MY_COMPLEX_LIBRARY
#define __MY_COMPLEX_LIBRARY 420
#include <iostream> // cout
#include <math.h>	// sqrt
#include <stdlib.h>	// abs
// CORE LIBRARY FOR COMPLEX NUMBERS
// HAS TO BE FAST!!!



// double --> precision
// float  --> performance
typedef double c_type;
//typedef float c_type;


// CUSTOM COMPLEX NUMBER
typedef struct complex__{
	c_type real;
	c_type imag;
} comp;


// Complex Operations
inline comp c			(c_type real, c_type imag);
inline comp add			(comp a, comp b);
inline comp mul			(comp a, comp b);
inline comp mul_conj	(comp a, comp b);
inline c_type distance	(comp a, comp b);
void   print_comp		(comp a);





// Constructor
inline comp c(c_type _real, c_type _imag) {
	return (comp) {real: _real, imag: _imag};
}


// COMPLEX ADDITION a+b
inline comp add(comp a, comp b) {
	return (comp) {real: a.real + b.real, 
		imag: a.imag + b.imag};
}

// COMPLEX MULTIPLICATION a*b
inline comp mul(comp a, comp b) {
	return (comp) {real: a.real*b.real - a.imag*b.imag, 
		imag: a.real*b.imag + a.imag*b.real};
}

// COMPLEX MULTIPLICATION a*b
inline comp mul_conj(comp a, comp b) {
	return (comp) {real: a.real*b.real + a.imag*b.imag, 
		imag: a.real*b.imag - a.imag*b.real};
}

// a + ib
void print_comp (comp a) {
	std::cout << a.real << " +i" << a.imag << "  ";
}


inline c_type distance (comp a, comp b) {
	// manhattan distance
	return abs(a.real - b.real) + abs(a.imag - b.imag);
}


#endif