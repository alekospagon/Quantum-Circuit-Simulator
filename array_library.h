#include <vector>
#include <math.h>
#include "comp.h"



// Standard Gates


// NON- PARAMETRIC GATES

// ===== ONE QUBIT OPEARATIONS =====
// 1 0
// 0 1
const std::vector<std::vector<comp>> arr_I {
	{ c(1.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(1.0,0.0) }
};

// 1		1  1
// sqrt(2)	1 -1
c_type sqrt2 = sqrt(2.0);
const std::vector<std::vector<comp>> arr_H {
	{ c(1.0 /sqrt2,0.0), c( 1.0/sqrt2,0.0)},
	{ c(1.0 /sqrt2,0.0), c(-1.0/sqrt2,0.0)}
};

// Pauli Gates
// 0 1
// 1 0
const std::vector<std::vector<comp>> arr_X {
	{ c(0.0,0.0), c(1.0,0.0) },
	{ c(1.0,0.0), c(0.0,0.0) }
};

// 0 -i
// i  0
const std::vector<std::vector<comp>> arr_Y {
	{ c(0.0,0.0), c(0.0,-1.0) },
	{ c(0.0,1.0), c(0.0, 0.0) }
};

// 1  0
// 0 -1
const std::vector<std::vector<comp>> arr_Z {
	{ c(1.0,0.0), c( 0.0,0.0) },
	{ c(0.0,0.0), c(-1.0,0.0) }
};


// ===== TWO QUBIT OPERATIONS =====
// 1 0 0 0 
// 0 1 0 0 
// 0 0 0 1
// 0 0 1 0
const std::vector<std::vector<comp>> arr_CNOT {
	{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(1.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) }
};

// 1 0 0  0 
// 0 1 0  0 
// 0 0 0 -i
// 0 0 i  0
const std::vector<std::vector<comp>> arr_CY {
	{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,-1.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,1.0), c(0.0,0.0) }
};

// 1 0 0  0 
// 0 1 0  0 
// 0 0 1  0
// 0 0 0 -1
const std::vector<std::vector<comp>> arr_CZ {
	{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(-1.0,0.0) }
};

// 1 0 0 0 
// 0 0 1 0 
// 0 1 0 0
// 0 0 0 1
const std::vector<std::vector<comp>> arr_SWAP {
	{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) }, 
	{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(1.0,0.0), c(0.0,0.0), c(0.0,0.0) },
	{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(1.0,0.0) }
};

// ===== THREE QUBIT OPERATIONS =====
// const std::vector<std::vector<comp>> TOFFOLI { ... } ;







/*
 * PARAMETRIC OPERATIONS
 */


// ===== ONE QUBIT OPEARATIONS =====

// Rotation gates
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



std::vector<std::vector<comp>> arr_ROT
	(c_type phi, c_type theta, c_type omega) {
	// Prepare exponents
	c_type sum = (phi + omega)/2.0;
	c_type dif = (phi - omega)/2.0;
	c_type the = theta/2.0;

	return {
		{ c(cos(sum)*cos(the) , -sin(sum)*cos(the)) , 
		  c(-cos(dif)*sin(the), -sin(dif)*sin(the)) },
		{ c(cos(dif)*sin(the) , -sin(dif)*sin(the)) ,
		  c(cos(sum)*cos(the) ,  sin(sum)*cos(the)) }
	};
}



// ===== TWO QUBIT OPEARATIONS =====
std::vector<std::vector<comp>> arr_CRX (c_type angle) {
	c_type phi = angle/2.0;

	return {
		{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(1.0,0.0), c(cos(phi),0.0), c(0.0,-sin(phi)) },
		{ c(0.0,0.0), c(0.0,0.0), c(0.0,-sin(phi)), c(cos(phi),0.0) }
	};
}

std::vector<std::vector<comp>> arr_CRY (c_type angle) {
	c_type phi = angle/2.0;

	return {
		{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(1.0,0.0), c(cos(phi),0.0), c(-sin(phi),0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(sin(phi),0.0), c(cos(phi),0.0) }
	};
}

std::vector<std::vector<comp>> arr_CRZ (c_type angle) {
	c_type phi = angle/2.0;

	return {
		{ c(1.0,0.0), c(0.0,0.0), c(0.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(1.0,0.0), c(0.0,0.0) },
		{ c(0.0,0.0), c(1.0,0.0), c(cos(phi),-sin(phi)), c(0.0,0.0) },
		{ c(0.0,0.0), c(0.0,0.0), c(0.0,0.0), c(cos(phi), sin(phi)) }
	};
}

// IMPLEMENT CROT.... maybe another time