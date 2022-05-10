#include "circuit.h"

// =============================================== //
// ============== CIRCUIT STATISTICS ============= //
// =============================================== //





void Circuit::print_state_vector(bool integer = false) {

    std::cout << "============ Printing State Vector ============ \n";

	unsigned int dim = state_vector.size();
	for(unsigned int base_state = 0; base_state < dim; ++base_state){

		// Print base state in binary
		if(integer == false) {
	        std::string filled_base = 
	            std::bitset< MAX_QUBITS >(base_state).to_string();
	        std::string base_string(filled_base, MAX_QUBITS - qubits, qubits);

	        std::cout << "|" << base_string << ">\t" << "= ";
	    }
	    // Print base state as integer
	    else {
	    	std::cout << "|" << base_state << ">\t" << "= ";
	    }
		print_comp(state_vector[base_state]);
		std::cout << "\n";
	}
}




// Debug info
void Circuit::print_circuit() {
	std::cout << "============= Printing Circuit ============= \n";

	for(unsigned int i = 0; i < layers.size(); ++i) {
		std::cout << "===== Printing Layer: " << i << " =====\n";

		for(unsigned int j = 0; j < layers[i].size(); ++j){
			layers[i][j].application_gate.print_gate();

			std::cout << "Applied on Qubit(s): ";
			for(unsigned int k = 0; k < layers[i][j].qubits.size(); ++k) 
				std::cout << layers[i][j].qubits[k] << " ";
			std::cout << "\n";
		}
	}

}






void Circuit::print_probabilities(bool integer = false, bool cent = false) {
    std::cout << "============ Printing probabilities ============ \n";

	unsigned int dim = state_vector.size();
	for(unsigned int base_state = 0; base_state < dim; ++base_state){

		// Print base state in binary
		if(integer == false) {
	        std::string filled_base = 
	            std::bitset< MAX_QUBITS >(base_state).to_string();
	        std::string base_string(filled_base, MAX_QUBITS - qubits, qubits);

	        std::cout << "P(|" << base_string << ">)\t" << "= ";
	    }
	    // Print base state as integer
	    else {
	    	std::cout << "P(|" << base_state << ">)\t" << "= ";
	    }
	    comp z = state_vector[base_state];
	    // |z|^2 = a^2 + b^2
		c_type prob = z.real * z.real + z.imag * z.imag;
		if(cent == false)
			std::cout << prob << "\n";
		else
			std::cout << prob*100 << "%\n";
	}

}




void Circuit::measure(unsigned int shots){

	std::cout << "============ Running Experiment ============ \n";
	std::cout << "Shots: " << shots << "\n";

    // Setup the random bits
    std::random_device rd;	// Random Device
    std::mt19937_64 gen(rd());	// Mersenne Twister pseudo-random generator

    // Set Distribution Weights
	unsigned int SPACE_SIZE = 1 << qubits;
	std::vector<int> weights (SPACE_SIZE);
	for(unsigned int i = 0; i < SPACE_SIZE; ++i) {
		comp z = state_vector[i];
		c_type prob = z.real * z.real + z.imag * z.imag;
		weights[i] = floor(prob*1000000);	// make integers
	}

    // Create the distribution with those weights
    std::discrete_distribution<> d(weights.begin(), weights.end());

    // Run experiment
    std::map<int, int> counts;
    for(unsigned int shot = 0; shot < shots; ++shot) {
    	++counts[d(gen)];
    }

    // Print measurements
    for(auto p : counts) {
    	// Make base_state in binary
		std::string filled_base = 
			std::bitset< MAX_QUBITS >(p.first).to_string();
		std::string base_string(filled_base, MAX_QUBITS - qubits, qubits);
		// Print result
		std::cout << "#(|" << base_string << ">)\t" << "= " 
			<< p.second << "\n";
    }
}







void Circuit::full_analysis() {
	return ;
}