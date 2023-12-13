#include "../simulator.h"


#define N_QUBITS 5	// 4+1 ancillary
#define DEPTH	5
#define MY_EPOCHS 2500

SqMatrix Y = matrix_Y;
SqMatrix X = matrix_X;
SqMatrix Z = matrix_Z;
SqMatrix I = matrix_I;

/* 
https://qiskit.org/documentation/nature/tutorials/01_electronic_structure.html
*/


SqMatrix Hamiltonian = 
  0.04523279994605781 * Y%Y%Y%Y
+ 0.04523279994605781 * X%X%Y%Y
+ 0.04523279994605781 * Y%Y%X%X
+ 0.04523279994605781 * X%X%X%X
- 0.8105479805373281  * I%I%I%I
- 0.22575349222402358 * Z%I%I%I
+ 0.17218393261915543 * I%Z%I%I
+ 0.12091263261776633 * Z%Z%I%I
- 0.22575349222402358 * I%I%Z%I
+ 0.17464343068300436 * Z%I%Z%I
+ 0.16614543256382414 * I%Z%Z%I
+ 0.17218393261915543 * I%I%I%Z
+ 0.16614543256382414 * Z%I%I%Z
+ 0.16892753870087904 * I%Z%I%Z
+ 0.12091263261776633 * I%I%Z%Z;


// Param Layer / Entang Layer...
// --RY--o-----X----RY--o-----X--------
// --RY--X-o---|----RY--X-o---|---etc--
// --RX----X-o-|----RX----X-o-|--------
// --RY------X-o----RY------X-o--------

void make_circuit(Circuit &c, std::vector<c_type> weights) {

	for(unsigned int i = 0; i < DEPTH; ++i) {

		// Parameter Layer
		for(unsigned int j = 0; j < N_QUBITS; ++j)
			c.RY(j, weights[i*DEPTH + j]);

		// Entanglement Layer
		for(unsigned int j = 0; j < N_QUBITS-1; ++j)
			c.CZ(j, j+1);

		c.CZ(N_QUBITS-1, 0);
	}

}




int main()
{
	std::vector<c_type> weights = random_weights(N_QUBITS * DEPTH);

	// optimize
	// qubits=3, layout, Observable, Obs_qubits, initial weights, epochs
	weights = ADAM(N_QUBITS, make_circuit, Hamiltonian, {0,1,2,3}, weights , MY_EPOCHS);


	return 0;
}
