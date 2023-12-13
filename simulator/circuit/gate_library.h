#ifndef __ARRAY_LIBRARY__
#define __ARRAY_LIBRARY__ 420

#include <vector>
#include <math.h>
#include "../math/math.h"



// Contains: Arrays and SqMatrix'es based on those arrays
// Bad Idea!! make SqMatrices out of these with 1 step!



/*
 *  NON PARAMETRIC OPERATIONS!!!!!
 */


// ===== ONE QUBIT OPERATIONS =====
// I, H, X, Y, Z, S, T, 

const std::vector<std::vector<comp>> arr_I {
	{ c(1.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(1.0,0.0) }
};


const c_type sqrt1_2 = sqrt(0.5);
const std::vector<std::vector<comp>> arr_H {
	{ c(sqrt1_2,0.0), c( sqrt1_2,0.0)},
	{ c(sqrt1_2,0.0), c(-sqrt1_2,0.0)}
};

// PAULI GATES
const std::vector<std::vector<comp>> arr_X {
	{ c(0.0,0.0), c(1.0,0.0) },
	{ c(1.0,0.0), c(0.0,0.0) }
};
const std::vector<std::vector<comp>> arr_Y {
	{ c(0.0,0.0), c(0.0,-1.0) },
	{ c(0.0,1.0), c(0.0, 0.0) }
};
const std::vector<std::vector<comp>> arr_Z {
	{ c(1.0,0.0), c( 0.0,0.0) },
	{ c(0.0,0.0), c(-1.0,0.0) }
};

// 1  0 			1 0
// 0  e^{i pi/2} =	0 i
const std::vector<std::vector<comp>> arr_S {
	{ c(1.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(0.0,1.0) }
};
// 1  0
// 0  e^{i pi/4}
const std::vector<std::vector<comp>> arr_T {
	{ c(1.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(cos(pi/4),sin(pi/4)) }
};






// ===== MULTI QUBIT OPERATIONS =====
// CNOT, CY, CZ, SWAP, TOFFOLI
const std::vector<std::vector<comp>> arr_CNOT {
	{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(1.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) }
};

const std::vector<std::vector<comp>> arr_CY {
	{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,-1.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,1.0), c(0.0,0.0) }
};

const std::vector<std::vector<comp>> arr_CZ {
	{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(-1.0,0.0) }
};

const std::vector<std::vector<comp>> arr_SWAP {
	{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(1.0,0.0) }
};
const std::vector<std::vector<comp>> arr_TOFFOLI {
	{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(1.0,0.0) }, 
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) }
};











/*
 *  PARAMETRIC OPERATIONS!!!!!
 */



// ===== ONE QUBIT OPEARATIONS =====
// RX, RY, RZ, P, CRX, CRY, CRZ, CP 
std::vector<std::vector<comp>> arr_RX (c_type angle) {
	return {
		{ c(cos(angle/2.0),0.0), c(0.0,-sin(angle/2.0)) },
		{ c(0.0,-sin(angle/2.0)), c(cos(angle/2.0),0.0) }
	};
}


std::vector<std::vector<comp>> arr_RY (c_type angle) {
	return {
		{ c(cos(angle/2.0),0.0), c(-sin(angle/2.0),0.0) },
		{ c(sin(angle/2.0),0.0), c(cos(angle/2.0),0.0) }
	};
}


std::vector<std::vector<comp>> arr_RZ (c_type angle) {
	return {
		{ c(cos(angle/2.0),-sin(angle/2.0)), c(0.0,0.0) },
		{ c(0.0,0.0), c(cos(angle/2.0),sin(angle/2.0)) }
	};
}


