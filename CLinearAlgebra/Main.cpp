#include "Main.hpp"

// define the object function
double ObjectFunction(vector<double>* function_location) {
	
	double x = function_location->at(0);
	return (x * x * x * x) + (2 * (x*x*x)) - (6*(x*x)) + (4*x) + 2;

} // ObjectFunction

int main() {
	
	// create a function pointer for our object function
	function<double(vector<double>*)> p_object_function{ ObjectFunction };

	// create a test instance of the GradientDescentOptimizer class
	GradientDescentOptimizer solver;

	// assign the object function
	solver.setObjectiveFunction(p_object_function);

	// set a start point
	vector<double> start_point = { -4.0 };
	solver.setInitialPoint(start_point);

	// set the maximum number of iterations
	solver.setMaxIterations(50);

	// set the step size;
	solver.setStepSize(0.01);

	// call optimize 
	vector<double> function_location;
	double function_value;
	solver.Optimize(&function_location, &function_value);

	// Expected output: Function location: -0.0005
	cout << "Function location: " << function_location[0] << endl;
	// Expected output: Function location: 2.5e-07
	cout << "Function Value: " << function_value << endl;

} // main