#include <math.h>
#include <stdio.h>
#include "comp.h"

typedef struct state_{
	int qubits;		// Number of Qubits
	comp *coeffs; 	// Coefficients
} State;


// FUNCTION DECLARATIONS
State	new_state			(int qubits);
void	init				(State* s);
void	print_state			(State* s);
bool	check_valid_state	(State* s);
double	prob_of_base_state	(State* s, int base_state);




// create a state
State new_state(int qubits)
{
	State s;
	s.qubits = qubits;
	s.coeffs = new comp[1<<qubits]; //2^qubits coefficients!
	return s;
}

// take a pointer to a state and init it
void init(State* s)
{
	int dimension = 1<<(s->qubits);
	for(int i = 0; i<dimension; i++) 
	{
		s->coeffs[i].real = 0.0;
		s->coeffs[i].imag = 0.0;
	}
	s->coeffs[0].real = 1.0;
}

// take a state location. print its vector
void print_state(State* s) 
{
	printf("Printing State:\n");
	int dimension = 1<<(s->qubits);

	// parse vector
	for(int i = 0; i<dimension; i++)
	{
		// Calculate probabilities
		double prob;
		prob  = s->coeffs[i].real * s->coeffs[i].real;
		prob += s->coeffs[i].imag * s->coeffs[i].imag;
		// Print |i> with its probability
		printf("|%d>\t= %lf + i%lf \t\t Prob: %lf\n", 
				i, s->coeffs[i].real, s->coeffs[i].imag, prob);
	}
	return ;
}

bool check_valid_state(State* s)
{
	double sum = 0.0;
	// sum |z|^2
	int dimension = 1<<(s->qubits);

	for(int i = 0; i<dimension; i++)
	{
		// z = a+ib --> |z|^2 = a^2 + b^2
		sum += 	s->coeffs[i].real * s->coeffs[i].real +
				s->coeffs[i].imag * s->coeffs[i].imag;
	}

	// Allow a precision-error
	if ( abs(1 - sum) > 0.000001 )
		return false;
	return true;	
}


double prob_of_base_state(State* s, int base_state) 
{
	comp data = s->coeffs[base_state];
	return data.real*data.real + data.imag*data.imag;
}

