#ifndef __OPTIMIZERS__
#define __OPTIMIZERS__ 420

#include <math.h>
#include <random>
#include <time.h>

#include "parameters.h"
#include "comp.h"


// DEFINE OPTIMIZER PARAMETERS
#define EPOCHS 1000
#define STEP_SIZE 0.01
#define VERBOSE true





// random weights in range (-2pi, 2pi)
std::vector<c_type> random_weights (unsigned int weights_len) {
	// random weights to be optimized
	srand((unsigned)time(0));
	std::vector<c_type> weights (weights_len, 0.0);
	for(unsigned int i = 0; i < weights_len; ++i) { 
		int random_num = (rand()%100000); // in range (0, 999)
		// map (0,999) to (-2pi, 2pi)
		c_type resize = 2*pi/100000;// shrink to (0, 4pi)
		c_type shift  = pi;			// offset --> 2 pi
		weights[i] = (resize*random_num) - shift;
	}

	return weights;
}




// Adagrad Optimizer
// Take cost, weights --> returns optimized weights
std::vector<c_type> ADAGRAD (
	c_type my_cost (std::vector<c_type>), 
	std::vector<c_type> init_weights,

	unsigned int epochs = EPOCHS,
	c_type step_size = STEP_SIZE,
	c_type eps = 1e-08,
	bool verbose = VERBOSE
) 
{
	// PARAMETERS
	std::vector<c_type> weights = init_weights;
	unsigned int weights_len = weights.size();
	std::vector<c_type> learning_rate (weights_len, step_size);
	std::vector<c_type> alpha (weights_len, 0.0);
	c_type epsilon = 0.00001;


	if(verbose)
		std::cout << "========== ADAGRAD =========\n"
			"Epochs:\t" << epochs << "\tLearning Rate:\t" <<
			step_size;



	// iterations
	for(unsigned int epoch = 1; epoch <= epochs; ++epoch) {
		std::vector<c_type> grad (weights_len, 0.0);

		// COMPUTE GRAD
		for(unsigned int w_i = 0; w_i < weights_len; ++w_i) {
			// f(x+epsilon)	and f(x-epsilon)
			std::vector<c_type> weights_1 = weights;
			std::vector<c_type> weights_2 = weights;
			weights_1[w_i] += epsilon;
			weights_2[w_i] -= epsilon;

			c_type v1 = my_cost(weights_1);
			c_type v2 = my_cost(weights_2);

			grad[w_i] = (v1 - v2) / epsilon;
		}

		// UPDATE
		for(unsigned int grad_i = 0; grad_i < weights_len; ++grad_i) {
			alpha[grad_i]  += grad[grad_i] * grad[grad_i];
			learning_rate[grad_i] = step_size / sqrt(alpha[grad_i] + eps);
			weights[grad_i] = weights[grad_i] - learning_rate[grad_i] * grad[grad_i];
		}

		// DEBUG PRINTING
		if(verbose && epoch % 10 == 0) {
			std::cout << "Epoch:\t" << epoch << "\tCOST: ";
			std::cout << my_cost(weights) << "\n";
		}
	}

	return weights;
}












// Adam Optimizer
// Take cost, weights --> returns optimized weights
std::vector<c_type> ADAM(
	c_type my_cost (std::vector<c_type>), 
	std::vector<c_type> init_weights,

	unsigned int epochs = EPOCHS,
	c_type step_size = STEP_SIZE,
	c_type beta1_init = 0.9,
	c_type beta2_init = 0.99,
	c_type eps = 1e-08,
	bool verbose = VERBOSE
)
{
	// WEIGHTS
	std::vector<c_type> weights = init_weights;
	unsigned int weights_len = weights.size();
	// PARAMETERS
	c_type learning_rate = step_size;
	c_type alpha = 0.0, beta = 0.0;
	c_type beta1 = beta1_init;
	c_type beta2 = beta2_init;
	// Gradient Parameter
	c_type epsilon = 0.00001;


	if(verbose)
		std::cout << "========== ADAM OPTIMIZER =========\n"
			"Epochs:\t" << epochs << "\tLearning Rate:\t" <<
			learning_rate;



	// iterations
	for(unsigned int epoch = 1; epoch <= epochs+1; ++epoch) {
		std::vector<c_type> grad (weights_len, 0.0);

		// COMPUTE GRAD
		for(unsigned int w_i = 0; w_i < weights_len; ++w_i) {
			// f(x+epsilon)	and f(x-epsilon)
			std::vector<c_type> weights_1 = weights;
			std::vector<c_type> weights_2 = weights;
			weights_1[w_i] += epsilon;
			weights_2[w_i] -= epsilon;

			c_type v1 = my_cost(weights_1);
			c_type v2 = my_cost(weights_2);

			grad[w_i] = (v1 - v2) / epsilon;
		}

		// UPDATE
		for(unsigned int grad_i = 0; grad_i < weights_len; ++grad_i) {
			alpha = beta1 * alpha + (1.0 - beta1) * grad[grad_i];
			beta  = beta2 * beta  + (1.0 - beta2) * grad[grad_i] * grad[grad_i];
			learning_rate = step_size * sqrt(1.0 - pow(beta2, epoch)) 
				/ (1.0 - pow(beta1, epoch));
			weights[grad_i] = weights[grad_i] - learning_rate * alpha / (sqrt(beta) + eps);
		}

		// DEBUG PRINTING
		if(verbose && epoch % 10 == 0) {
			std::cout << "Epoch:\t" << epoch << "\tCOST: ";
			std::cout << my_cost(weights) << "\n";
		}
	}

	return weights;
}














// Gradient Descent Optimizer
// Take cost, weights --> returns optimized weights
std::vector<c_type> GD(
	c_type my_cost (std::vector<c_type>), 
	std::vector<c_type> init_weights,

	unsigned int epochs = EPOCHS,
	c_type learning_rate = STEP_SIZE,
	bool verbose = VERBOSE 
) 
{
	if(verbose)
		std::cout << "========== GRADIENT DESCENT =========\n"
			"Epochs:\t" << epochs << "\tLearning Rate:\t" <<
			learning_rate;

	// Parameters
	std::vector<c_type> weights = init_weights;
	unsigned int weights_len = weights.size();
	c_type epsilon = 0.00001;


	// iterations
	for(unsigned int epoch = 1; epoch <= epochs; ++epoch) {

		// Gradient vector
		std::vector<c_type> grad (weights_len, 0.0);

		// COMPUTE GRAD
		for(unsigned int w_i = 0; w_i < weights_len; ++w_i) {
			// f(x+epsilon)	and f(x-epsilon)
			std::vector<c_type> weights_1 = weights;
			std::vector<c_type> weights_2 = weights;
			weights_1[w_i] += epsilon;
			weights_2[w_i] -= epsilon;

			c_type v1 = my_cost(weights_1);
			c_type v2 = my_cost(weights_2);

			grad[w_i] = (v1 - v2) / epsilon;
		}

		// Update weights
		for(unsigned int grad_i = 0; grad_i < weights_len; ++grad_i) {
			weights[grad_i] = weights[grad_i] - learning_rate * grad[grad_i];
		}

		// Print Results
		if(verbose && epoch % 10 == 0) {
			std::cout << "Epoch:\t" << epoch << "\tCOST: ";
			std::cout << my_cost(weights) << "\n";
		}
	}

	return weights;
}












#endif
