#include "circuit.h"



// =============================================== //
// ============ STANDARD GATE LIBRARY ============ //
// =============================================== //


void Circuit::I(unsigned int qubit){
	Application a(gate_I, std::vector<unsigned int> {qubit});
	app(a);
}
void Circuit::H(unsigned int qubit){
	Application a(gate_H, std::vector<unsigned int> {qubit});
	app(a);
}
void Circuit::X(unsigned int qubit){
	Application a(gate_X, std::vector<unsigned int> {qubit});
	app(a);
}
void Circuit::Y(unsigned int qubit){
	Application a(gate_Y, std::vector<unsigned int> {qubit});
	app(a);
}
void Circuit::Z(unsigned int qubit){
	Application a(gate_Z, std::vector<unsigned int> {qubit});
	app(a);
}
void Circuit::S(unsigned int qubit){
	Application a(gate_S, std::vector<unsigned int> {qubit});
	app(a);
}
void Circuit::T(unsigned int qubit){
	Application a(gate_T, std::vector<unsigned int> {qubit});
	app(a);
}

void Circuit::CNOT(unsigned int control, unsigned int target){
	Application a(gate_CNOT, std::vector<unsigned int> {target, control});
	app(a);
}
void Circuit::CY(unsigned int control, unsigned int target){
	Application a(gate_CY, std::vector<unsigned int> {target, control});
	app(a);
}
void Circuit::CZ(unsigned int control, unsigned int target){
	Application a(gate_CZ, std::vector<unsigned int> {target, control});
	app(a);
}
void Circuit::SWAP(unsigned int qubit1, unsigned int qubit2){
	Application a(gate_SWAP, std::vector<unsigned int> {qubit1, qubit2});
	app(a);
}

void Circuit::TOFFOLI(unsigned int control1, unsigned int control2, unsigned int target){
	Application a(gate_TOFFOLI, std::vector<unsigned int> {target, control1, control2});
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
void Circuit::P (unsigned int qubit, c_type angle){
	Application a(gate_P (angle), std::vector<unsigned int> {qubit});
	app(a);
}
void Circuit::ROT(unsigned int qubit, c_type phi, c_type theta, c_type omega){
	Application a(gate_ROT(phi, theta, omega), std::vector<unsigned int> {qubit});
	app(a);
}
void Circuit::CRX(unsigned int control, unsigned int target, c_type angle){
	Application a(gate_CRX(angle), std::vector<unsigned int> {target, control});
	app(a);
}
void Circuit::CRY(unsigned int control, unsigned int target, c_type angle){
	Application a(gate_CRY(angle), std::vector<unsigned int> {target, control});
	app(a);
}
void Circuit::CRZ(unsigned int control, unsigned int target, c_type angle){
	Application a(gate_CRZ(angle), std::vector<unsigned int> {target, control});
	app(a);
}






