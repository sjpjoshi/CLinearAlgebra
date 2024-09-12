#include "GradientDescentOptimizer.hpp"

Gradient::GradientDescentOptimizer::GradientDescentOptimizer() 
	: number_of_dimensions_(0), 
	step_size_(0.0), 
	max_iterations_(1), 
	gradient_threshold_(1e-09), 
	h_(0.001) {} // GradientDescentOptimizer

Gradient::GradientDescentOptimizer::~GradientDescentOptimizer() {} // ~GradientDescentOptimizer

// Function to set the objective functions
void Gradient::GradientDescentOptimizer::setObjectiveFunction(function<double(vector<double>*)> objective_function) {
	objective_function_ = objective_function;

} // setObjectiveFunction

// function to set the inital(start) point and set the number of degrees of freedom
void Gradient::GradientDescentOptimizer::setInitialPoint(vector<double> initial_point) {
	// copy the inital point
	initial_point_ = initial_point;

	// determine the number of degrees of freedom
	number_of_dimensions_ = initial_point_.size();
	cout << "Number of Dimensions: " << number_of_dimensions_ << endl;

} // setInitialPoint 

// function to set the step size
void Gradient::GradientDescentOptimizer::setStepSize(double step_size) {
	step_size_ = step_size;

} // setStepSize

// function to set the max iterations
void Gradient::GradientDescentOptimizer::setMaxIterations(int max_iterations) {
	max_iterations_ = max_iterations;

} // setMaxIterations

// function to set the gradient threshold
// the optimization stops when the gradient magnitude is below this value
void Gradient::GradientDescentOptimizer::setGradientThreshold(double gradient_threshold) {
	gradient_threshold_ = gradient_threshold;

} // setGradientThreshold

// function to perform the optimization
bool Gradient::GradientDescentOptimizer::Optimize(vector<double>* function_location, double* function_value) {
	// set the current point to the start point
	current_point_ = initial_point_; 

	// loop up to max iterations or until threshold is reached
	int iteration_count = 0;
	double gradient_magnitude = 1.0;

	while ((iteration_count < max_iterations_) && (gradient_magnitude > gradient_threshold_)) {

		// compute the gradient vector
		vector<double> gradient_vector = ComputeGradientVector();
		gradient_magnitude = ComputeGradientMagnitude(gradient_vector);
	 
		// Debug output for each iteration
		cout << "Iteration: " << iteration_count << ", Gradient Magnitude: " << gradient_magnitude << endl;  
		cout << "Current Point: " << current_point_[0] << endl;  

		// compute the gradient vector
		vector<double> new_point = current_point_;
		for (int i = 0; i < number_of_dimensions_; ++i) {
			new_point[i] += -(gradient_vector[i] * step_size_);
			cout << "New point: " << new_point[i] << endl;
		}


		// update the current point
		current_point_ = new_point; 

		iteration_count++;

	} // while

	// return the results
	*function_location = current_point_;
	*function_value = objective_function_(&current_point_);

	return 0;

} // Optimize

// function to compute the gradient of the object function in the specific dimension
double Gradient::GradientDescentOptimizer::ComputeGradient(int dimension) {
	// make a copy of the current location
	vector<double> new_point = current_point_;

	// modify the copy according to h and number of dimensions
	new_point[dimension] += h_;

	// compute the two function values for these points
	double function_value_one = objective_function_(&current_point_);
	double function_value_two = objective_function_(&new_point); 

	// compute the approximate numerical values
	return (function_value_two - function_value_one) / h_;

} // ComputeGradient

// function to compute the gradient vector
vector<double> Gradient::GradientDescentOptimizer::ComputeGradientVector() {
	vector<double> gradient_vector = current_point_;
	for (int i = 0; i < number_of_dimensions_; ++i)
		gradient_vector[i] = ComputeGradient(i);

	return gradient_vector; 
	 
} // ComputeGradientVector

// function to compute the gradient magnitude
double Gradient::GradientDescentOptimizer::ComputeGradientMagnitude(vector<double> gradient_vector) {
	double vector_magnitude = 0.0;
	for (int i = 0; i < number_of_dimensions_; ++i)
		vector_magnitude += gradient_vector[i] * gradient_vector[i];

	return sqrt(vector_magnitude); 

} // ComputeGradientMagnitude