#ifndef __MATH_ALGEBRA_CORE__ 
#define __MATH_ALGEBRA_CORE__ 

#include <vector>
#include "../complex/complex.h"


// make vector into array?

// 2D Square Matrix implemented with 1D flattened array
class SqMatrix {
	private:
		// rows and columns
		unsigned int _dims;
		std::vector<comp> _elems;

	public:
		// constructors
		inline SqMatrix(unsigned int d);
		inline SqMatrix(std::vector<std::vector <comp>> e);
		
		// element manipulation
		inline comp get(unsigned int r, unsigned int c) const;
		inline void set(unsigned int r, unsigned int c, comp e);
		inline unsigned int dims() const { return _dims; }
};








// memory allocate
inline SqMatrix::SqMatrix(unsigned int d) {
	_dims  = d;
	_elems = std::vector<comp> ( d*d );
}




// const .. &e  ???
inline SqMatrix::SqMatrix(std::vector<std::vector <comp>> e) {
	unsigned int d = e.size();

	#ifdef __SAFE_LIBRARY__
	for(unsigned int i = 0; i < d; ++i){
		if(e[i].size() != d) {
			std::cout << "Matrix Constructor Error: "
				<< "2D vector is not square\n";
			exit(1);
		}
	}
	#endif

	_elems = std::vector<comp> (d*d);
	_dims  = d;
	// block parallel? cache? 
	for(unsigned int i = 0; i < d; ++i)
		for(unsigned int j = 0; j < d; ++j)
			_elems[i * d + j] = e[i][j]; // d is a power of 2!!!!
}





inline comp SqMatrix::get(unsigned int r, unsigned int c) const {
	// you can ignore this. vector will crash anyway
	#ifdef __SAFE_LIBRARY__
	if(r > _dims-1){
		std::cout << "SqMatrix Get_Element Error:"
			"Element row index " << r << " out of range\n";
		exit(1);
	}
	if(c > _dims-1){
		std::cout << "SqMatrix Get_Element Error:"
			"Element column index " << c << " out of range\n";
		exit(1);
	}
	#endif

	return _elems[r * _dims + c];
}






inline void SqMatrix::set(unsigned int r, unsigned int c, comp e){
	// you can ignore this. vector will crash anyway
	#ifdef __SAFE_LIBRARY__
	if(r > _dims-1){
		std::cout << "SqMatrix Set_Element Error:"
			"Element row index " << r << " out of range\n";
		exit(1);
	}
	if(c > _dims-1){
		std::cout << "SqMatrix Set_Element Error:"
			"Element column index " << c << " out of range\n";
		exit(1);
	}
	#endif

	_elems[r * _dims + c] = e;
}



#endif
