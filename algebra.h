#ifndef __ALGEBRA__ 
#define __ALGEBRA__ 420

#include <vector>
#include "parameters.h"
#include "comp.h"





// =========== FUNCTION DEFINITIONS =========== //
std::vector<std::vector<comp>> square_tensor_prod(
	const std::vector<std::vector<comp>> &arr1,
	const std::vector<std::vector<comp>> &arr2);

std::vector<std::vector<comp>> square_matrix_mul(
	const std::vector<std::vector<comp>> &arr1,
	const std::vector<std::vector<comp>> &arr2);

std::vector<std::vector<comp>> Identity_matrix(
	unsigned int dim);

std::vector<comp> Array_dot_state(
	const std::vector<std::vector<comp>> &array,
	const std::vector<comp> &state);

bool is_hermitian(
	const std::vector<std::vector<comp>> &Obs );

c_type expectation_value (
	const std::vector<std::vector<comp>> &Obs,
	const std::vector<comp> &state );






// =========== FUNCTION IMPLEMENTATIONS =========== //


// Tensor product for square matrices
std::vector<std::vector<comp>> square_tensor_prod(
	const std::vector<std::vector<comp>> &arr1,
	const std::vector<std::vector<comp>> &arr2) 
{
	// =========== CHECK DIMENSIONS! =========== //
	unsigned int dim1 = arr1.size();
	for(unsigned int i = 0; i < dim1; ++i)
		if(arr1[i].size() != dim1) {
			std::cout << "Tensor Product Error:"
				"First array is not a square\n";
				exit(1);
		}
	unsigned int dim2 = arr2.size();
	for(unsigned int i = 0; i < dim2; ++i)
		if(arr2[i].size() != dim2) {
			std::cout << "Tensor Product Error:"
				"Second array is not a square\n";
				exit(1);
		}


	// tensor product dimension
	unsigned int dim = arr1.size() * arr2.size();
	unsigned int p = arr2.size();

	// =========== FILL ARRAY =========== //
	std::vector<std::vector<comp>> 
		elements(dim, std::vector<comp>(dim));

	// Closed Formula for C_ij from wikipedia
	for(unsigned int i = 0; i < dim; ++i) {
		for(unsigned int j = 0; j < dim; ++j)
			elements[i][j] = arr1[i/p][j/p] * arr2[i%p][j%p];
	}

	return elements;
}





// Tensor product for square matrices
std::vector<std::vector<comp>> square_matrix_mul(
	const std::vector<std::vector<comp>> &arr1,
	const std::vector<std::vector<comp>> &arr2) 
{
	// =========== CHECK DIMENSIONS! =========== //
	unsigned int dim1 = arr1.size();
	for(unsigned int i = 0; i < dim1; ++i)
		if(arr1[i].size() != dim1) {
			std::cout << "Matrix Multiplication Error:"
				"First array is not a square\n";
				exit(1);
		}
	unsigned int dim2 = arr2.size();
	for(unsigned int i = 0; i < dim2; ++i)
		if(arr2[i].size() != dim2) {
			std::cout << "Matrix Multiplication Error:"
				"Second array is not a square\n";
				exit(1);
		}


	// =========== FILL ARRAY =========== //
	unsigned int dim;
	dim = arr1.size();
	std::vector<std::vector<comp>> 
		elements(dim, std::vector<comp>(dim));

	for(unsigned int i = 0; i < dim; ++i) {
		for(unsigned int j = 0; j < dim; ++j) {
			comp c_ij = c(0.0, 0.0);
			for(unsigned int k = 0; k < dim; ++k)
				c_ij = c_ij + arr1[i][k] * arr2[k][j];

			elements[i][j] = c_ij;
		}
	}

	return elements;
}




