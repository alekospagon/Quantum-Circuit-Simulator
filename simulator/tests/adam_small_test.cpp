#include "../simulator.h"
#include <math.h>
#include <random>
#include <time.h>



// make circuit given weights
// --RX--o--RY-----
// ------|---------
// ------X--RZ-----{X}

void make_circuit(Circuit &c, std::vector<c_type> weights) {
	c.RX(0, weights[0]);
	c.CNOT(0,1);
	c.RY(1, weights[1]);
	c.RZ(1, weights[2]);
}


int main() 
{
	std::vector<c_type> weights = random_weights(3);

	// optimize
	// qubits=3, layout, Observable, Obs_qubits, initial weights, epochs
	weights = GD( 3, make_circuit, matrix_X, {1}, weights , 2500);

	return 0;
}