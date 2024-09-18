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

