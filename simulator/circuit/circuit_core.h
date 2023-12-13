#ifndef __QUANTUM_CIRCUIT_CORE__
#define __QUANTUM_CIRCUIT_CORE__


#include <iostream>	// input/output
#include <vector>	// all my arrays
#include <map>		// dictionary for measure();
#include <bitset>   // convert integer to bin_string
#include <random>	// discrete_distribution
#include <math.h>	// floor
#include <unordered_map>	// application SN --> actual gate
#include <tuple>	// (Layer, Layer_number)


#include "../math/math.h"
#include "circuit_application.h"



#define MAX_QUBITS 10


#define max(a,b) ((a)>(b)?(a):(b))


class Circuit {
	public:
		// Core
		unsigned int qubits;
		std::vector<unsigned int> available_layer; // squeeze gates
		std::vector< std::vector<Application> > layers; // layout in layers
		std::vector<comp> state_vector;
		bool executed; // run on every change only!


		// Adjoint Differentiation. keep track of gate's Serial Number.
		// SN -> <layer_ID, Pos_in_layer>
		std::unordered_map<unsigned int, 
			std::tuple<unsigned int, unsigned int>> app_id;
		unsigned int applications;
		unsigned int parametric_gates;


		// Constructor
		Circuit(unsigned int q);





		// =========== circuit_core.h =========== //
		void app (Application &a);
		void run();
		c_type exp_value (const SqMatrix &Obs, const std::vector<unsigned int> &qubs);

		// returns Nabla <E> for an observable E
		std::vector<c_type> exp_value_grad(const SqMatrix &Obs, 
			const std::vector<unsigned int> &qubs);



		// =========== OPTIMIZATION =========== //
		std::vector<comp> grad();





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
		// void ROT(unsigned int qubit, c_type phi, c_type theta, c_type omega);
		void CRX(unsigned int control, unsigned int target, c_type angle);
		void CRY(unsigned int control, unsigned int target, c_type angle);
		void CRZ(unsigned int control, unsigned int target, c_type angle);
		void CP(unsigned int control, unsigned int target, c_type angle);
		void TOFFOLI(unsigned int control1, unsigned int control2, unsigned int target);
};




// Constructor
Circuit::Circuit(unsigned int q) {
	#ifdef __SAFE_LIBRARY__
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
	#endif


	

	state_vector = std::vector<comp> ( 1<<q, c(0.0, 0.0) );
	state_vector[0] = c(1.0, 0.0);
	qubits = q;
	available_layer = std::vector<unsigned int> (q,0);
	applications = 0;
	parametric_gates = 0;
	executed = false;
};








#endif
