#ifndef __MY_COMPLEX_LIBRARY
#define __MY_COMPLEX_LIBRARY 420
#include <iostream> // cout
#include <math.h>	// sqrt
#include <stdlib.h>	// abs

#include "parameters.h"

// CORE LIBRARY FOR COMPLEX NUMBERS

// Constants
const c_type pi = 3.141592653589793238;


// CUSTOM COMPLEX NUMBER
typedef struct complex__{
	c_type real;
	c_type imag;
} comp;


// Complex Operations
inline comp 	c			(c_type real, c_type imag);
inline comp 	conj		(comp a);
inline comp 	mul_conj	(comp a, comp b);
inline c_type 	distance	(comp a, comp b);
inline void   	print_comp	(comp a);




// Complex Number Constructor
inline comp c(c_type _real, c_type _imag) {
	return (comp) {_real, _imag};
}



inline comp conj (comp a) {
	return (comp) {a.real, -a.imag};
}




// COMPLEX CONJUGATE MULTIPLICATION a*b
inline comp mul_conj(comp a, comp b) {
	return (comp) {a.real*b.real + a.imag*b.imag, 
		a.real*b.imag - a.imag*b.real};
}


// print as: a + ib
inline void print_comp (comp a) {
	if(a.real == 0.0 and a.imag == 0.0) {
		std::cout << "0  ";
		return;
	}

	if(a.real != 0.0) 
		std::cout << a.real;

	if(a.imag != 0.0) {
		if(a.imag > 0.0) {
			std::cout << "+i";
			if(a.imag != 1.0)
				std::cout <<  a.imag;
		}
		else {
			std::cout << "-i";
			if(a.imag != -1.0)
				std::cout << -a.imag;
		}
	}

	std::cout << "  ";
}


// euclidean distance of two complex numbers
inline c_type distance (comp a, comp b) {
	// manhattan distance
	return abs(a.real - b.real) + abs(a.imag - b.imag);
}



// Define imaginary unit
// const comp i = (comp) {0.0, 1.0};




// Complex Arithmetics

// COMPLEX OPERATOR COMPLEX

inline comp operator + (comp c1, comp c2) {
    return comp {c1.real + c2.real, c1.imag + c2.imag}; 
}

inline comp operator - (comp c1, comp c2) {
    return comp {c1.real - c2.real, c1.imag - c2.imag}; 
}

inline comp operator * (comp c1, comp c2) {
    return (comp) {c1.real*c2.real - c1.imag*c2.imag, 
		c1.real*c2.imag + c1.imag*c2.real};  
}

inline comp operator / (comp c1, comp c2) {
	c_type den = c2.real * c2.real + c2.imag * c2.imag;

    return (comp) {
    	(c1.real * c2.real + c1.imag * c2.imag) / den, 
		(c1.imag * c2.real - c1.real * c2.imag) / den
	};
}




// COMPLEX OPERATOR REAL & REAL OPERATOR COMPLEX

// position independant
inline comp operator + (comp c, c_type r) { return (comp) {r + c.real, c.imag}; }
inline comp operator + (c_type r, comp c) { return (comp) {r + c.real, c.imag}; }
inline comp operator * (comp c, c_type r) { return (comp) {r * c.real, r * c.imag}; }
inline comp operator * (c_type r, comp c) { return (comp) {r * c.real, r * c.imag}; }

// position dependant
inline comp operator - (comp c, c_type r) { return (comp) {c.real - r, c.imag}; }
inline comp operator - (c_type r, comp c) { return (comp) {r - c.real, -c.imag}; }
inline comp operator / (comp c, c_type r) { return (comp) {c.real / r, c.imag / r}; }
inline comp operator / (c_type r, comp c) { 
	c_type den = c.real * c.real + c.imag * c.imag;
    return (comp) { (r * r + c.imag * c.imag) / den, (- r * c.imag) / den };
}



#endif
