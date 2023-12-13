#include "../simulator.h"
#include <math.h>
#include <random>
#include <time.h>


// Example from:
// https://pennylane.ai/qml/demos/tutorial_adjoint_diff.html


int main() 
{
	std::vector<c_type> weights = {0.1 , 0.2 , 0.3};

	Circuit c(2);

	c.RX(0, weights[0]);
	c.CNOT(0,1);
	c.RY(1, weights[1]);
	c.RZ(1, weights[2]);


	c.run();


	std::cout << c.exp_value(matrix_X, {1}) << "\n";
	print_vector(c.exp_value_grad(matrix_X, {1}));

	// Should print:
	// exp_val : 0.1888478712271
	// gradient: -0.01894799  0.9316158  -0.05841749

	return 0;
}
