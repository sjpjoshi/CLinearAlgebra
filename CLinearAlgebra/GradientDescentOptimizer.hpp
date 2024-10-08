#pragma once

#include "Includes.hpp"

class GradientDescentOptimizer {

	public:
		GradientDescentOptimizer();
		~GradientDescentOptimizer();

		// Setters
		// --------------------------------------------------------------------------------------------------------
		void setObjectiveFunction(function<double(vector<double>*)> objective_function);
		void setInitialPoint     (const           vector<double>    initial_point);
		void setStepSize         (double step_size);
		void setMaxIterations    (int    max_iterations);
		void setGradientThreshold(double gradient_threshold); 
		// --------------------------------------------------------------------------------------------------------

		bool Optimize(vector<double> *function_location, double * function_value);

	private:
		double		    ComputeGradient(int dimension); 
		double			ComputeGradientMagnitude(vector<double> gradient_vector);

		vector<double>  ComputeGradientVector();

	private:
		int    number_of_dimensions_; 
		int    h_;
		int	   max_iterations_;

		double step_size_; 
		double gradient_threshold_;

		vector<double>					  initial_point_; 
		vector<double>                    current_point_;
		function<double(vector<double>*)> objective_function_; 

}; // GradientDescentOptimizer