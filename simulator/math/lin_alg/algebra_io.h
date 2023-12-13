#ifndef __MATH_ALGEBRA_IO__ 
#define __MATH_ALGEBRA_IO__ 


#include "algebra_core.h"


// print a vector
void print_vector(std::vector<c_type> vec) { // const &?
	std::cout << "Printing Vector\n";
	for(unsigned int i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << "\n";
}



// print a square matrix
void print_matrix(const SqMatrix &m) {
	int r = m.dims();

	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < r; ++j)
			print_comp( m.get(i, j) );
		std::cout << "\n";
	}
}



#endif