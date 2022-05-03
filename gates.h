#ifndef __GATES__
#define __GATES__ 420

#include <math.h>
#include <vector>
#include <iostream>
#include "comp.h"			// complex numbers
#include "array_library.h"	// standard gates
#include "algebra.h"		// tensor_product





// Gate: has dimensions and a list of elemetns
// This implementation of sparse arrays is 
// useful with multi-qubit layers. if a single qubit gate
// has 2 zeros then the matrix representing the whole layer
// has already half its entries zeros (from the definition
// of tensor prouct). So keep only non-zero values
class gate {
	public:
		unsigned int dimensions;
		std::vector<std::vector<comp>> array;
	
		gate(unsigned int dim, std::vector<std::vector<comp>> els);
		gate() = default;
		void print_gate();
};


// GATE CONSTRUCTOR
gate::gate(unsigned int dim, std::vector<std::vector<comp>> els) {

	// DIMENSIONS
	if (dim == 0) {
		std::cout << "Error while initializing gate:" 
			" Dimension is zero. Exiting!\n";
		exit(1);
	}
	// check if n is power of 2 in binary:
	if ((dim & (~(dim - 1))) != dim) {
		std::cout << "Error while initializing gate:" 
			" Dimension is not a power of 2a\n";
		exit(1);
	}
	dimensions = dim;
	
	// check dimensionality
	if (els.size() != dim) {
		std::cout << "Array has wrong dimensions (rows)\n";
		exit(1);
	}

	// ELEMENTS
	for(long unsigned int i = 0; i < els.size(); ++i) {
		if (els[i].size() != dim) {
			std::cout << "Array has wrong dimensions (col: " << i << ")\n";
			exit(1);
		}

		// row-by-row
		std::vector<comp> row;
		for(long unsigned int j = 0; j< els[i].size(); ++j)
			row.push_back(els[i][j]);
		array.push_back(row);
	}

	// check if matrix is unitary!!!!!
	// UU^dag = I
	// I don't need to make U^dag. I need to save space and time

	
	for(long unsigned int i = 0; i < dim; ++i)
		for(long unsigned int j = 0; j < dim; ++j) {
			// c_ij = SUM a_ik b_kj
			// but b_kj = a_jk*
			comp elem = c(0.0, 0.0);
			for(unsigned int k = 0; k < dim; ++k)
				elem = add(elem, mul_conj(array[j][k], array[i][k]));

			// diagonal
			if (i == j) {
				if( distance(elem, c(1.0,0.0)) > 0.00001) {
					std::cout << "Error while making gate. "
						"Not a unitary matrix!!\n";
					exit(1);
				}
			}
			if (i != j) {
				if( distance(elem, c(0.0,0.0)) > 0.00001) {
					std::cout << "Error while making gate. "
						"Not a unitary matrix!!\n";
					exit(1);
				}
			}
	}
	
};



// print gate in a fancy (AND FULL) way
void gate::print_gate() {
	std::cout << "Printing Gate\n";
	std::cout << "Gate dimensions: " << dimensions << "\n";

	// print
	for(unsigned int i = 0; i < dimensions; i++) {
		for(unsigned int j = 0; j < dimensions; j++)
			print_comp(array[i][j]);
		std::cout << "\n";
	}
}


// STANDARD GATE LIBRARY

gate gate_I() { return gate(2, arr_I); }
gate gate_H() { return gate(2, arr_H); }
gate gate_X() { return gate(2, arr_X); }
gate gate_Y() { return gate(2, arr_Y); }
gate gate_Z() { return gate(2, arr_Z); }

gate gate_CNOT(){ return gate(4, arr_CNOT); }
gate gate_CY(){ return gate(4, arr_CY); }
gate gate_CZ(){ return gate(4, arr_CZ); }
gate gate_SWAP(){ return gate(4, arr_SWAP); }



gate gate_RX(c_type angle){ return gate(2, arr_RX(angle)); }
gate gate_RY(c_type angle){ return gate(2, arr_RY(angle)); }
gate gate_RZ(c_type angle){ return gate(2, arr_RZ(angle)); }
gate gate_ROT(c_type phi, c_type theta, c_type omega){
	return gate(2, arr_ROT(phi, theta, omega));
}
gate gate_CRX(c_type angle){	return gate(4, arr_CRX(angle)); }
gate gate_CRY(c_type angle){ return gate(4, arr_CRY(angle)); }
gate gate_CRZ(c_type angle){ return gate(4, arr_CRZ(angle)); }




#endif