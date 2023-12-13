#ifndef __MATH_ALGEBRA_OPERATIONS__ 
#define __MATH_ALGEBRA_OPERATIONS__ 


#include "algebra_core.h"


// Declarations:
bool is_hermitian(const SqMatrix &Obs);
// Array and Vector operations
std::vector<comp> Array_dot_state(const SqMatrix &array, const std::vector<comp> &state);
std::vector<comp> Sparse_Array_dot_state(const SqMatrix &array, const std::vector<comp> &state);
c_type expectation_value (const SqMatrix &Obs, const std::vector<comp> &state);
// array only operations
SqMatrix square_tensor_prod(const SqMatrix &arr1, const SqMatrix &arr2);
SqMatrix Identity_matrix(unsigned int dim);
inline SqMatrix dagger(const SqMatrix & m);
inline SqMatrix operator * (const c_type number, const SqMatrix & arr);





// Tensor product for square matrices
SqMatrix square_tensor_prod(
	const SqMatrix &arr1,
	const SqMatrix &arr2)
{
	// tensor product dimension
	unsigned int dim = arr1.dims() * arr2.dims();
	unsigned int p = arr2.dims(); // power of two

	// find which power of two is p
	unsigned int power;
	for(power = 0; p >> power != 1; ++power) ;

	// =========== FILL ARRAY =========== //
	SqMatrix elements (dim);


	// parallel. cache? blocks? 
	for(unsigned int i = 0; i < dim; ++i) {
		for(unsigned int j = 0; j < dim; ++j)
			// C_ij = a[i/p][j/p] * b[i%p][j%p];
			// dimensions are powers of two!!!
			// instead of / and % do >> and &(x-1)
			elements.set(i, j, 
				arr1.get(i>>power,j>>power) * arr2.get(i&(p-1),j&(p-1)) );
	}
	
	return elements;
}




// return an I array with dimensions dim x dim
SqMatrix Identity_matrix(unsigned int dim) {

	SqMatrix result(dim);

	for(unsigned int i = 0; i < dim; ++i)
		for(unsigned int j = 0; j < dim; ++j)
			result.set(i, j, c((i == j) ? 1.0 : 0.0, 0.0) );

	return result;
}








// Anxn * Snx1
std::vector<comp> Array_dot_state(
	const SqMatrix &array,
	const std::vector<comp> &state ) 
{
	#ifdef __SAFE_LIBRARY__
		// =========== CHECK DIMENSIONS! =========== //
		if(state.size() != array.dims()) {
			std::cout << "Array Dot State Error: "
				"Array dimensions(" << array.dims() << 
				") and State dimensions(" << state.size() << 
				") don't match\n";
				exit(1);
		}
	#endif


	unsigned int dim = state.size();

	std::vector<comp> res(dim);

	// matrix multiplication
	for(unsigned int i = 0; i < dim; ++i) {
		comp c_i = c(0.0, 0.0);
		// c_i = SUM a_ik b_k
		for(unsigned int k = 0; k < dim; ++k)
			c_i = c_i + array.get(i,k) * state[k];

		res[i] = c_i;
	}

	return res;
}



/*
	/ S 0 0 0 \ / psi1 \
	| 0 S 0 0 | | psi2 |
	| 0 0 S 0 | | .... |
	\ 0 0 0 S / \ psin /
*/
std::vector<comp> Sparse_Array_dot_state(
	const SqMatrix &array,
	const std::vector<comp> &state) 
{
	unsigned int Id_dim = state.size() / array.dims(); 


#ifdef __SAFE_LIBRARY__
	// =========== CHECK DIMENSIONS! =========== //
	if(state.size() != Id_dim * array.dims()) {
		std::cout << "Array Dot State Error: "
			"Array dimensions(" << array.dims() << 
			") and State dimensions(" << state.size() << 
			") don't match\n";
			exit(1);
	}
#endif

	// Result StateVector
	unsigned int dim = state.size();
	std::vector<comp> res(dim);
	// Snxn
	unsigned int s_dim = array.dims();

	// for every sub-matrix S
	for(unsigned int s = 0; s < Id_dim; ++s) {


		for(unsigned int i = 0; i < s_dim; ++i) {
			comp c_i = c(0.0, 0.0);
			// c_i = SUM a_ik b_k
			for(unsigned int k = 0; k < s_dim; ++k)
				// offset for statevector --> some S arrays
				c_i = c_i + array.get(i,k) * state[s_dim * s + k];

			res[s_dim * s + i] = c_i;
		}
	}


	return res;
}







