#ifndef __GATES__
#define __GATES__ 420

#include <math.h>
#include <vector>
#include <iostream>
#include "comp.h"			// complex numbers
#include "array_library.h"	// standard gates
#include "algebra.h"		// tensor_product

#include "parameters.h"


// Gate: has dimensions and a list of elemetns
class gate {
	public:
		unsigned int dimensions;
		std::vector<std::vector<comp>> array;
	
		// constructor
		gate(unsigned int dim, const std::vector<std::vector<comp>> &els);
		gate() = default;
		void print_gate();
};




// GATE CONSTRUCTOR
gate::gate(unsigned int dim, const std::vector<std::vector<comp>> & els) {

	// =========== CHECK DIMENSIONS =========== //
	if (dim == 0) {
		std::cout << "Error while initializing gate: "
			"Dimension is zero. Exiting!\n";
		exit(1);
	}
	// check if n is power of 2 with binary hacking:
	if ((dim & (~(dim - 1))) != dim) {
		std::cout << "Error while initializing gate: "
			"Dimension is not a power of 2a\n";
		exit(1);
	}
	dimensions = dim;
	
	if (els.size() != dim) {
		std::cout << "Array has wrong dimensions (rows)\n";
		exit(1);
	}


	// =========== FILL ARRAY AND CHECK ROW'S DIMENSIONS =========== //
	for(long unsigned int i = 0; i < els.size(); ++i) {
		if (els[i].size() != dim) {
			std::cout << "Array has wrong dimensions (col: " << i << ")\n";
			exit(1);
		}
	}

	// copy array
	array = els;


	// =========== CHECK IF MATRIX IS UNITARY! =========== //
	// Check is: UU^dag = I 
	// I don't need to create U^dag. I know it's elements

	
	for(long unsigned int i = 0; i < dim; ++i)
		for(long unsigned int j = 0; j < dim; ++j) {
			// c_ij = SUM a_ik b_kj
			// but b_kj = a_jk* --> USE mul_conj from "comp.h"
			comp elem = c(0.0, 0.0);
			for(unsigned int k = 0; k < dim; ++k)
				elem = elem + mul_conj(array[j][k], array[i][k]);

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

	for(unsigned int i = 0; i < dimensions; i++) {
		for(unsigned int j = 0; j < dimensions; j++)
			print_comp(array[i][j]);
		std::cout << "\n";
	}
}



// STANDARD GATE LIBRARY
const gate gate_I = gate(2, arr_I);
const gate gate_H = gate(2, arr_H);
const gate gate_X = gate(2, arr_X);
const gate gate_Y = gate(2, arr_Y);
const gate gate_Z = gate(2, arr_Z);

const gate gate_S = gate(2, arr_S);
const gate gate_T = gate(2, arr_T);

const gate gate_CNOT = gate(4, arr_CNOT);
const gate gate_CY   = gate(4, arr_CY);
const gate gate_CZ   = gate(4, arr_CZ);
const gate gate_SWAP = gate(4, arr_SWAP);

const gate gate_TOFFOLI = gate(8, arr_TOFFOLI);


const gate gate_RX(c_type angle){ return gate(2, arr_RX(angle)); }
const gate gate_RY(c_type angle){ return gate(2, arr_RY(angle)); }
const gate gate_RZ(c_type angle){ return gate(2, arr_RZ(angle)); }
const gate gate_P (c_type angle){ return gate(2, arr_P (angle)); }
const gate gate_ROT(c_type phi, c_type theta, c_type omega){
	return gate(2, arr_ROT(phi, theta, omega));
}
const gate gate_CRX(c_type angle){ return gate(4, arr_CRX(angle)); }
const gate gate_CRY(c_type angle){ return gate(4, arr_CRY(angle)); }
const gate gate_CRZ(c_type angle){ return gate(4, arr_CRZ(angle)); }




#endif
