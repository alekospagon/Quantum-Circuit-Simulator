#ifndef __MATH_COMPLEX_OPERATIONS__
#define __MATH_COMPLEX_OPERATIONS__

#include "complex_core.h"




// operations
inline comp 	mul_conj	(comp a, comp b); // a * b_conj (for inner product)
inline c_type 	distance	(comp a, comp b); // for equality precision


// complex arithmetic
inline comp operator + (comp c1, comp c2);
inline comp operator - (comp c1, comp c2);
inline comp operator * (comp c1, comp c2);
inline comp operator / (comp c1, comp c2);


// complex-real arithmetic
inline comp operator + (comp c, c_type r); // position independant
inline comp operator + (c_type r, comp c);
inline comp operator * (comp c, c_type r);
inline comp operator * (c_type r, comp c);
inline comp operator - (comp c, c_type r); // position dependant
inline comp operator - (c_type r, comp c);
inline comp operator / (comp c, c_type r);
inline comp operator / (c_type r, comp c);








// COMPLEX CONJUGATE MULTIPLICATION a*b
inline comp mul_conj(comp a, comp b) {
	return (comp) {
		a.real*b.real + a.imag*b.imag, 
		a.real*b.imag - a.imag*b.real};
}



// euclidean distance of two complex numbers
inline c_type distance (comp a, comp b) {
	// manhattan distance
	return abs(a.real - b.real) + abs(a.imag - b.imag);
}




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







// Complex @ Real   AND   Real @ Complex

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
    return (comp) { (r * c.real) / den, (- r * c.imag) / den };
}



#endif