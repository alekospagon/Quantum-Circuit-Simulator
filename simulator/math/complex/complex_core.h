#ifndef __MATH_COMPLEX_CORE__
#define __MATH_COMPLEX_CORE__
#include <iostream> 	// cout
#include <math.h>		// sqrt
#include <stdlib.h>		// abs



// basic mathematics type. float for speed. double for precision.
typedef double c_type; // float

const c_type pi = 3.141592653589793238;


// TYPE
typedef struct complex__{
	c_type real;
	c_type imag;
} comp;



// Complex Construction
inline comp 	c 			(c_type real, c_type imag);
inline comp 	conj		(comp a);


// Complex Number Constructor
inline comp c(c_type _real, c_type _imag) {
	return (comp) {_real, _imag};
}


inline comp conj (comp a) {
	return (comp) {a.real, -a.imag};
}


#endif
