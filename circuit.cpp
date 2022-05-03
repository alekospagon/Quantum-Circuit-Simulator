#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <bitset>   // convert integer to bin_string
// #include "state.h"  
#include "algebra.h"
#include "comp.h"
#include "gates.h"      // gate library
#include "gate_ids.h"  // gates as instuctions!


#define max(a,b) ((a)>(b)?(a):(b))





// this defines a gate application to the circuit
// gate g with parameters "params" applied to "qubits"
class Application {
    public:
        // short int g;
        // std::vector<c_type> params;
        gate application_gate;
        std::vector<unsigned int> qubits;

        Application(gate g, std::vector<unsigned int> qubits);
};

Application::Application(
    gate g, 
    std::vector<unsigned int> q) {
    application_gate = g;
    qubits = q;
}











class Circuit {
    public:
        unsigned int qubits;
        // last layer that this qubit is available
        std::vector<unsigned int> available_layer;
        // fill layers with gate applications
        std::vector< std::vector<Application> > layers;

        std::vector<comp> state_vector;

    
        Circuit(unsigned int q) : 
            qubits(q), available_layer(q,0), 
            state_vector( 1<<q, c(0.0, 0.0) )
            {
                unsigned int MAX_QUBITS = 10;
                if(q == 0) {
                    std::cout << "Zero Qubits Given!\n";
                    exit(1);
                }
                if(q > MAX_QUBITS) {
                    std::cout << "More than " << MAX_QUBITS
                        << " Qubits! You are a mad man....\n";
                    exit(1);
                }
                state_vector[0] = c(1.0, 0.0);
            };

        // gate application handler
        void app (Application a);

        // print 
        void print_circuit();

        void print_state_vector();


        // Run Circuit - Save state-vector
        void run();


        // standard library 
        void I(unsigned int qubit);
        void H(unsigned int qubit);
        void X(unsigned int qubit);
        void Y(unsigned int qubit);
        void Z(unsigned int qubit);
        void CNOT(unsigned int control, unsigned int target);
        void CY(unsigned int control, unsigned int target);
        void CZ(unsigned int control, unsigned int target);
        void SWAP(unsigned int qubit1, unsigned int qubit2);
        void RX(unsigned int qubit, c_type angle);
        void RY(unsigned int qubit, c_type angle);
        void RZ(unsigned int qubit, c_type angle);
        void ROT(unsigned int qubit, c_type phi, c_type theta, c_type omega);
        void CRX(unsigned int control, unsigned int target, c_type angle);
        void CRY(unsigned int control, unsigned int target, c_type angle);
        void CRZ(unsigned int control, unsigned int target, c_type angle);
};



// gate application. Fit into correct Layer
void Circuit::app(Application a) {
    
    // find rightmost position to apply gate
    unsigned int layer_index = 0;
    for(unsigned int i = 0; i < a.qubits.size(); ++i) {
        layer_index = max(layer_index, available_layer[a.qubits[i]]);

        if(a.qubits[i] > qubits - 1) {
            std::cout << "Qubit out of Range!\n";
            exit(1);
        }
    }



    // NEW LAYER?
    if( layers.size() < layer_index + 1) {
        std::vector<Application> new_layer = {a};
        layers.push_back( new_layer );
    }
    else layers[layer_index].push_back(a);

    
    // update positions
    for(unsigned int i = 0; i < a.qubits.size(); ++i)
        available_layer[a.qubits[i]] = layer_index + 1;

    // std::cout << "Circuit Depth: " << layers.size() << "\n";
}




// Helper function. It swaps two bits in a number
// Used for qubit permutations: State_vector indices are bits
// Position = qubit. So I swap qubits with an iteration in the state-vector
inline int swapBits(unsigned int b, unsigned int p1, unsigned int p2)
{
    unsigned int x = ((b >> p1) ^ (b >> p2)) & 1; // XOR temporary
    return b ^ ((x << p1) | (x << p2));
}






