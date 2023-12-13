#ifndef __CIRCUIT_APPLICATION__
#define __CIRCUIT_APPLICATION__

#include <iostream>
#include <vector>

#include "../math/math.h"



// GATE APPLICATION
class Application {
	public:
		SqMatrix application_gate;
		SqMatrix application_gate_dif; // dGate
		std::vector<unsigned int> qubits;


		// Constructor
		Application(SqMatrix g, SqMatrix g_dif, std::vector<unsigned int> q )
		: application_gate(g), application_gate_dif(g_dif), qubits(q) {

			#ifdef __SAFE_LIBRARY__
				// Check qubits-gate dimensions!
				unsigned int qubs = q.size();
				if (g.dims() != (unsigned int) (1<<qubs)) {
					std::cout << "Application Constructor Error:"
						"qubits don't match array size\n";
						exit(1);
				}

				// Check for duplicates in qubit list
				std::vector<bool> qubit_used(MAX_QUBITS, false);
				for(unsigned int i = 0; i < qubs; ++i) {
					if(qubit_used[q[i]] == true) {
						std::cout << "Application Constructor Error: "
							"Dulpicate Qubit Detected!\n";
						exit(1);
					}
					qubit_used[q[i]] = true;
				}
			#endif
		};
};






#endif
