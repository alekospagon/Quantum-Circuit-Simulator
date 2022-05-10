#include "circuit.h"



// =============================================== //
// ================= CIRCUIT CORE ================ //
// =============================================== //


// Handle a gate application
// void Circuit::app(const Application a);

// Run Circuit --> Updates State_vector
// void Circuit::run();

// Expectation Value of Observable
// c_type exp_value (const std::vector<std::vector<comp>> Obs);






// =========== APPLY GATE ON CIRCUIT =========== //
void Circuit::app(const Application &a) {

	// =========== FIND THE RIGHT LAYER =========== //
	unsigned int layer_index = 0;
	unsigned int max_qubit_used = 0;
	for(unsigned int i = 0; i < a.qubits.size(); ++i) {
		layer_index = max(layer_index, available_layer[a.qubits[i]]);
		max_qubit_used = max(max_qubit_used, a.qubits[i]);
	}

	// =========== QUBIT OUT OF RANGE =========== //
	if(max_qubit_used > qubits - 1) {
		std::cout << "Application Error: "
			"Qubit " << max_qubit_used << " out of Range! "
			"(0, " << qubits - 1 << ")\n";
		exit(1);
	}

	// =========== NEW CIRCUIT LAYER? =========== //
	if( layers.size() < layer_index + 1) 
		layers.push_back( std::vector<Application> {a} );
	else 
		layers[layer_index].push_back(a);


	// =========== UPDATE AVAILABLE QUBIT POSITIONS =========== //
	for(unsigned int i = 0; i < a.qubits.size(); ++i)
		available_layer[a.qubits[i]] = layer_index + 1;
}








// =========== RUN AND UPDATE STATE VECTOR =========== //
void Circuit::run(){

	// =========== CLEAR STATE VECTOR =========== //
	unsigned int SV_size = 1 << qubits;
	state_vector[0] = c(1.0, 0.0);
	for(unsigned int i = 1; i < SV_size; ++i)
		state_vector[i] = c(0.0, 0.0);


	// =========== LAYER BY LAYER =========== //
	int depth = layers.size();
	for(int i = 0; i < depth; ++i) {

		// =============================================== //
		// ============= PREPARE LAYER ARRAY ============= //
		// =============================================== //


		// =========== PREPARE PERMUTATION MAP =========== //
        std::vector<bool> allocated(qubits, false);
		std::vector<unsigned int> permutation(qubits);
        for(unsigned int map_i = 0; map_i < qubits; ++map_i)
            permutation[map_i] = map_i;

		unsigned int last_used_qubit;


		// =========== FIRST GATE =========== //

		// Layer (by definition) is never empty!
		std::vector<std::vector<comp>> layer_array = 
			layers[i][0].application_gate.array;

		last_used_qubit = layers[i][0].qubits.size();

		// update permutation and allocated qubits
		for(unsigned int qubit = 0; qubit < last_used_qubit; ++qubit) {
            permutation[qubit] = layers[i][0].qubits[qubit];
            allocated[layers[i][0].qubits[qubit]] = true;
        }


		// =========== REST GATES =========== //

		int gates = layers[i].size();
		for(int j = 1; j < gates; ++j) {
			layer_array = square_tensor_prod( 
				layers[i][j].application_gate.array, layer_array);

			unsigned int gate_size = layers[i][j].qubits.size();

			for(unsigned int qubit = 0; qubit < gate_size; ++qubit) {
				permutation[qubit + last_used_qubit] = layers[i][j].qubits[qubit];
                allocated[layers[i][j].qubits[qubit]] = true;
            }
			last_used_qubit += gate_size;    // qubits used
		}


        // =========== FILL WIRES WITH IDENTITY =========== //
		// Fill rest wires --> I @ I @ ... @ I = Big Identity Matrix
		unsigned int rest_wires_dim = 1 << (qubits - last_used_qubit);
		if(rest_wires_dim > 1)
			layer_array = square_tensor_prod(Identity_matrix(rest_wires_dim), layer_array);

        // =========== FILL PERMUTATION WITH UNALLOCATED WIRES =========== //
        for(unsigned int un_it = 0; un_it < qubits; ++un_it) {
            if(allocated[un_it] == false)
                permutation[last_used_qubit++] = un_it;
        }



		// =============================================== //
		// ============ APPLY IT ON MAPPED SV ============ //
		// =============================================== //



        // =========== MAP STATEVECTOR =========== //
        std::vector<comp> mapped_state_vector = state_vector;

        // iterate state vector and map real qubits to fake qubits
        for(unsigned int pos = 0; pos < SV_size; ++pos) {

            unsigned int mapped_pos = 0;
            for(unsigned int fake = 0; fake < qubits; ++fake) {
                unsigned int real = permutation[fake];
                // replace fake qubit with the real one
                unsigned int real_bit = (pos >> real) & 1;
                mapped_pos |= (real_bit << fake);
            }
            mapped_state_vector[mapped_pos] = state_vector[pos];
        }

		// =========== APPLY LAYER =========== //
		mapped_state_vector = Array_dot_state(layer_array, mapped_state_vector);

        // =========== UNDO MAPPING OF STATEVECTOR =========== //

        
        // iterate state vector and map real qubits to fake qubits
        for(unsigned int pos = 0; pos < SV_size; ++pos) {

            unsigned int mapped_pos = 0;
            for (unsigned int fake = 0; fake < qubits; ++fake) {
                unsigned int real = permutation[fake];
                unsigned int real_bit = (pos >> real) & 1;
                mapped_pos |= (real_bit << fake);
            }
            // reverse action
            state_vector[pos] = mapped_state_vector[mapped_pos];
        }


	} // circuit depth iterator end
}





