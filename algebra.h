#ifndef __ALGEBRA__ 
#define __ALGEBRA__ 420

#include <vector>
#include "comp.h"


// Tensor product for square matrices
std::vector<std::vector<comp>> tensor_prod(
	std::vector<std::vector<comp>> arr1,
	std::vector<std::vector<comp>> arr2) 
{
	unsigned int dim;

	// tensor product dimension
	dim = arr1.size() * arr2.size();

	unsigned int p = arr2.size();

	std::vector<std::vector<comp>> elements;

	// fill array row-by-row with index formula
	for(unsigned int i = 0; i < dim; ++i) {
		std::vector<comp> row;
		for(unsigned int j = 0; j < dim; ++j)
			row.push_back( mul(arr1[i/p][j/p], arr2[i%p][j%p] ));
		elements.push_back(row);
	}


	return elements;
}





// Tensor product for square matrices
std::vector<std::vector<comp>> matrix_mul(
	std::vector<std::vector<comp>> arr1,
	std::vector<std::vector<comp>> arr2) 
{
	// Assume square matrices
	unsigned int dim;
	dim = arr1.size();
	std::vector<std::vector<comp>> elements;


	// fill array row-by-row with index formula
	for(unsigned int i = 0; i < dim; ++i) {
		std::vector<comp> row;
		for(unsigned int j = 0; j < dim; ++j) {
			// make c_ij
			comp c_ij = c(0.0, 0.0);
			for(unsigned int k = 0; k < dim; ++k)
				c_ij = add(c_ij, mul(arr1[i][k], arr2[k][j]));
			// push element to row
			row.push_back(c_ij);
		}
		// push back row
		elements.push_back(row);
	}


	return elements;
}




// return an I array with dimensions dim x dim
std::vector<std::vector<comp>> Identity_matrix(unsigned int dim) {
	std::vector<std::vector<comp>> result;

	for(unsigned int i = 0; i < dim; ++i){
		std::vector<comp> row;
		for(unsigned int j = 0; j < dim; ++j)
			if(i == j)
				row.push_back( c(1.0, 0.0) );
			else
				row.push_back( c(0.0, 0.0) );

		result.push_back( row );
	}

	return result;
}








// Anxn * Snx1
std::vector<comp> Array_dot_state(
	std::vector<std::vector<comp>> array,
	std::vector<comp> state ) 
{
	std::vector<comp> res;

	unsigned int dim = state.size();

	// matrix multiplication
	for(unsigned int i = 0; i < dim; ++i) {
		comp c_i = c(0.0, 0.0);

		// c_i = SUM a_ik b_k
		for(unsigned int k = 0; k < dim; ++k)
			c_i = add(c_i, mul(array[i][k], state[k]));

		res.push_back(c_i);
	}

	return res;
}







// THIS IS ONE GOOD BUT IT DOES NOT MAKE CONTROL GATES

// define direct sum of arrays
// on sparce arrays! 
/*
gate direct_sum(gate g1, gate g2) 
{
	unsigned int dim = g1.dimensions + g2.dimensions;

	std::vector<std::vector<comp>> elements;

	//   /A 0\
	//   \0 B/

	// array A rows
	for(int i = 0; i < g1.dimensions; ++i) {
		std::vector<comp> row;
		// alphas
		for(int j = 0; j < g1.dimensions; ++j)
			row.push_back(g1.array[i][j]);
		// zeros
		for(int j = 0; j < g2.dimensions; ++j)
			row.push_back( c(0.0,0.0) );

		elements.push_back(row);
	}

	// array B rows
	for(int i = 0; i < g2.dimensions; ++i) {
		std::vector<comp> row;

		// zeros
		for(int j = 0; j < g1.dimensions; ++j)
			row.push_back( c(0.0,0.0) );

		// betas
		for(int j = 0; j < g1.dimensions; ++j)
			row.push_back(g2.array[i][j]);

		elements.push_back(row);
	}

	return gate(dim, elements);
}
*/



#endif