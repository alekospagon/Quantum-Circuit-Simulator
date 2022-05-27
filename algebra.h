#ifndef __ALGEBRA__ 
#define __ALGEBRA__ 420

#include <vector>
#include "parameters.h"
#include "comp.h"



// =============================================== //
// =================== 2D ARRAY ================== //
// =============================================== //

// 1D Matrix is an std::vector<comp>

// 2D Square Matrix
// implemented with 1D flattened array
class SqMatrix {
	private:
		// rows and columns
		unsigned int _dims;
		std::vector<comp> _elems;

	public:
		inline SqMatrix(unsigned int d);
		inline SqMatrix(std::vector<std::vector <comp>> e);
		
		// get and dims are don't change the matrix --> const
		inline comp get(unsigned int r, unsigned int c) const;
		inline void set(unsigned int r, unsigned int c, comp e);
		inline unsigned int dims() const { return _dims; }
};




// memory allocate
inline SqMatrix::SqMatrix(unsigned int d) {
	_dims  = d;
	_elems = std::vector<comp> ( d*d );
}


inline SqMatrix::SqMatrix(std::vector<std::vector <comp>> e) {
	unsigned int d = e.size();

	#ifdef __SAFE_LIBRARY__
		for(unsigned int i = 0; i < d; ++i){
			if(e[i].size() != d) {
				std::cout << "Matrix Constructor Error: "
					<< "2D vector is not square\n";
				exit(1);
			}
		}
	#endif

	_elems = std::vector<comp> (d*d);
	_dims  = d;
	for(unsigned int i = 0; i < d; ++i)
		for(unsigned int j = 0; j < d; ++j)
			_elems[i * d + j] = e[i][j];
}


inline comp SqMatrix::get(unsigned int r, unsigned int c) const {
	// you can ignore this. vector will crash anyway
	#ifdef __SAFE_LIBRARY__
		if(r > _dims-1){
			std::cout << "SqMatrix Get_Element Error:"
				"Element row index " << r << " out of range\n";
			exit(1);
		}
		if(c > _dims-1){
			std::cout << "SqMatrix Get_Element Error:"
				"Element column index " << c << " out of range\n";
			exit(1);
		}
	#endif

	return _elems[r * _dims + c];
}


inline void SqMatrix::set(unsigned int r, unsigned int c, comp e){
	// you can ignore this. vector will crash anyway
	#ifdef __SAFE_LIBRARY__
		if(r > _dims-1){
			std::cout << "SqMatrix Set_Element Error:"
				"Element row index " << r << " out of range\n";
			exit(1);
		}
		if(c > _dims-1){
			std::cout << "SqMatrix Set_Element Error:"
				"Element column index " << c << " out of range\n";
			exit(1);
		}
	#endif

	_elems[r * _dims + c] = e;
}












// =============================================== //
// ============= SQUARE MATRIX ALGEBRA =========== //
// =============================================== //




// =========== FUNCTION IMPLEMENTATIONS =========== //


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


	for(unsigned int i = 0; i < dim; ++i) {
		for(unsigned int j = 0; j < dim; ++j)
			// C_ij = a[i/p][j/p] * b[i%p][j%p];
			// dimensions are power of two!!! optimize / and %
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

















// DEBUG INFO
void print_vector(std::vector<c_type> vec) {
	std::cout << "Printing Vector\n";
	for(unsigned int i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << "\n";
}


void print_matrix(const SqMatrix &m) {
	int r = m.dims();

	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < r; ++j)
			print_comp( m.get(i, j) );
		std::cout << "\n";
	}
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