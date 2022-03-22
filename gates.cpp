#include <math.h>
#include "comp.h"


/*
 * NON - PARAMETRIC OPERATIONS
 */


// ===== ONE QUBIT OPEARATIONS =====
// 1 0
// 0 1
void I(comp arr[2][2]) {
	arr[0][0] = c(1.0,0.0);
	arr[0][1] = c(0.0,0.0);
	arr[1][0] = c(0.0,0.0);
	arr[1][1] = c(1.0,0.0);
}

// 1		1  1
// sqrt(2)	1 -1
void H(comp arr[2][2]) {
	arr[0][0] = c(1.0/sqrt(2),0.0);
	arr[0][1] = c(1.0/sqrt(2),0.0);
	arr[1][0] = c(1.0/sqrt(2),0.0);
	arr[1][1] = c(-1.0/sqrt(2),0.0);
}

// Pauli Gates
// 0 1
// 1 0
void X(comp arr[2][2]) {
	arr[0][0] = c(0.0,0.0);
	arr[0][1] = c(1.0,0.0);
	arr[1][0] = c(1.0,0.0);
	arr[1][1] = c(0.0,0.0);
}

// 0 -i
// i  0
void Y(comp arr[2][2]) {
	arr[0][0] = c(0.0,0.0);
	arr[0][1] = c(0.0,-1.0);
	arr[1][0] = c(0.0,1.0);
	arr[1][1] = c(0.0,0.0);
}

// 1  0
// 0 -1
void Z(comp arr[2][2]) {
	arr[0][0] = c(1.0,0.0);
	arr[0][1] = c(0.0,0.0);
	arr[1][0] = c(0.0,0.0);
	arr[1][1] = c(-1.0,0.0);
}


// ===== TWO QUBIT OPERATIONS =====
// 1 0 0 0 
// 0 1 0 0 
// 0 0 0 1
// 0 0 1 0
void CNOT(comp arr[4][4]) {
	arr[0][0] = c(1.0,0.0);
	arr[0][1] = c(0.0,0.0);
	arr[0][2] = c(0.0,0.0);
	arr[0][3] = c(0.0,0.0);
	arr[1][0] = c(0.0,0.0);
	arr[1][1] = c(1.0,0.0);
	arr[1][2] = c(0.0,0.0);
	arr[1][3] = c(0.0,0.0);
	arr[2][0] = c(0.0,0.0);
	arr[2][1] = c(0.0,0.0);
	arr[2][2] = c(0.0,0.0);
	arr[2][3] = c(1.0,0.0);
	arr[3][0] = c(0.0,0.0);
	arr[3][1] = c(0.0,0.0);
	arr[3][2] = c(1.0,0.0);
	arr[3][3] = c(0.0,0.0);
}

// 1 0 0  0 
// 0 1 0  0 
// 0 0 0 -i
// 0 0 i  0
void CY(comp arr[4][4]) {
	arr[0][0] = c(1.0,0.0);
	arr[0][1] = c(0.0,0.0);
	arr[0][2] = c(0.0,0.0);
	arr[0][3] = c(0.0,0.0);
	arr[1][0] = c(0.0,0.0);
	arr[1][1] = c(1.0,0.0);
	arr[1][2] = c(0.0,0.0);
	arr[1][3] = c(0.0,0.0);
	arr[2][0] = c(0.0,0.0);
	arr[2][1] = c(0.0,0.0);
	arr[2][2] = c(0.0,0.0);
	arr[2][3] = c(0.0,-1.0);
	arr[3][0] = c(0.0,0.0);
	arr[3][1] = c(0.0,0.0);
	arr[3][2] = c(0.0,1.0);
	arr[3][3] = c(0.0,0.0);
}

// 1 0 0  0 
// 0 1 0  0 
// 0 0 1  0
// 0 0 0 -1
void CZ(comp arr[4][4]) {
	arr[0][0] = c(1.0,0.0);
	arr[0][1] = c(0.0,0.0);
	arr[0][2] = c(0.0,0.0);
	arr[0][3] = c(0.0,0.0);
	arr[1][0] = c(0.0,0.0);
	arr[1][1] = c(1.0,0.0);
	arr[1][2] = c(0.0,0.0);
	arr[1][3] = c(0.0,0.0);
	arr[2][0] = c(0.0,0.0);
	arr[2][1] = c(0.0,0.0);
	arr[2][2] = c(1.0,0.0);
	arr[2][3] = c(0.0,0.0);
	arr[3][0] = c(0.0,0.0);
	arr[3][1] = c(0.0,0.0);
	arr[3][2] = c(0.0,0.0);
	arr[3][3] = c(-1.0,0.0);
}

