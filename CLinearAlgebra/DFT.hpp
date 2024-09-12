#pragma once

#include "Includes.hpp"

namespace FourierTransform {
	
	// this should be included in math.h, for some reason visual studio does not recongize it 
	# define M_PI 3.14159265358979323846 

	// Functions
	void testDFT();
	vector <complex<double>> DFT(vector<complex<double>> X);
	int getValidInt(const string& prompt, int minValue, int maxValue);
	vector<complex<double>> generateSignal(int N, double signalK, double signalPhase);
	void displayDFTResults(const vector<complex<double>>& Fx, int N, int samplesToDisplay);
	double getValidDouble(const string& prompt, double minValue, double maxValue);

} // FourierTransform