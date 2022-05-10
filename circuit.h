#ifndef __QUANTUM_CIRCUIT__
#define __QUANTUM_CIRCUIT__ 420


#include <iostream>	// input/output
#include <vector>	// all my arrays
#include <map>		// dictionary for measure();
#include <bitset>   // convert integer to bin_string
#include <random>	// discrete_distribution
#include <math.h>	// floor

#include "parameters.h"
#include "algebra.h"
#include "comp.h"
#include "gates.h"
#include "application.h"




#define max(a,b) ((a)>(b)?(a):(b))


class Circuit {
	public:
		unsigned int qubits;
		// last layer that this qubit is available
		std::vector<unsigned int> available_layer;
		// fill layers with gate applications
		std::vector< std::vector<Application> > layers;

		std::vector<comp> state_vector;

		// Constructor
		Circuit(unsigned int q);


		// =========== circuit_core.h =========== //
		void app (const Application &a);
		void run();
		c_type exp_value (
			const std::vector<std::vector<comp>> &Obs,
			const std::vector<unsigned int> &qubs);


		// ======== circuit_statistics.h ======== //
		void print_circuit();
		void print_state_vector(bool integer);
		void print_probabilities(bool integer, bool cent);
		void measure(unsigned int shots);
		void full_analysis();


		// ========== circuit_library.h ========= //
		// NON-PARAMETRIC GATES
		void I(unsigned int qubit);
		void H(unsigned int qubit);
		void X(unsigned int qubit);
		void Y(unsigned int qubit);
		void Z(unsigned int qubit);
		void S(unsigned int qubit);
		void T(unsigned int qubit);
		void CNOT(unsigned int control, unsigned int target);
		void CY(unsigned int control, unsigned int target);
		void CZ(unsigned int control, unsigned int target);
		void SWAP(unsigned int qubit1, unsigned int qubit2);
		// PARAMETRIC GATES
		void RX(unsigned int qubit, c_type angle);
		void RY(unsigned int qubit, c_type angle);
		void RZ(unsigned int qubit, c_type angle);
		void P (unsigned int qubit, c_type angle);
		void ROT(unsigned int qubit, c_type phi, c_type theta, c_type omega);
		void CRX(unsigned int control, unsigned int target, c_type angle);
		void CRY(unsigned int control, unsigned int target, c_type angle);
		void CRZ(unsigned int control, unsigned int target, c_type angle);
		void TOFFOLI(unsigned int control1, unsigned int control2, unsigned int target);
};




// Constructor
Circuit::Circuit(unsigned int q) {
	// check qubit range
	if(q == 0) {
		std::cout << "Zero Qubits Given!\n";
		exit(1);
	}
	if(q > MAX_QUBITS) {
		std::cout << "More than " << MAX_QUBITS
			<< " Qubits! You are a mad man....\n";
		exit(1);
	}
	
	// copy data
	state_vector = std::vector<comp> ( 1<<q, c(0.0, 0.0) );
	state_vector[0] = c(1.0, 0.0);
	qubits = q;
	available_layer = std::vector<unsigned int> (q,0);
};









#endif