// return an I array with dimensions dim x dim
std::vector<std::vector<comp>> Identity_matrix(unsigned int dim) {

	std::vector<std::vector<comp>> 
		result(dim, std::vector<comp> (dim));

	for(unsigned int i = 0; i < dim; ++i)
		for(unsigned int j = 0; j < dim; ++j)
			result[i][j] = (i == j) ? c(1.0, 0.0) : c(0.0, 0.0);

	return result;
}








// Anxn * Snx1
std::vector<comp> Array_dot_state(
	const std::vector<std::vector<comp>> &array,
	const std::vector<comp> &state ) 
{
	// =========== CHECK DIMENSIONS! =========== //
	unsigned int dim1 = array.size();
	for(unsigned int i = 0; i < dim1; ++i)
		if(array[i].size() != dim1) {
			std::cout << "Array Dot State Error:"
				"Array is not a square\n";
				exit(1);
		}
	if(state.size() != dim1) {
		std::cout << "Array Dot State Error:"
			"Array and State dimensions don't match\n";
			exit(1);
	}


	unsigned int dim = state.size();

	std::vector<comp> res(dim);

	// matrix multiplication
	for(unsigned int i = 0; i < dim; ++i) {
		comp c_i = c(0.0, 0.0);
		// c_i = SUM a_ik b_k
		for(unsigned int k = 0; k < dim; ++k)
			c_i = c_i + array[i][k] * state[k];

		res[i] = c_i;
	}

	return res;
}







// THIS IS GOOD, BUT IT DOES NOT MAKE CONTROL GATES

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





bool is_hermitian( const std::vector<std::vector<comp>> &Obs ) {

	// =========== CHECK DIMENSIONS! =========== //
	unsigned int rows = Obs.size();
	for(unsigned int row = 0; row < rows; ++row) {

		unsigned int columns = Obs[row].size();
		if(rows != columns) {
			std::cout << "Observable Matrix is not Square!\n";
			exit(1);
		}
	}

	// ============ CHECK ELEMENTS ============ //
	// Hermitian means: a_ij = a_ji*
	for(unsigned int i = 0; i < rows; ++i) {
		for(unsigned int j = 0; j < rows; ++j) 
			// allow a small error --> their distance
			if( distance(Obs[i][j], conj(Obs[j][i])) > 0.0001 ) 
				return false;
	}

	return true;
}




// Returns:   <A> = <Psi|A|Psi>
c_type expectation_value (
	const std::vector<std::vector<comp>> &Obs,
	const std::vector<comp> &state )
{
	// =========== ARRAY CHECKS =========== //
	if(!is_hermitian(Obs)) {
		std::cout << "Expectation Value Error: "
			"Observable matrix is not Hermitian!\n";
		exit(1);
	}


	// =========== COMPUTE Right=A|Psi> =========== //
	/*
	unsigned int dim = state.size();

	std::vector<comp> right_product (dim);
	for(unsigned int i = 0; i < dim; ++i) {
		comp tmp = c(0.0, 0.0);
		for(unsigned int j = 0; j < dim; ++j)
			tmp = tmp + Obs[i][j] * state[j];
		right_product[i] = tmp;
	}

	// =========== COMPUTE <Psi|Right> =========== //
	// Note: <Psi| = |Psi> CONJUGATE
	comp tmp_res = c(0.0, 0.0);
	for(unsigned int i = 0; i < dim; ++i)
		tmp_res = tmp_res + mul_conj(state[i], right_product[i]);
	*/

	unsigned int dim = state.size();
	comp tmp_res = c(0.0, 0.0);
	for(unsigned int i = 0; i < dim; ++i) {
		comp tmp = c(0.0, 0.0);
		for(unsigned int j = 0; j < dim; ++j)
			tmp = tmp + Obs[i][j] * state[j];
		tmp_res = tmp_res + mul_conj(state[i], tmp);
	}



	// this complex should be real.
	if( abs(tmp_res.imag) > 0.0001 ) {
		std::cout << "Expectation Value Error: "
			"Result has big imaginary part\n";
		exit(1);
	}
	return tmp_res.real;
}








#endif