// 1 0
// 0 e^{i phi}
std::vector<std::vector<comp>> arr_P (c_type angle) {
	return {
		{ c(1.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(cos(angle),sin(angle)) }
	};
}


// ===== TWO QUBIT OPEARATIONS =====
std::vector<std::vector<comp>> arr_CRX (c_type angle) {
	c_type phi = angle/2.0;

	return {
		{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(cos(phi),0.0), c(0.0,-sin(phi)) },
		{ c(0.0,0.0), c(0.0,0.0), c(0.0,-sin(phi)), c(cos(phi),0.0) }
	};
}

std::vector<std::vector<comp>> arr_CRY (c_type angle) {
	c_type phi = angle/2.0;

	return {
		{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(cos(phi),0.0), c(-sin(phi),0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(sin(phi),0.0), c(cos(phi),0.0) }
	};
}

std::vector<std::vector<comp>> arr_CRZ (c_type angle) {
	c_type phi = angle/2.0;

	return {
		{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(cos(phi),-sin(phi)), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(cos(phi), sin(phi)) }
	};
}


std::vector<std::vector<comp>> arr_CP (c_type angle) {
	return {
		{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0),c(cos(angle),sin(angle)) }
	};
}








/*
 *  GRADIENTS OF PARAMETRIC GATES
 */
std::vector<std::vector<comp>> arr_RX_dif (c_type angle) {
	return {
		{ c(-sin(angle/2.0)/2.0,0.0), c(0.0,-cos(angle/2.0)/2.0) },
		{ c(0.0,-cos(angle/2.0)/2.0), c(-sin(angle/2.0)/2.0,0.0) }
	};
}



std::vector<std::vector<comp>> arr_RY_dif (c_type angle) {
	return {
		{ c(-sin(angle/2.0)/2.0,0.0), c(-cos(angle/2.0)/2.0,0.0) },
		{ c( cos(angle/2.0)/2.0,0.0), c(-sin(angle/2.0)/2.0,0.0) }
	};
}



std::vector<std::vector<comp>> arr_RZ_dif (c_type angle) {
	return {
		{ c(-sin(angle/2.0)/2.0,-cos(angle/2.0)/2.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(-sin(angle/2.0)/2.0,cos(angle/2.0)/2.0) }
	};
}


// 1 0
// 0 e^{i phi}
std::vector<std::vector<comp>> arr_P_dif (c_type angle) {
	return {
		{ c(1.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(-sin(angle),cos(angle)) }
	};
}



// ===== TWO QUBIT OPEARATIONS =====
std::vector<std::vector<comp>> arr_CRX_dif (c_type angle) {
	c_type phi = angle/2.0;

	return {
		{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(-sin(phi)/2.0,0.0), c(0.0,-cos(phi)/2.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(0.0,-cos(phi)/2.0), c(-sin(phi)/2.0,0.0) }
	};
}

std::vector<std::vector<comp>> arr_CRY_dif (c_type angle) {
	c_type phi = angle/2.0;

	return {
		{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(-sin(phi)/2.0,0.0), c(-cos(phi)/2.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(cos(phi)/2.0,0.0), c(-sin(phi)/2.0,0.0) }
	};
}

std::vector<std::vector<comp>> arr_CRZ_dif (c_type angle) {
	c_type phi = angle/2.0;

	return {
		{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(-sin(phi)/2.0,-cos(phi)/2.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(-sin(phi)/2.0,cos(phi)/2.0) }
	};
}


std::vector<std::vector<comp>> arr_CP_dif (c_type angle) {
	return {
		{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0),c(-sin(angle),cos(angle)) }
	};
}



// Debug info
void print_array(std::vector<std::vector<comp>> arr) {
	unsigned int dim1 = arr.size();
	for(unsigned int i = 0; i < dim1; ++i) {
		unsigned int dim2 = arr[i].size();
		for(unsigned int j = 0; j < dim2; ++j)
			print_comp(arr[i][j]);
		std::cout << "\n";
	}
}






const SqMatrix empty(0);


// NON-PARAMETRIC MATRICES
// ===== ONE QUBIT OPERATIONS =====
const SqMatrix matrix_I(arr_I);
const SqMatrix matrix_H(arr_H);
const SqMatrix matrix_X(arr_X);
const SqMatrix matrix_Y(arr_Y);
const SqMatrix matrix_Z(arr_Z);
const SqMatrix matrix_S(arr_S);
const SqMatrix matrix_T(arr_T);
// ===== TWO QUBIT OPERATIONS =====
const SqMatrix matrix_CNOT(arr_CNOT);
const SqMatrix matrix_CY(arr_CY);
const SqMatrix matrix_CZ(arr_CZ);
const SqMatrix matrix_SWAP(arr_SWAP);
// ===== THREE QUBIT OPERATIONS =====
const SqMatrix matrix_TOFFOLI(arr_TOFFOLI);


// TO DO --> make SqMatrix at once without calling arr_XXX

// PARAMETRIC MATRICES
// ===== ONE QUBIT OPERATIONS =====
SqMatrix matrix_RX(c_type angle) { return SqMatrix(arr_RX(angle)); }
SqMatrix matrix_RY(c_type angle) { return SqMatrix(arr_RY(angle)); }
SqMatrix matrix_RZ(c_type angle) { return SqMatrix(arr_RZ(angle)); }
SqMatrix matrix_P (c_type angle) { return SqMatrix(arr_P (angle)); }
// SqMatrix matrix_ROT(c_type phi, c_type theta, c_type omega) { return SqMatrix(arr_ROT(phi, theta, omega)); }
// ===== TWO QUBIT OPERATIONS =====
SqMatrix matrix_CRX(c_type angle) { return SqMatrix(arr_CRX(angle)); }
SqMatrix matrix_CRY(c_type angle) { return SqMatrix(arr_CRY(angle)); }
SqMatrix matrix_CRZ(c_type angle) { return SqMatrix(arr_CRZ(angle)); }
SqMatrix matrix_CP(c_type angle) { return SqMatrix(arr_CP(angle)); }



// DERIVATIVES OF GATES
// ===== ONE QUBIT OPERATIONS =====
SqMatrix matrix_RX_dif(c_type angle) { return SqMatrix(arr_RX_dif(angle)); }
SqMatrix matrix_RY_dif(c_type angle) { return SqMatrix(arr_RY_dif(angle)); }
SqMatrix matrix_RZ_dif(c_type angle) { return SqMatrix(arr_RZ_dif(angle)); }
SqMatrix matrix_P_dif (c_type angle) { return SqMatrix(arr_P_dif (angle)); }
// SqMatrix matrix_ROT(c_type phi, c_type theta, c_type omega) { return SqMatrix(arr_ROT(phi, theta, omega)); }
// ===== TWO QUBIT OPERATIONS =====
SqMatrix matrix_CRX_dif(c_type angle) { return SqMatrix(arr_CRX_dif(angle)); }
SqMatrix matrix_CRY_dif(c_type angle) { return SqMatrix(arr_CRY_dif(angle)); }
SqMatrix matrix_CRZ_dif(c_type angle) { return SqMatrix(arr_CRZ_dif(angle)); }
SqMatrix matrix_CP_dif(c_type angle) { return SqMatrix(arr_CP_dif(angle)); }





#endif
