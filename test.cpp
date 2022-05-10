#include "library.h"	


void print_vector(std::vector<c_type> vec) {
	std::cout << "Printing Vector\n";
	for(int i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << "\n";
}




// Make Circuit with weights
// Returns Expectation Value
c_type cost (std::vector <c_type> weights) 
{
	Circuit c(3);

	c.ROT(1, weights[0], weights[1], weights[2]);
	c.ROT(2, weights[3], weights[4], weights[5]);
	c.run();

	c_type spin_0 = c.exp_value(arr_Z, {0});
	c_type spin_1 = c.exp_value(arr_Z, {1});
	c_type spin_2 = c.exp_value(arr_Z, {2});

	c_type energy = -(1.0*spin_0*spin_1) - (-1.0*spin_1*spin_2);

	return energy;
}




int main() {

	auto weights = random_weights(6);

	GD(cost, weights);
	ADAGRAD(cost, weights);
	ADAM(cost, weights);

	return 0;
}