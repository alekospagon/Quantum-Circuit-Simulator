#ifndef __CIRCUIT_LIBRARY__
#define __CIRCUIT_LIBRARY__


#include "circuit.h"
#include "gate_library.h"


// Make an Application, then use app(); to pass it to Circuit
// pretty simplex syntax:
// Circuit.NOT(1, 2); 


void Circuit::I(unsigned int qubit){
	Application a(matrix_I, empty, {qubit});
	app(a);
}
void Circuit::H(unsigned int qubit){
	Application a(matrix_H, empty, {qubit});
	app(a);
}
void Circuit::X(unsigned int qubit){
	Application a(matrix_X, empty, {qubit});
	app(a);
}
void Circuit::Y(unsigned int qubit){
	Application a(matrix_Y, empty, {qubit});
	app(a);
}
void Circuit::Z(unsigned int qubit){
	Application a(matrix_Z, empty, {qubit});
	app(a);
}
void Circuit::S(unsigned int qubit){
	Application a(matrix_S, empty, {qubit});
	app(a);
}
void Circuit::T(unsigned int qubit){
	Application a(matrix_T, empty, {qubit});
	app(a);
}

void Circuit::CNOT(unsigned int control, unsigned int target){
	Application a(matrix_CNOT, empty, {target, control});
	app(a);
}
void Circuit::CY(unsigned int control, unsigned int target){
	Application a(matrix_CY, empty, {target, control});
	app(a);
}
void Circuit::CZ(unsigned int control, unsigned int target){
	Application a(matrix_CZ, empty, {target, control});
	app(a);
}
void Circuit::SWAP(unsigned int qubit1, unsigned int qubit2){
	Application a(matrix_SWAP,  empty,{qubit1, qubit2});
	app(a);
}

void Circuit::TOFFOLI(unsigned int control1, unsigned int control2, unsigned int target){
	Application a(matrix_TOFFOLI, empty, {target, control1, control2});
	app(a);
}









// include derivative for these

void Circuit::RX(unsigned int qubit, c_type angle){
	Application a(matrix_RX(angle), matrix_RX_dif(angle), {qubit});
	app(a);
	parametric_gates++;
}
void Circuit::RY(unsigned int qubit, c_type angle){
	Application a(matrix_RY(angle), matrix_RY_dif(angle), {qubit});
	app(a);
	parametric_gates++;
}
void Circuit::RZ(unsigned int qubit, c_type angle){
	Application a(matrix_RZ(angle), matrix_RZ_dif(angle), {qubit});
	app(a);
	parametric_gates++;
}
void Circuit::P (unsigned int qubit, c_type angle){
	Application a(matrix_P(angle), matrix_P_dif(angle), {qubit});
	app(a);
	parametric_gates++;
}
void Circuit::CRX(unsigned int control, unsigned int target, c_type angle){
	Application a(matrix_CRX(angle), matrix_CRX_dif(angle), {target, control});
	app(a);
	parametric_gates++;
}
void Circuit::CRY(unsigned int control, unsigned int target, c_type angle){
	Application a(matrix_CRY(angle), matrix_CRY_dif(angle), {target, control});
	app(a);
	parametric_gates++;
}
void Circuit::CRZ(unsigned int control, unsigned int target, c_type angle){
	Application a(matrix_CRZ(angle), matrix_CRZ_dif(angle), {target, control});
	app(a);
	parametric_gates++;
}
void Circuit::CP(unsigned int control, unsigned int target, c_type angle){
	Application a(matrix_CP(angle), matrix_CP_dif(angle), {target, control});
	app(a);
	parametric_gates++;
}


#endif
