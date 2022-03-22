#include <stdio.h>
#include <stdlib.h>
#include "state.h"

/*
 * GENERAL IDEA OF THIS FILE:
 *
 * DEFINE A CIRCUIT WHICH HAS THESE:
 * 1) State = The state of qubits
 * 2) Layout = Layers of gates - layer = a single big matrix
 * 3) Apply layers
 * 4) Measure <-- needs a random *something*
 *
 *
 * LAYER:
 * list of gates = a big nxn matrix of the layer
 * helping funcs: tensor prod, direct sum!
 *
 *
 * Split to layers:
 * take a list of operations
 * operation = {Gatename, parameters, qubits to be applied on}
 * xantres mia mia pros ta pisw. spaw se layers. NA BRW ALGORITHMO!
 *
 * OPTIMIZER:
 * Adam. Gradient???
 *
 */

int main() {

}