bool is_hermitian( const SqMatrix &Obs ) {
	// ============ CHECK ELEMENTS ============ //
	// Hermitian means: a_ij = a_ji*
	for(unsigned int i = 0; i < Obs.dims(); ++i) {
		for(unsigned int j = 0; j < Obs.dims(); ++j) 
			// allow a small error --> their distance
			if( distance(Obs.get(i,j) , conj(Obs.get(j,i))) > 0.0001 ) 
				return false;
	}

	return true;
}






// Returns:   <A> = <Psi|A|Psi>
c_type expectation_value (
	const SqMatrix &Obs,
	const std::vector<comp> &state )
{
	#ifdef __SAFE_LIBRARY__
		// =========== ARRAY CHECKS =========== //
		if(!is_hermitian(Obs)) {
			std::cout << "Expectation Value Error: "
				"Observable matrix is not Hermitian!\n";
			exit(1);
		}
	#endif

	// compute
	unsigned int dim = state.size();
	comp tmp_res = c(0.0, 0.0);
	for(unsigned int i = 0; i < dim; ++i) {
		comp tmp = c(0.0, 0.0);
		for(unsigned int j = 0; j < dim; ++j)
			tmp = tmp + Obs.get(i,j) * state[j];
		tmp_res = tmp_res + mul_conj(state[i], tmp);
	}

	// check imaginary part. Should be zero or very small
	#ifdef __SAFE_LIBRARY__
		// this complex should be real.
		if( abs(tmp_res.imag) > 0.0001 ) {
			std::cout << "Expectation Value Error: "
				"Result has big imaginary part\n";
			exit(1);
		}
	#endif


	return tmp_res.real;
}





inline SqMatrix dagger(const SqMatrix & m) {
	unsigned int d = m.dims();

	SqMatrix res(d);

	// b_ij = a_ji*
	// RE-ORDER FOR CACHE EFFICIENCY
	for(unsigned int i = 0; i < d; ++i)
		for(unsigned int j = 0; j < d; ++j)
			res.set(i,j, conj(m.get(j,i)) );

	return res;
}




comp inner_product(
	const std::vector<comp> &v1,
	const std::vector<comp> &v2) 
{
	unsigned int s1 = v1.size();
	#ifdef __SAFE_LIBRARY__
		if(s1 != v2.size()) {
			std::cout << "Inner Product Error: "
				"vector sizes are different\n";
			exit(1);
		}
	#endif

	comp res = c(0.0, 0.0);
	for(unsigned int i = 0; i < s1; ++i)
		res = res + mul_conj(v1[i], v2[i]);

	return res;
}






























// Make tensor product as operator %
inline SqMatrix operator % (
	const SqMatrix &arr1, 
	const SqMatrix &arr2) 
{ 
	return square_tensor_prod(arr1, arr2);
}


// Add arrays
inline SqMatrix operator + (
	const SqMatrix &arr1, 
	const SqMatrix &arr2) 
{ 
	#ifdef __SAFE_LIBRARY__
		if(arr1.dims() != arr2.dims()) {
			std::cout << "SqMatrix operator + error: "
				"Different sizes\n";
				exit(1);
		}
	#endif

	unsigned int n = arr1.dims();

	SqMatrix res(n);

	for(unsigned int i = 0; i < n; ++i)
		for(unsigned int j = 0; j < n; ++j)
			res.set(i,j, arr1.get(i,j) + arr2.get(i,j));

	return res;
}



// Add arrays
inline SqMatrix operator - (
	const SqMatrix &arr1, 
	const SqMatrix &arr2) 
{ 
	#ifdef __SAFE_LIBRARY__
		if(arr1.dims() != arr2.dims()) {
			std::cout << "SqMatrix operator + error: "
				"Different sizes\n";
				exit(1);
		}
	#endif

	unsigned int n = arr1.dims();

	SqMatrix res(n);

	for(unsigned int i = 0; i < n; ++i)
		for(unsigned int j = 0; j < n; ++j)
			res.set(i,j, arr1.get(i,j) - arr2.get(i,j));

	return res;
}






// Make number * array operator
inline SqMatrix operator * (
	const c_type number,
	const SqMatrix & arr)
{
	unsigned int n = arr.dims();

	SqMatrix res(n);

	for(unsigned int i = 0; i < n; ++i)
		for(unsigned int j = 0; j < n; ++j)
			res.set(i,j, arr.get(i,j) * number);

	return res;
}



#endif
