#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>

#include "CMatrix2.hpp"

using namespace std;

// A simple function to print a matrix to stdout.
template <class T>
void PrintMatrix(CMatrix2<T> matrix) {
	int nRows = matrix.getNumberRow();
	int nCols = matrix.getNumberCols();
	for (int row = 0; row < nRows; ++row)  {
		for (int col = 0; col < nCols; ++col)
			cout << std::fixed << std::setprecision(3) << matrix.getElement(row, col) << "  ";
		
		cout << endl;

	} // for

} // PrintMatrix

int main()
{
	cout << "Code to test CMatrix2" << endl;

	// *******************************************************************
	// Create an instance of the qbMatrix2 class.
	// This will contain a simple 2D 3x4 matrix
	double simpleData[12] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
	CMatrix2<double> testMatrix(3, 4, simpleData);

	// Extract and print the elements of testMatrix.
	cout << endl << "**************************" << endl;
	cout << "3x4 matrix test (testMatrix)." << endl;
	PrintMatrix(testMatrix);

	// *******************************************************************
	// Test element retrieval.
	cout << endl << "**************************" << endl;
	cout << "Test element retrieval." << endl;
	cout << "Element (0,0) = " << testMatrix.getElement(0, 0) << endl;
	cout << "Element (1,0) = " << testMatrix.getElement(1, 0) << endl;
	cout << "Element (2,0) = " << testMatrix.getElement(2, 0) << endl;
	cout << "Element (0,1) = " << testMatrix.getElement(0, 1) << endl;
	cout << "Element (1,1) = " << testMatrix.getElement(1, 1) << endl;
	cout << "Element (2,1) = " << testMatrix.getElement(2, 1) << endl;
	cout << "Element (5,5) = " << testMatrix.getElement(5, 5) << endl;

	// *******************************************************************
	// Test matrix multiplication.
	cout << endl << "**************************" << endl;
	cout << "Test matrix multiplication." << endl;
	double simpleData2[12] = { 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0 };
	CMatrix2<double> testMatrix2(4, 3, simpleData2);
	cout << "4x3 matrix (testMatrix2)" << endl;
	PrintMatrix(testMatrix2);
	cout << "Multiplication (testMatrix * testMatrix2) result:" << endl;
	CMatrix2<double> multTest1 = testMatrix * testMatrix2;
	PrintMatrix(multTest1);

	cout << endl << "**************************" << endl;
	cout << "testMatrix2 * testMatrix:" << endl;
	CMatrix2<double> multTest2 = testMatrix2 * testMatrix;
	PrintMatrix(multTest2);

	cout << endl << "**************************" << endl;
	cout << "Test multiplication of column vector by matrix." << endl;
	double columnData[3] = { 1.5, 2.5, 3.5 };
	double squareData[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	CMatrix2<double> testColumn(3, 1, columnData);
	CMatrix2<double> squareMatrix(3, 3, squareData);
	cout << "Column vector = " << endl;
	PrintMatrix(testColumn);
	cout << "Square matrix = " << endl;
	PrintMatrix(squareMatrix);
	cout << "Column vector * Square matrix = " << endl;
	PrintMatrix(testColumn * squareMatrix);
	cout << "Square matrix * Column vector = " << endl;
	PrintMatrix(squareMatrix * testColumn);
	cout << "Square matrix + 1.0 = " << endl;
	CMatrix2<double> squareMatrix2 = squareMatrix + 1.0;
	PrintMatrix(squareMatrix2);
	cout << "(Square matrix + 1.0) * Column vector = " << endl;
	PrintMatrix(squareMatrix2 * testColumn);

	// *******************************************************************
	// Test equality operator
	cout << endl << "**************************" << endl;
	cout << "Test equility operator." << endl;
	cout << "testMatrix == testMatrix2: " << (testMatrix == testMatrix2) << endl;
	cout << "testMatrix2 == testMatrix: " << (testMatrix2 == testMatrix) << endl;
	cout << "(Let testMatrix3 = testMatrix)" << endl;
	CMatrix2<double> testMatrix3 = testMatrix;
	cout << "testMatrix == testMatrix3: " << (testMatrix == testMatrix3) << endl;
	cout << "testMatrix3 == testMatrix: " << (testMatrix3 == testMatrix) << endl;

	// *******************************************************************
	// Test matrix addition by scaler.
	cout << endl << "**************************" << endl;
	cout << "Test addition by scaler" << endl;
	cout << "testMatrix + 2.0 = " << endl;
	PrintMatrix(testMatrix + 2.0);
	cout << endl;
	cout << "2.0 + testMatrix = " << endl;
	PrintMatrix(2.0 + testMatrix);

	// *******************************************************************
	// Test matrix subtraction by scaler.
	cout << endl << "**************************" << endl;
	cout << "Test addition by scaler" << endl;
	cout << "testMatrix - 2.0 = " << endl;
	PrintMatrix(testMatrix - 2.0);
	cout << endl;
	cout << "2.0 - testMatrix = " << endl;
	PrintMatrix(2.0 - testMatrix);

	// *******************************************************************
	// Test matrix multiplication by scaler.
	cout << endl << "**************************" << endl;
	cout << "Test multiplication by scaler" << endl;
	cout << "testMatrix * 2.0 = " << endl;
	PrintMatrix(testMatrix * 2.0);
	cout << endl;
	cout << "2.0 * testMatrix = " << endl;
	PrintMatrix(2.0 * testMatrix);
	
	return 0;
}