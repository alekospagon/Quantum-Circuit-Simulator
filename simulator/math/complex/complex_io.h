#ifndef __MATH_COMPLEX_IO__
#define __MATH_COMPLEX_IO__

#include "complex_core.h"


inline void   	print_comp	(comp a);



// print as: a + ib
inline void print_comp (comp a) {
	if(a.real == 0.0 and a.imag == 0.0) {
		std::cout << "0  ";
		return;
	}

	// real part
	if(a.real != 0.0) 
		std::cout << a.real;

	// imaginary part
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




#endif