// 1 0 0 0 
// 0 0 1 0 
// 0 1 0 0
// 0 0 0 1
void SWAP(comp arr[4][4]) {
	arr[0][0] = c(1.0,0.0);
	arr[0][1] = c(0.0,0.0);
	arr[0][2] = c(0.0,0.0);
	arr[0][3] = c(0.0,0.0);
	arr[1][0] = c(0.0,0.0);
	arr[1][1] = c(0.0,0.0);
	arr[1][2] = c(1.0,0.0);
	arr[1][3] = c(0.0,0.0);
	arr[2][0] = c(0.0,0.0);
	arr[2][1] = c(1.0,0.0);
	arr[2][2] = c(0.0,0.0);
	arr[2][3] = c(0.0,0.0);
	arr[3][0] = c(0.0,0.0);
	arr[3][1] = c(0.0,0.0);
	arr[3][2] = c(0.0,0.0);
	arr[3][3] = c(1.0,0.0);
};

// ===== THREE QUBIT OPERATIONS =====
void TOFFOLI(comp arr[8][8]) {
	// empty
	for(int i = 0; i<8; i++)
		for(int j = 0; j<8; j++)
			arr[i][j] = c(0.0,0.0);
	// fill with ones
	arr[0][0] = c(1.0,0.0);
	arr[1][1] = c(1.0,0.0);
	arr[2][2] = c(1.0,0.0);
	arr[3][3] = c(1.0,0.0);
	arr[4][4] = c(1.0,0.0);
	arr[5][5] = c(1.0,0.0);
	arr[6][6] = c(1.0,0.0);
	arr[7][8] = c(1.0,0.0);	// NOT OPERATION
	arr[8][7] = c(1.0,0.0); // NOT OPERATION
};




/*
 * PARAMETRIC OPERATIONS
 */


// ===== ONE QUBIT OPEARATIONS =====

// Rotation gates
void RX(comp arr[2][2], double angle) {
	double phi = angle/2.0;
	arr[0][0] = c(cos(phi),0.0);
	arr[0][1] = c(0.0,-sin(phi));
	arr[1][0] = c(0.0,-sin(phi));
	arr[1][1] = c(cos(phi),0.0);
}

void RY(comp arr[2][2], double angle) {
	double phi = angle/2.0;
	arr[0][0] = c(cos(phi),0.0);
	arr[0][1] = c(-sin(phi),0.0);
	arr[1][0] = c(sin(phi),0.0);
	arr[1][1] = c(cos(phi),0.0);
}


void RZ(comp arr[2][2], double angle) {
	double phi = angle/2.0;
	arr[0][0] = c(cos(phi),-sin(phi));
	arr[0][1] = c(0.0,0.0);
	arr[1][0] = c(0.0,0.0);
	arr[1][1] = c(cos(phi),sin(phi));
}


void ROT(comp arr[2][2], double phi, double theta, double omega) {
	// Prepare exponents
	double sum = (phi + omega)/2.0;
	double dif = (phi - omega)/2.0;
	double the = theta/2.0;

	arr[0][0] = c(cos(sum)*cos(the) , -sin(sum)*cos(the));
	arr[0][1] = c(-cos(dif)*sin(the), -sin(dif)*sin(the));
	arr[1][0] = c(cos(dif)*sin(the) , -sin(dif)*sin(the));
	arr[1][1] = c(cos(sum)*cos(the) ,  sin(sum)*cos(the));
}