// Run circuit - Returns result StateVector
void Circuit::run(){

    std::cout << " ============= Running Circuit ============= \n";



    // |000...0>
    state_vector.clear();
    state_vector.push_back( c(1.0, 0.0) );
    for(int i = 1; i < (1<<qubits); ++i)
        state_vector.push_back( c(0.0, 0.0) );



    // Layer-by-Layer
    int depth = layers.size();
    for(int i = 0; i < depth; ++i) {

        // take layer and make layer_array
        std::vector<Application> this_layer = layers[i];
        std::vector<std::vector<comp>> layer_array = this_layer[0].application_gate.array;
        // fill with I
        int gates = this_layer.size();


        // put all gates in first qubits and accumulate permutations
        for(int j = 1; j < gates; ++j)
            // associativity of tensor product. Accumulate them
            layer_array = tensor_prod(
                        layer_array, 
                        this_layer[j].application_gate.array );

        // I @ ... @ I = Identity_with_dimensions(2^n)
        unsigned int rest_wires_dim = (1<<qubits) / layer_array.size();
        layer_array = tensor_prod(layer_array, Identity_matrix(rest_wires_dim));


        state_vector = Array_dot_state(layer_array, state_vector);
    }
}




void Circuit::print_state_vector() {

    unsigned int dim = state_vector.size();

    for(unsigned int i = 0; i < dim; ++i){
        std::cout << "|" << i << ">\t" << "= ";
        print_comp(state_vector[i]);
        std::cout << "\n";
    }
}


void Circuit::print_circuit() {
    std::cout << "============= Printing Circuit ============= \n";

    for(int i = 0; i < layers.size(); ++i) {
        std::cout << "===== Printing Layer: " << i << " =====\n";

        for(int j = 0; j < layers[i].size(); ++j){
            layers[i][j].application_gate.print_gate();

            std::cout << "Applied on Qubit(s): ";
            for(int k = 0; k < layers[i][j].qubits.size(); ++k) 
                std::cout << layers[i][j].qubits[k] << " ";
            std::cout << "\n";
        }
    }

}




void Circuit::I(unsigned int qubit){
    Application a(gate_I(), std::vector<unsigned int> {qubit});
    app(a);
}
void Circuit::H(unsigned int qubit){
    Application a(gate_H(), std::vector<unsigned int> {qubit});
    app(a);
}
void Circuit::X(unsigned int qubit){
    Application a(gate_X(), std::vector<unsigned int> {qubit});
    app(a);
}
void Circuit::Y(unsigned int qubit){
    Application a(gate_Y(), std::vector<unsigned int> {qubit});
    app(a);
}
void Circuit::Z(unsigned int qubit){
    Application a(gate_Z(), std::vector<unsigned int> {qubit});
    app(a);
}

void Circuit::CNOT(unsigned int control, unsigned int target){
    Application a(gate_CNOT(), std::vector<unsigned int> {control, target});
    app(a);
}
void Circuit::CY(unsigned int control, unsigned int target){
    Application a(gate_CY(), std::vector<unsigned int> {control, target});
    app(a);
}
void Circuit::CZ(unsigned int control, unsigned int target){
    Application a(gate_CZ(), std::vector<unsigned int> {control, target});
    app(a);
}
void Circuit::SWAP(unsigned int qubit1, unsigned int qubit2){
    Application a(gate_SWAP(), std::vector<unsigned int> {qubit1, qubit2});
    app(a);
}
void Circuit::RX(unsigned int qubit, c_type angle){
    Application a(gate_RX(angle), std::vector<unsigned int> {qubit});
    app(a);
}
void Circuit::RY(unsigned int qubit, c_type angle){
    Application a(gate_RY(angle), std::vector<unsigned int> {qubit});
    app(a);
}
void Circuit::RZ(unsigned int qubit, c_type angle){
    Application a(gate_RZ(angle), std::vector<unsigned int> {qubit});
    app(a);
}
void Circuit::ROT(unsigned int qubit, c_type phi, c_type theta, c_type omega){
    Application a(gate_ROT(phi, theta, omega), std::vector<unsigned int> {qubit});
    app(a);
}
void Circuit::CRX(unsigned int control, unsigned int target, c_type angle){
    Application a(gate_CRX(angle), std::vector<unsigned int> {control, target});
    app(a);
}
void Circuit::CRY(unsigned int control, unsigned int target, c_type angle){
    Application a(gate_CRY(angle), std::vector<unsigned int> {control, target});
    app(a);
}
void Circuit::CRZ(unsigned int control, unsigned int target, c_type angle){
    Application a(gate_CRZ(angle), std::vector<unsigned int> {control, target});
    app(a);
}





int main() {
    Circuit c = Circuit(6);

    for(int i = 0; i<36; i++) {
        c.RX(0, 0.123);
        c.RX(1, 0.123);
        c.RX(2, 0.123);
        c.RX(3, 0.123);
        c.RX(4, 0.123);
        c.RX(5, 0.123);
    }


    // c.print_circuit();

    for(int k = 0; k < 5000; ++k)
        c.run();

    c.print_state_vector();

    return 0;
}