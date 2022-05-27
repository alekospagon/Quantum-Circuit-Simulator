#include "../library.h"
#include <math.h>
#include <random>
#include <time.h>


// Quantum Fourier Transfrom Adder:
// https://arxiv.org/pdf/1411.5949.pdf
void QFT(Circuit &c, int qubs) {

	// Hadamard every qubit
	for(int i = 0; i < qubs; ++i) {
		c.H(i);
	}

	for(int i = 0; i < qubs-1; ++i) {
		// controlled phase gates
		for(int j = i+1; j < qubs; ++j) {
			c_type angle = pi / pow(2, j-i);
			c.CP(j, i, angle);
		}
	}

	for(int i = 0; i < qubs/2; ++i)
		c.SWAP(i, qubs-1-i);
}



// Inverse QFT
void IQFT(Circuit &c, int qubs) {

	for(int i = 0; i < qubs/2; ++i)
		c.SWAP(i, qubs-1-i);

	// for every qubit
	for(int i = qubs-2; i >= 0; --i) {
		// controlled phase gates
		for(int j = qubs-1; j > i; --j) {
			c_type angle = pi / pow(2, j-i);
			c.CP(j, i, -angle);
		}
	}

	// Hadamard every qubit
	for(int i = 0; i < qubs; ++i) {
		c.H(i);
	}
}



void Addition(Circuit &c, int qubs) {

	// for every qubit in low register
	for(int i = 0; i < qubs; ++i) {
		// for some qubits in the high register
		for(int j = 0; j < i+1; ++j) {
			c_type angle = pi / pow(2,i-j);
			c.CP(qubs + j, qubs-1-i, angle);
		}
	}
}



int main() 
{
	Circuit c(6);

	// Keep two registers --> xxxyyy

	// put number 1 on low register
	// 000 | 001
	c.X(1);

	// put number 2 on high register
	// 001 | 001
	c.X(3);



	// QFT first register
	QFT (c, 3);

	// 010 | 011
	Addition(c, 3);

	// Inverse QFT
	IQFT(c, 3);



	c.run();
	c.measure(100000);


	return 0;
}
