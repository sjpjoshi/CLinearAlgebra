#pragma once

template <class T>

class CMatrix2 {
public:
	// Constructors
	//------------------------------------------------------------------
	CMatrix2();
	CMatrix2(int number_rows, int number_cols);
	CMatrix2(int number_rows, int number_cols, const T * input_data);
	CMatrix2(const CMatrix2<T>& input_matrix);
	//---------------------

	//Destructor
	~CMatrix2();

	// Configuration
	bool Resize(int number_rows, int number_cols);

	// Element Access
	//-------------------------------------------------
	T getElement(int row, int col);
	bool setElement(int row, int col, T element_value);
	int getNumberRow();
	int getNumberCols();
	//-------------------------------------------------

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

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
*************************************************************************************************/
// Default Constructor
template<class T>
inline CMatrix2<T>::CMatrix2() {
	number_rows_ = 0;
	number_cols_ = 0;
	number_elements_ = 0;
	matrix_data_ = nullptr;

} // CMatrix2

// Construct empty matrix (all elements 0)
template<class T>
CMatrix2<T>::CMatrix2(int number_rows, int number_cols) {
	number_rows_ = number_rows;
	number_cols_ = number_cols;
	number_elements_ = number_rows_ * number_cols_;
	matrix_data_ = new T[number_elements_];
	for (int i = 0; i < number_elements_; i++)
		matrix_data_[i] = 0.0;

} // CMatrix2(int number_rows, int number_cols)

// Construct from const linear array.
template<class T>
CMatrix2<T>::CMatrix2(int number_rows, int number_cols, const T* input_data) {
	number_rows_ = number_rows;
	number_cols_ = number_cols;
	number_elements_ = number_rows_ * number_cols_; 
	matrix_data_ = new T[number_elements_]; 
	for (int i = 0; i < number_elements_; i++) 
		matrix_data_[i] = input_data[i]; 

} // CMatrix2(int number_rows, int number_cols, const T* input_data

// The copy constructor.
template<class T>
CMatrix2<T>::CMatrix2(const CMatrix2<T>& input_matrix) {
	number_rows_ = input_matrix.number_rows_; 
	number_cols_ = input_matrix.number_cols_; 
	number_elements_ = input_matrix.number_elements_;

	matrix_data_ = new T[number_elements_];
	for (int i = 0; i < number_elements_; i++)
		matrix_data_[i] = input_matrix.matrix_data_[i];

} // CMatrix2(const CMatrix2<T>& input_matrix)

template<class T>
CMatrix2<T>::~CMatrix2() {
	if (matrix_data_)
		delete[] matrix_data_;

	matrix_data_ = nullptr;

} // ~CMatrix2

/* **************************************************************************************************
CONFIGURATION FUNCTIONS
*************************************************************************************************/
template<class T>
bool CMatrix2<T>::Resize(int number_rows, int number_cols) {
	number_rows_ = number_rows;
	number_cols_ = number_cols;
	number_elements_ = (number_rows_ * number_cols_);
	delete[] matrix_data_;
	matrix_data_ = new T[number_elements_];
	if (matrix_data_ != nullptr) {
		for (int i = 0; i < number_elements_; i++)
			matrix_data_[i] = 0.0;

		return true;

	} // if
	else
		return false;

} // Resize


/* **************************************************************************************************
ELEMENT ACCESS
*************************************************************************************************/
template<class T>
T CMatrix2<T>::getElement(int row, int col) {
	int linearIndex = SubsituteToIndex(row, col);
	if (linearIndex >= 0)
		return matrix_data_[linearIndex];
	else
		return 0.0;

} // getElement

template<class T>
bool CMatrix2<T>::setElement(int row, int col, T element_value) {
	int linearIndex = SubsituteToIndex(row, col);
	if (linearIndex >= 0) {
		matrix_data_[linearIndex] = element_value;
		return true;

	}  // if
	else
		return false;

} // setElement

template<class T>
int CMatrix2<T>::getNumberRow() {
	return number_rows_;

} // getNumberRow

template<class T>
int CMatrix2<T>::getNumberCols() {
	return number_cols_;

} // getNumberCol


/* **************************************************************************************************
OVERLOAD FRIENDS -> + OPERATOR
*************************************************************************************************/

// Matrix + Matrix
template<class T>
inline CMatrix2<T> operator+(const CMatrix2<T>& lhs, const CMatrix2<T>& rhs) {
	int number_rows = lhs.number_rows_;
	int number_cols = lhs.number_cols_;
	int number_elements = number_rows * number_cols;
	T* temp_result = new T[number_elements];
	for (int i = 0; i < number_elements; i++)
		temp_result[i] = lhs.matrix_data_[i] + rhs.matrix_data_[i];

	CMatrix2<T> result(number_rows, number_cols, temp_result);
	delete[] temp_result;
	return result;

} // operator+(const CMatrix2<U>& lhs, const CMatrix2<U>& rhs)

// Scalar + Matrix
template<class T>
CMatrix2<T> operator+(const T& lhs, const CMatrix2<T>& rhs) {
	int number_rows = rhs.number_rows_; 
	int number_cols = rhs.number_cols_; 
	int number_elements = number_rows * number_cols;
	T* temp_result = new T[number_elements];
	for (int i = 0; i < number_elements; i++)
		temp_result[i] = lhs + rhs.matrix_data_[i];

	CMatrix2<T> result(number_rows, number_cols, temp_result);
	delete[] temp_result;
	return result;

} // operator+(const U& lhs, const CMatrix2<U>& rhs

// Matrix + Scalar
template<class T>
CMatrix2<T> operator+(const CMatrix2<T>& lhs, const T& rhs) {
	int number_rows = lhs.number_rows_;
	int number_cols = lhs.number_cols_;
	int number_elements = number_rows * number_cols;  
	T* temp_result = new T[number_elements]; 
	for (int i = 0; i < number_elements; ++i)
		temp_result[i] = lhs.matrix_data_[i] + rhs;
	 
	CMatrix2<T> result(number_rows, number_cols, temp_result);
	delete[] temp_result;
	return result;

} // operator+(const CMatrix2<U>& lhs, const U& rhs)

/* **************************************************************************************************
OVERLOAD FRIENDS -> - OPERATOR
*************************************************************************************************/
// Matrix - Matrix
template<class T>
inline CMatrix2<T> operator-(const CMatrix2<T>& lhs, const CMatrix2<T>& rhs) {
	int number_rows = lhs.number_rows_; 
	int number_cols = lhs.number_cols_; 
	int number_elements = number_rows * number_cols; 
	T* temp_result = new T[number_elements]; 
	for (int i = 0; i < number_elements; ++i) 
		temp_result[i] = lhs.matrix_data_[i] - rhs.matrix_data_[i];

	CMatrix2 result(number_rows, number_cols, temp_result); 
	delete[] temp_result; 
	return result; 

} //operator-(const CMatrix2<U>& lhs, const CMatrix2<U>& rhs)

// Scalar - Matrix
template<class T>
inline CMatrix2<T> operator-(const T& lhs, const CMatrix2<T>& rhs) {
	int number_rows = rhs.number_rows_;
	int number_cols = rhs.number_cols_; 
	int number_elements = number_rows * number_cols;
	T* temp_result = new T[number_elements];
	for (int i = 0; i < number_elements; ++i)
		temp_result[i] = lhs - rhs.matrix_data_[i];

	CMatrix2<T> result(number_rows, number_cols, temp_result);
	delete[] temp_result;
	return result;

} // operator-(const U& lhs, const CMatrix2<U>& rhs)

// Matrix - Scalar
template<class T>
inline CMatrix2<T> operator-(const CMatrix2<T>& lhs, const T& rhs) {
	int number_rows = lhs.number_rows_;
	int number_cols = lhs.number_cols_;
	int number_elements = number_rows * number_cols;
	T* temp_result = new T[number_elements];
	for (int i = 0; i < number_elements; ++i)
		temp_result[i] = lhs.matrix_data_[i] - rhs;

	CMatrix2<T> result(number_rows, number_cols, temp_result); 
	delete[] temp_result; 
	return result;

} // operator-(const CMatrix2<U>& lhs, const U& rhs)


/* **************************************************************************************************
OVERLOAD FRIENDS -> * OPERATOR
*************************************************************************************************/

// Matrix * Matrix
template<class T>
inline CMatrix2<T> operator*(const CMatrix2<T>& lhs, const CMatrix2<T>& rhs) {
	int r_num_rows = rhs.number_rows_;
	int r_num_cols = rhs.number_cols_;
	int l_num_rows = lhs.number_rows_;
	int l_num_cols = lhs.number_cols_;

	if (l_num_cols == r_num_rows) {
		// This is the standard matrix multiplication condition.
		// The output will be the same size as the RHS.
		T* temp_result = new T[lhs.number_rows_ * rhs.number_cols_];

		// Loop through each row of the LHS.
		for (int lhsRow = 0; lhsRow < l_num_cols; lhsRow++) {
			// Loop through each column on the RHS.
			for (int rhsCol = 0; rhsCol < r_num_rows; rhsCol++) {
				T element_result = static_cast<T>(0.0);
				// Loop through each element of this LHS row.
				for (int lhsCol = 0; lhsCol < l_num_cols; lhsCol++) { 
					// Compute the LHS linear index.
					int lhsLinearIndex = (lhsRow * l_num_cols) + lhsCol;

					// Compute the RHS linear index (based on LHS col).
					// rhs row number equal to lhs column number.
					int rhsLinearIndex = (lhsCol * r_num_cols) + rhsCol; 

					// Perform the calculation on these elements.
					element_result += (lhs.matrix_data_[lhsLinearIndex] * rhs.matrix_data_[rhsLinearIndex]);

				} // for (int lhsCol = 0; lhsCol < l_num_cols; lhsCol++)

				// Store the result.
				int resultLinearIndex = (lhsRow * r_num_cols) + rhsCol; 
				temp_result[resultLinearIndex] = element_result;  

			} // for (int rhsCol = 0; rhsCol < r_num_rows; rhsCol++)

		} // for (int lhsRow = 0; lhsRow < l_num_cols; lhsRow++)

		CMatrix2<T> result(l_num_rows, r_num_cols, temp_result);
		delete[] temp_result;
		return result;

	} // if (l_num_cols == r_num_rows)
	else {
		CMatrix2<T> result(1, 1);
		return result;

	} // else

} // operator*(const CMatrix2<U>& lhs, const CMatrix2<U>& rhs)

// Scalar * Matrix
template<class T>
inline CMatrix2<T> operator*(const T& lhs, const CMatrix2<T>& rhs) {
	int number_rows = rhs.number_rows_;
	int number_cols = rhs.number_cols_;
	int number_elements = number_rows * number_cols;
	T* temp_result = new T[number_elements];
	for (int i = 0; i < number_elements; ++i)
		temp_result[i] = lhs * rhs.matrix_data_[i];

	CMatrix2<T> result(number_rows, number_cols, temp_result);
	delete[] temp_result; 
	return result;

} // operator*(const U& lhs, const CMatrix2<U>& rhs)

// Matrix * Scalar
template<class T>
inline CMatrix2<T> operator*(const CMatrix2<T>& lhs, const T& rhs) {
	int number_rows = lhs.number_rows_;
	int number_cols = lhs.number_cols_;   
	int number_elements = number_rows * number_cols;
	T* temp_result = new T[number_elements];
	for (int i = 0; i < number_elements; ++i)
		temp_result[i] = lhs.matrix_data_[i] * rhs;

	CMatrix2<T> result(number_rows, number_cols, temp_result);
	delete[] temp_result;
	return result;  

} // operator*(const CMatrix2<U>& lhs, const U& rhs)

/* **************************************************************************************************
OVERLOAD FRIENDS -> == OPERATOR
*************************************************************************************************/
template<class T>
inline bool CMatrix2<T>::operator==(const CMatrix2<T>& rhs) {
	// Check if the matricies are the same size, if not return false.
	if ((this->number_rows_ != rhs.number_rows_) || (this->number_cols_ != rhs.number_cols_)) 
		return false;

	// Check if the elements are equal.
	bool flag = true;
	for (int i = 0; i < this->number_elements_; ++i) {
		if (this->matrix_data_[i] != rhs.matrix_data_[i])
			flag = false;

	} // for 

	return flag;

} // operator==(const CMatrix2<T>& rhs)

/* **************************************************************************************************
PRIVATE FUNTIONS
*************************************************************************************************/
template<class T>
inline int CMatrix2<T>::SubsituteToIndex(int row, int col) {
	if ((row < number_rows_) && (row >= 0) && (col < number_cols_) && (col >= 0))
		return (row * number_cols_) + col;
	else
		return -1;

} // SubsituteToIndex