// Takes A and list of qubits A is applied onto
// Returns:   <A> = <Psi|A|Psi>
c_type Circuit::exp_value (
	const std::vector<std::vector<comp>> &Obs, 
	const std::vector<unsigned int> &qubs) 
{
	// =========== COMPATIBILITY CHECKS =========== //
	if(Obs.size() != (1 << qubs.size())) {
		std::cout << "Expectation Value Error: "
			"Observable matrix size doesn't match qubits given\n";
		exit(1);
	}

	// =========== QUBIT CHECKS =========== //
	std::vector<bool> qubit_used(MAX_QUBITS, false);
	for(unsigned int i = 0; i < qubs.size(); ++i) {
		// Check range
		if(qubs[i] > qubits - 1) {
			std::cout << "Expectation Value Error: "
				"Qubit " << qubs[i] << " out of Range "
				"(0," << qubits-1 << ")\n";
			exit(1);
		}
		// Check duplicates
		if(qubit_used[qubs[i]] == true) {
			std::cout << "Expectation Value Error: "
				"Dulpicate Qubit Detected!\n";
			exit(1);
		}
		qubit_used[qubs[i]] = true;
	}


	// =========== PREPARE PERMUTATION MAP =========== //
    std::vector<bool> allocated(qubits, false);
	std::vector<unsigned int> permutation(qubits);
    for(unsigned int map_i = 0; map_i < qubits; ++map_i) {
        permutation[map_i] = map_i;
    }



	// =========== FILL GATE & PERMUTE QUBITS =========== //
	std::vector<std::vector<comp>> filled_gate = Obs;
	unsigned int qubits_used = qubs.size();

	// update permutation and allocated qubits
	for(unsigned int qubit = 0; qubit < qubits_used; ++qubit) {
        permutation[qubit] = qubs[qubit];
        allocated[qubs[qubit]] = true;
    }


    // =========== FILL WIRES WITH IDENTITY =========== //
	// Fill rest wires --> I @ I @ ... @ I = Big Identity Matrix
	unsigned int rest_wires_dim = 1 << (qubits - qubits_used);
	if(rest_wires_dim > 1)
		filled_gate = square_tensor_prod(Identity_matrix(rest_wires_dim), Obs);

    // =========== FILL PERMUTATION WITH UNALLOCATED WIRES =========== //
    for(unsigned int un_it = 0; un_it < qubits; ++un_it) {
        if(allocated[un_it] == false)
            permutation[qubits_used++] = un_it;
    }

	
    // =========== MAP STATEVECTOR =========== //
    std::vector<comp> mapped_state_vector = state_vector;

    // iterate state vector and map real qubits to fake qubits
    unsigned int SV_size = 1 << qubits;
    for(unsigned int pos = 0; pos < SV_size; ++pos) {

        unsigned int mapped_pos = 0;
        for(unsigned int fake = 0; fake < qubits; ++fake) {
            unsigned int real = permutation[fake];
            // replace fake qubit with the real one
            unsigned int real_bit = (pos >> real) & 1;
            mapped_pos |= (real_bit << fake);
        }
        mapped_state_vector[mapped_pos] = state_vector[pos];
    }

	c_type exp_val = expectation_value(filled_gate, mapped_state_vector);

	return exp_val;
}