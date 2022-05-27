#include "circuit.h"



// =============================================== //
// ================= CIRCUIT CORE ================ //
// =============================================== //


// =========== APPLY GATE ON CIRCUIT =========== //
void Circuit::app(Application &a) {

	unsigned int pos_in_layer;

	// =========== FIND THE RIGHT LAYER =========== //
	unsigned int layer_index = 0;
	unsigned int max_qubit_used = 0;
	for(unsigned int i = 0; i < a.qubits.size(); ++i) {
		layer_index = max(layer_index, available_layer[a.qubits[i]]);
		max_qubit_used = max(max_qubit_used, a.qubits[i]);
	}


#ifdef __SAFE_LIBRARY__
	// =========== QUBIT OUT OF RANGE =========== //
	if(max_qubit_used > qubits - 1) {
		std::cout << "Application Error: "
			"Qubit " << max_qubit_used << " out of Range! "
			"(0, " << qubits - 1 << ")\n";
		exit(1);
	}
#endif


	// =========== NEW CIRCUIT LAYER? =========== //
	if( layers.size() < layer_index + 1) {
		layers.push_back( std::vector<Application> {a} );
		pos_in_layer = 0;
	}
	else {
		layers[layer_index].push_back(a);
		pos_in_layer = layers[layer_index].size() - 1;
	}


	// =========== UPDATE AVAILABLE QUBIT POSITIONS =========== //
	for(unsigned int i = 0; i < a.qubits.size(); ++i)
		available_layer[a.qubits[i]] = layer_index + 1;


	// map application's Serial Number to its place on the circuit
	app_id[applications++] = std::make_tuple(layer_index, pos_in_layer);

	executed = false;
}









// algorithm used by many functions
// apply gate on State_Vector
// given a permutation map for the qubits
void apply_on_map(
		std::vector<comp> &SV,
		std::vector<unsigned int> &permutation,
		unsigned int qubits,
		SqMatrix &gate)
{
	// =========== MAP STATEVECTOR =========== //
	std::vector<comp> mapped_state_vector = SV;

	// iterate state vector and map fake qubits to real qubits
	unsigned int SV_size = 1 << qubits;
	for(unsigned int pos = 0; pos < SV_size; ++pos) {

		unsigned int mapped_pos = 0;
		for(unsigned int fake = 0; fake < qubits; ++fake) {
			unsigned int real = permutation[fake];
			// replace fake qubit with the real one
			unsigned int real_bit = (pos >> real) & 1;
			mapped_pos |= (real_bit << fake);
		}
		mapped_state_vector[mapped_pos] = SV[pos];
	}

	// =========== APPLY LAYER =========== //
	mapped_state_vector = 
		Sparse_Array_dot_state(gate, mapped_state_vector);

	// =========== UNDO MAPPING OF STATEVECTOR =========== //
	for(unsigned int pos = 0; pos < SV_size; ++pos) {

		unsigned int mapped_pos = 0;
		for (unsigned int fake = 0; fake < qubits; ++fake) {
			unsigned int real = permutation[fake];
			unsigned int real_bit = (pos >> real) & 1;
			mapped_pos |= (real_bit << fake);
		}
		// reverse map
		SV[pos] = mapped_state_vector[mapped_pos];
	}
}





// returns qubits used for gates
template <typename T> //apps or app_difs 
void make_permutation(
		std::vector<unsigned int> & permutation,
		unsigned int qubits,
		const std::vector<T> & layer) 
{
	std::vector<bool> allocated(qubits, false);

	// PREMARE MAP AND PARAMETERS
	int gates = layer.size();
	unsigned int last_used_qubit = 0;

	// ITERATE LAYER OF GATES
	for(int i = 0; i < gates; ++i) {

		unsigned int gate_size = layer[i].qubits.size();

		// ITERATE GATE
		for(unsigned int qubit = 0; qubit < gate_size; ++qubit) {
			permutation[qubit + last_used_qubit] = layer[i].qubits[qubit];
			allocated[layer[i].qubits[qubit]] = true;
		}
		last_used_qubit += gate_size; // qubits used on this gate
	}

	// =========== FILL PERMUTATION WITH UNALLOCATED WIRES =========== //
	for(unsigned int un_it = 0; un_it < qubits; ++un_it) {
		if(allocated[un_it] == false)
			permutation[last_used_qubit++] = un_it;
	}
}




// Tensor product of many gates
void fill_gate(
		SqMatrix & layer_array,
		const std::vector<Application> & layer) 
{
	// Layer (by definition) is never empty!
	layer_array = layer[0].application_gate;

	// fill with gates given
	int gates = layer.size();
	for(int i = 1; i < gates; ++i) {
		layer_array = layer[i].application_gate % layer_array;
	}
}


// Tensor product of many gates + fill with Identities
void full_fill_gate(
		SqMatrix & layer_array,
		const std::vector<Application> & layer,
		unsigned int qubits )
{
	// Layer (by definition) is never empty!
	layer_array = layer[0].application_gate;

	// fill with gates given
	int gates = layer.size();
	for(int i = 1; i < gates; ++i) {
		layer_array = layer[i].application_gate % layer_array;
	}

	unsigned int rest_wires_dim = (1<<qubits) / layer_array.dims();

	SqMatrix big_id = Identity_matrix(rest_wires_dim);

	layer_array = big_id % layer_array;
}





