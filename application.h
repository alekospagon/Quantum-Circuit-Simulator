#ifndef __APPLICATION__
#define __APPLICATION__ 420

#include <iostream>
#include <vector>

#include "parameters.h"
#include "comp.h"
#include "gates.h"

// GATE APPLICATION
class Application {
	public:
		gate application_gate;
		std::vector<unsigned int> qubits;

		// Application Constructor
		Application(gate g, std::vector<unsigned int> q) {
			// Check dimensions!
			unsigned int qubs = q.size();
			if (g.array.size() != (unsigned int) (1<<qubs)) {
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

			// copy 
			application_gate = g;
			qubits = q;
		};
};




#endif
