#pragma once

/************************************************************************

							HEADER

*************************************************************************/

template <class T>
class CMatrix2 {
public:
	// Constructors
	//------------------------------------------------------------------
	CMatrix2();
	CMatrix2(int number_rows, int number_cols);
	CMatrix2(int number_rows, int number_cols, const T * input_data);
	CMatrix2(const CMatrix2<T>& input_matrix);
	//------------------------------------------------------------------
	
	//Destructor
	~CMatrix2();

	// Configuration
	bool Resize(int number_rows, int number_cols);

	// Element Access
	//-------------------------------------------------
	bool setElement   (int row, int col, T element_value);
	T    getElement   (int row, int col); 
	int  getNumberRow ();
	int  getNumberCols();
	//-------------------------------------------------

	// Overload ==
	bool operator== (const CMatrix2<T>& rhs);
	

	// Overload +, - and * operators (friends).
	//-----------------------------------------------------------------------------------------------
	template <class U> friend CMatrix2<U> operator+ (const CMatrix2<U>& lhs, const CMatrix2<U>& rhs);
	template <class U> friend CMatrix2<U> operator+ (const U& lhs, const CMatrix2<U>& rhs);
	template <class U> friend CMatrix2<U> operator+ (const CMatrix2<U>& lhs, const U& rhs);

	template <class U> friend CMatrix2<U> operator- (const CMatrix2<U>& lhs, const CMatrix2<U>& rhs);
	template <class U> friend CMatrix2<U> operator- (const U& lhs, const CMatrix2<U>& rhs);
	template <class U> friend CMatrix2<U> operator- (const CMatrix2<U>& lhs, const U& rhs);

	template <class U> friend CMatrix2<U> operator* (const CMatrix2<U>& lhs, const CMatrix2<U>& rhs);
	template <class U> friend CMatrix2<U> operator* (const U& lhs, const CMatrix2<U>& rhs);
	template <class U> friend CMatrix2<U> operator* (const CMatrix2<U>& lhs, const U& rhs);
	//-----------------------------------------------------------------------------------------------

private:
	int SubsituteToIndex(int row, int col);

private:
	T* matrix_data_;
	int number_rows_, number_cols_, number_elements_;

}; // CMatrix2


/************************************************************************

						IMPLEMENTATION

*************************************************************************/

/* 
*CONSTRUCTOR/DESTRUCTOR
*/

// Default Constructor
template<class T>
CMatrix2<T>::CMatrix2() {
	number_rows_ = 1;
	number_cols_ = 1;
	number_elements_ = 1;
	matrix_data_ = nullptr;

} // CMatrix2

// Construct empty matrix - all elements are 0
template<class T>
CMatrix2<T>::CMatrix2(int number_rows, int number_cols) {
	number_rows_ = number_rows;
	number_cols_ = number_cols;
	number_elements_ = number_rows_ * number_cols_; 
	matrix_data_ = new T[number_elements_];
	for (int i = 0; i < number_elements_; ++i)
		matrix_data_[i] = 0.0; 

} // CMatrix2(int number_rows, int number_cols)

// Construct from a const linear array
template<class T>
CMatrix2<T>::CMatrix2(int number_rows, int number_cols, const T* input_data) {
	number_rows_ = number_rows; 
	number_cols_ = number_cols;
	number_elements_ = number_rows_ * number_cols_; 
	matrix_data_ = new T[number_elements_];
	for (int i = 0; i < number_elements_; ++i)
		matrix_data_[i] = input_data[i]; 

} // CMatrix2(int number_rows, int number_cols, const T* input_data)

// A copy constructor
template<class T>
CMatrix2<T>::CMatrix2(const CMatrix2<T>& input_matrix) {
	number_rows_ = number_rows;
	number_cols_ = number_cols;
	number_elements_ = number_rows_ * number_cols_;
	matrix_data_ = new T[number_elements_]; 
	for (int i = 0; i < number_elements_; ++i)
		matrix_data_[i] = input_matrix.matrix_data_[i];    

} // CMatrix2(const CMatrix2<T>& input_matrix)