// =========== RUN AND UPDATE STATE VECTOR =========== //
void Circuit::run(){

	// don't run the same circuit twice
	if(executed) return;

	// =========== CLEAR STATE VECTOR =========== //
	unsigned int SV_size = 1 << qubits;
	state_vector[0] = c(1.0, 0.0);
	for(unsigned int i = 1; i < SV_size; ++i)
		state_vector[i] = c(0.0, 0.0);


	// =========== LAYER BY LAYER =========== //
	int depth = layers.size();
	for(int i = 0; i < depth; ++i) {

		std::vector<unsigned int> permutation(qubits);

		make_permutation(permutation, qubits, layers[i]);
		SqMatrix layer_array(0);	// init as emptys
		fill_gate(layer_array, layers[i]);
		apply_on_map(state_vector, permutation, qubits, layer_array);
	}

	executed = true;
}





// Takes A and list of qubits A is applied onto
// Returns:   <A> = <Psi|A|Psi>
c_type Circuit::exp_value (
		const SqMatrix &Obs, 
		const std::vector<unsigned int> &qubs) 
{
#ifdef __SAFE_LIBRARY__
	// =========== COMPATIBILITY CHECKS =========== //
	unsigned int qub_len = 1 << qubs.size();
	if(Obs.dims() != qub_len) {
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
#endif

	run();

	// Like run(); only one layer containing Obs gate
	std::vector<Application> layer = {Application(Obs, empty, qubs)};

	std::vector<unsigned int> permutation(qubits);

	make_permutation(permutation, qubits, layer);

	SqMatrix layer_array(0);	// empty
	full_fill_gate(layer_array, layer, qubits);

	// Don't call apply_on_map since we don't need to unmap
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

	c_type exp_val = expectation_value(layer_array, mapped_state_vector);

	return exp_val;
}


















// https://arxiv.org/pdf/2009.02823.pdf
// returns Nabla <E> for an observable E
std::vector<c_type> Circuit::exp_value_grad(
		const SqMatrix &Obs,
		const std::vector<unsigned int> &qubs)
{

#ifdef __SAFE_LIBRARY__
	// =========== COMPATIBILITY CHECKS =========== //
	unsigned int qub_len = 1 << qubs.size();
	if(Obs.dims() != qub_len) {
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
#endif


	run();


	// result vector --> Nabla <E>
	std::vector<c_type> grad (parametric_gates);
	unsigned int param = parametric_gates - 1;

	// Find <E>
	// YOU MUST RUN THE CIRCUIT FIRST!
	run();
	std::vector<comp> phi    = state_vector;
	std::vector<comp> lambda = state_vector;


	// ============================================== //
	// ======= |Lambda> = Observable |Lambda> ======= //
	// ============================================== //

	// A layer containing only Obs array
	std::vector<Application> layer = {Application(Obs, empty, qubs)};
	std::vector<unsigned int> perm(qubits);

	// PERMUTE
	make_permutation(perm, qubits, layer);
	// MAKE GATE
	SqMatrix filled_gate(0);	// init as empty
	fill_gate(filled_gate, layer);
	// APPLY GATE ON GIVEN STATEVECTOR WITH GIVEN MAP
	apply_on_map(lambda, perm, qubits, filled_gate);




	// ============================================== //
	// ========== ITERATE GATES IN REVERSE ========== //
	// ============================================== //


	// iterate backwards all gates
	for(int app = applications-1; app >= 0; --app) {

		// look up in hash --> find gate in circuit
		std::tuple coordinates = app_id[app];
		Application gate = 
			layers[std::get<0>(coordinates)][std::get<1>(coordinates)];


		// ============================================== //
		// ============ |Phi> = Ui^dag |Phi> ============ //
		// ============================================== //

		SqMatrix arr = dagger(gate.application_gate);
		std::vector<unsigned int> gate_qubs = gate.qubits;

		// Prepare Layer and permutation
		std::vector<Application> layer = {Application(arr, empty, gate_qubs)};
		std::vector<unsigned int> permutation(qubits);


		make_permutation(permutation, qubits, layer);
		SqMatrix filled_gate(0);	// init as empty
		fill_gate(filled_gate, layer);
		apply_on_map(phi, permutation, qubits, filled_gate);


		// ============================================== //
		// ======= |Mi> = (dUi^dag / dthetai) |Mi> ====== //
		// ============================================== //

		arr = gate.application_gate_dif;

		// PARAMETRIC GATE!
		if(arr.dims() > 1) 
		{
			std::vector<comp> mi = phi;

			layer = {Application(arr, empty, gate_qubs)};
			make_permutation(permutation, qubits, layer);

			filled_gate = SqMatrix(0);	// init as empty
			fill_gate(filled_gate, layer);
			apply_on_map(mi, permutation, qubits, filled_gate);

			// Nabla <E>i
			grad[param--] = 2.0 * inner_product(lambda, mi).real;
		}


		// UPDATE LAMBDA
		//if(param > 0) {

		// ============================================== //
		// ========= |Lambda> = Ui^dag |Lambda> ========= //
		// ============================================== //

		arr = dagger(gate.application_gate);

		// Prepare Layer and permutation
		layer = {Application(arr, empty, gate_qubs)};
		make_permutation(permutation, qubits, layer);

		filled_gate = SqMatrix(0);	// init as empty
		fill_gate(filled_gate, layer);
		apply_on_map(lambda, permutation, qubits, filled_gate);
		//}


	} // applications loop

	return grad;
}
