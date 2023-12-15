# A Quantum Circuit Simulator with efficient Circuit Training

 A fully custom, fast, simple Quantum Circuit simulator written in C++ for fun


# How it works?

At its core there is a complex number and linear algebra subset.

Based on that and on a Quantum Gates library, 
we make a Quantum Circuit that handles these gates using basic algorithms.

We can run the circuit, print the statevector, make a virtual experiment,
but it can also return the gradient of the expectation value of an 
observable (using Adjoint Differentiation). That allows us to train a 
Quantum Circuit by calculating the gates parameters that minimize an observable.

There are also a built-in Optimizers (like GD, Adam).


# How to use it as a simple Circuit Simulator

Make a circuit like this

```c++
Circuit c(3);

c.RX(0, weights[0]);
c.CNOT(0,1);
c.RY(1, weights[1]);
c.RZ(1, weights[2]);
```

that just creates the layout. Then run it!

```c++
c.run();
```

And then get your results:

```c++
std::cout << c.exp_value(matrix_X, {1}) << "\n";
```

# How to train a circuit

Make a function that fills the circuit with your parameters like this:

```c++
void make_circuit(Circuit &c, vector<c_type> weights);
```

Then pass this layout to the optimizer along with some random weights
and an Obserable to minimize:

```c++
weights = ADAM(N_QUBITS, make_circuit, Obs, Osb_qubits, weights, MY_EPOCHS);
```

And grab your optimized weights!
