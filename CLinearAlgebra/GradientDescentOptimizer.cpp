#include "GradientDescentOptimizer.hpp"
#include <iostream>
#include <fstream>
#include <math.h>

Gradient::GradientDescentOptimizer::GradientDescentOptimizer() {
	// Set defaults.
	number_of_dimensions_ = 0;
	step_size_ = 0.0;
	max_iterations_ = 1;
	h_ = 0.001;
	gradient_threshold_ = 1e-09;

} // GradientDescentOptimizer

Gradient::GradientDescentOptimizer::~GradientDescentOptimizer() {} // ~GradientDescentOptimizer

void Gradient::GradientDescentOptimizer::setObjectiveFunction(function<double(vector<double>*)> objective_function) {
	objective_function_ = objective_function;

} // setObjectiveFunction

void Gradient::GradientDescentOptimizer::setInitialPoint(const vector<double> initial_point) {
	// Copy the start point.
	initial_point_ = initial_point;

	// Determine the number of degrees of freedom.
	number_of_dimensions_ = initial_point_.size();

} // setInitialPoint

void Gradient::GradientDescentOptimizer::setStepSize(double step_size) {
	 step_size_ = step_size;

} // setStepSize

void Gradient::GradientDescentOptimizer::setMaxIterations(int max_iterations) {
	max_iterations_ = max_iterations;

} // setMaxIterations

void Gradient::GradientDescentOptimizer::setGradientThreshold(double gradient_threshold) {	
	gradient_threshold_ = gradient_threshold;

} // setGradientThreshold

bool Gradient::GradientDescentOptimizer::Optimize(vector<double>* function_location, double* function_value) {
	// Set the currentPoint to the startPoint.
	current_point_ = initial_point_; 

	// Loop up to max iterations or until threshold reached.
	int iterCount = 0; 
	double gradientMagnitude = 1.0; 
	while ((iterCount < max_iterations_) && (gradientMagnitude > gradient_threshold_))
	{
		// Compute the gradient vector.
		std::vector<double> gradientVector = ComputeGradientVector(); 
		gradientMagnitude = ComputeGradientMagnitude(gradientVector); 

		// Compute the new point.
		std::vector<double> newPoint = current_point_; 
		for (int i = 0; i < number_of_dimensions_; ++i) 
		{
			newPoint[i] += -(gradientVector[i] * step_size_); 
		}

		// Update the current point.
		current_point_ = newPoint; 

		// Increment the iteration counter.
		iterCount++; 
	}

	// Return the results.
	*function_location = current_point_;  
	*function_value = objective_function_(&current_point_); 

	return 0;

} // Optimize

double Gradient::GradientDescentOptimizer::ComputeGradient(int dimension) {
	// Make a copy of the current location.
	std::vector<double> newPoint = current_point_;

	// Modify the copy, according to h and dim.
	newPoint[dimension] += h_;

	// Compute the two function values for these points.
	double funcVal1 = objective_function_(&current_point_);
	double funcVal2 = objective_function_(&newPoint);

	// Compute the approximate numerical gradient.
	return (funcVal2 - funcVal1) / h_;

} // ComputeGradient

double Gradient::GradientDescentOptimizer::ComputeGradientMagnitude(vector<double> gradient_vector) {
	double vectorMagnitude = 0.0; 
	for (int i = 0; i < number_of_dimensions_; ++i)
		vectorMagnitude += gradient_vector[i] * gradient_vector[i];

	return sqrt(vectorMagnitude);
	 
} // ComputeGradientMagnitude

vector<double> Gradient::GradientDescentOptimizer::ComputeGradientVector() {
	std::vector<double> gradientVector = current_point_; 
	for (int i = 0; i < number_of_dimensions_; ++i) 
		gradientVector[i] = ComputeGradient(i); 

	return gradientVector; 
	
} // ComputeGradientVector