// ===== TWO QUBIT OPEARATIONS =====
void CRX(comp arr[4][4], double angle) {
	double phi = angle/2.0;
	arr[0][0] = c(1.0,0.0);
	arr[0][1] = c(0.0,0.0);
	arr[0][2] = c(0.0,0.0);
	arr[0][3] = c(0.0,0.0);
	arr[1][0] = c(0.0,0.0);
	arr[1][1] = c(0.0,0.0);
	arr[1][2] = c(1.0,0.0);
	arr[1][3] = c(0.0,0.0);
	arr[2][0] = c(0.0,0.0);
	arr[2][1] = c(1.0,0.0);
	arr[2][2] = c(cos(phi),0.0);
	arr[2][3] = c(0.0,-sin(phi));
	arr[3][0] = c(0.0,0.0);
	arr[3][1] = c(0.0,0.0);
	arr[3][2] = c(0.0,-sin(phi));
	arr[3][3] = c(cos(phi),0.0);
}

void CRY(comp arr[4][4], double angle) {
	double phi = angle/2.0;
	arr[0][0] = c(1.0,0.0);
	arr[0][1] = c(0.0,0.0);
	arr[0][2] = c(0.0,0.0);
	arr[0][3] = c(0.0,0.0);
	arr[1][0] = c(0.0,0.0);
	arr[1][1] = c(0.0,0.0);
	arr[1][2] = c(1.0,0.0);
	arr[1][3] = c(0.0,0.0);
	arr[2][0] = c(0.0,0.0);
	arr[2][1] = c(1.0,0.0);
	arr[2][2] = c(cos(phi),0.0);
	arr[2][3] = c(-sin(phi),0.0);
	arr[3][0] = c(0.0,0.0);
	arr[3][1] = c(0.0,0.0);
	arr[3][2] = c(sin(phi),0.0);
	arr[3][3] = c(cos(phi),0.0);
}

void CRZ(comp arr[4][4], double angle) {
	double phi = angle/2.0;
	arr[0][0] = c(1.0,0.0);
	arr[0][1] = c(0.0,0.0);
	arr[0][2] = c(0.0,0.0);
	arr[0][3] = c(0.0,0.0);
	arr[1][0] = c(0.0,0.0);
	arr[1][1] = c(0.0,0.0);
	arr[1][2] = c(1.0,0.0);
	arr[1][3] = c(0.0,0.0);
	arr[2][0] = c(0.0,0.0);
	arr[2][1] = c(1.0,0.0);
	arr[2][2] = c(cos(phi),-sin(phi));
	arr[2][3] = c(0.0,0.0);
	arr[3][0] = c(0.0,0.0);
	arr[3][1] = c(0.0,0.0);
	arr[3][2] = c(0.0,0.0);
	arr[3][3] = c(cos(phi), sin(phi));
}

// IMPLEMENT CROT.... maybe another time


int main()
{

	/* PRINT ARRAYS --> DEBUG!

	comp res[2][2]; 

	I(res);
	printf("I gate:\n");
	for(int i = 0; i<2; i++) {
		for(int j = 0; j<2; j++)
			print_comp(res[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("H gate:\n");
	H(res);
	for(int i = 0; i<2; i++) {
		for(int j = 0; j<2; j++)
			print_comp(res[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("X gate:\n");
	X(res);
	for(int i = 0; i<2; i++) {
		for(int j = 0; j<2; j++)
			print_comp(res[i][j]);
		printf("\n");
	}
	printf("\n");
	
	printf("Y gate:\n");
	Y(res);
	for(int i = 0; i<2; i++) {
		for(int j = 0; j<2; j++)
			print_comp(res[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("Z gate:\n");
	Z(res);
	for(int i = 0; i<2; i++) {
		for(int j = 0; j<2; j++)
			print_comp(res[i][j]);
		printf("\n");
	}	
	printf("\n");

	printf("RX gate:\n");
	RX(res, M_PI/2.0);
	for(int i = 0; i<2; i++) {
		for(int j = 0; j<2; j++)
			print_comp(res[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("RY gate:\n");
	RY(res, M_PI/2.0);
	for(int i = 0; i<2; i++) {
		for(int j = 0; j<2; j++)
			print_comp(res[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("RZ gate:\n");
	RZ(res, M_PI/2.0);
	for(int i = 0; i<2; i++) {
		for(int j = 0; j<2; j++)
			print_comp(res[i][j]);
		printf("\n");
	}
	printf("\n");

	*/

	comp res[2][2]; 
	for(int iter = 0; iter<1000000; iter++)
	{
		// fill and print
		for(int i = 0; i<2; i++)
			for(int j = 0; j<2; j++)
				print_comp(res[i][j]);
		printf("\n");
	}
	

	return 0;
}




























