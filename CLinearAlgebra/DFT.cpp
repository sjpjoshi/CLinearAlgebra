#include "DFT.hpp"

int testDFT() {
	// Get user input for signal properties
	int N = getValidInt("Enter the number of samples (N): ", 10, 10000);
	double signalK = getValidInt("Enter the signal frequency (k): ", 1, 10);

	int results;
	cout << "How many results do you want to output? enter: ";
	cin >> results;

	// Get valid phase input from the user (phase in range [0, 2π])
	double signalPhase = getValidDouble("Enter the signal phase (in radians, between 0 and 2π): ", 0.0, 2 * M_PI);

	// Generate the signal
	vector<complex<double>> signal = generateSignal(N, signalK, signalPhase);

	// Compute the DFT
	vector<complex<double>> Fx = DFT(signal);

	// Display the results
	displayDFTResults(Fx, N, results); // Show first 6 samples
	
} // testDFT

vector <complex<double>> DFT(vector<complex<double>> X) {
	// Determine the number of samples
	int N = X.size();
	int K = N;

	// Allocate memory for internals
	complex<double> sum;

	// Allocate memory for output
	vector<complex<double>> output;
	output.reserve(K);

	// Loop through each k
	for (int k = 0; k < K; ++k) {
		// loop through each n
		sum = complex<double>(0, 0);
		for (int n = 0; n < N; ++n) {
			double real = cos((2 * M_PI) / N * k * n);
			double imaginary = sin((2 * M_PI) / N * k * n);
			complex<double> w(real, -imaginary);
			sum += X[n] * w;

		} // for

		output.emplace_back(sum);

	} // for

	return output;

} // DFT

// Function to get user input with validation
int getValidInt(const string& prompt, int minValue, int maxValue) {
	int value;
	while (true) {
		cout << prompt;
		cin >> value;
		if (cin.fail() || value < minValue || value > maxValue) {
			cin.clear(); // clear the input buffer
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, please enter a number between " << minValue << " and " << maxValue << ".\n";

		} // if
		else 
			break;
		
	} // while

	return value;

} // getValidInt

// Function to get a valid floating-point value for phase input
double getValidDouble(const string& prompt, double minValue, double maxValue) {
	double value;
	while (true) {
		cout << prompt;
		cin >> value;
		if (cin.fail() || value < minValue || value > maxValue) {
			cin.clear(); // Clear the input buffer
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, please enter a value between " << minValue << " and " << maxValue << ".\n";

		} // if
		else 
			break;
		
	} // while

	return value;

} // getValidDouble

// Function to generate the signal
vector<complex<double>> generateSignal(int N, double signalK, double signalPhase) {
	vector<complex<double>> signal;
	signal.reserve(N);

	for (int x = 0; x < N; ++x) {
		double real = cos((2 * M_PI / static_cast<double>(N)) * signalK * static_cast<double>(x) + signalPhase);
		signal.emplace_back(complex<double>(real, 0.0));

	} // for
	return signal;

} // generateSignal

// Function to display the DFT results
void displayDFTResults(const vector<complex<double>>& Fx, int N, int samplesToDisplay) {
	cout << "------------------------------------" << endl;
	cout << "First " << samplesToDisplay << " samples of the output" << endl;
	cout << "\n" << "k\t" << setw(12) << "Real\t" << setw(12) << "Imaginary" << endl;

	for (int i = 0; i < samplesToDisplay; ++i) 
		cout << i << "\t" << setw(12) << Fx[i].real() / static_cast<double>(N) << "\t"
			<< setw(12) << Fx[i].imag() / static_cast<double>(N) << endl;

} // displayDFTResults