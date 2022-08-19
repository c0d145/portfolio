/*
* This program realizes the calculation of the harmonic series and calculates
* e and pi with the help of different series.
*
* Author: c0d145
* Created: 2022-04-14
* Updated: 2022-04-28 (Comments added)
*/

#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

/* int in C++ have a maximum value of 2147483647 and
 * 4294967295 as unsigned int.
 * After some tries I replaced int with unsigned long long int which
 * extends the value range to 18,446,744,073,709,551,615.
 * This make it possible to calculate e until n=33.
 */
 
unsigned long long int factorial(int num)
{
	unsigned long long int fact_num = 1;
	for(int i = 1; i <= num; ++i)
	{
		fact_num *= i;
	}
	return fact_num;
}

void calculate_harmonic(int steps, bool print_single_steps) 
{
	/*
	* Float is precise for 7, double for 15 digits.
	* https://docs.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-170
	* Weshalb double die genaueren Ergebnisse liefert.
	* Forward gives bad / worse results as follow up values are "flattend".
	* That's not the case with backward method.
	*/ 
	float harmonic_forward_f = 0.0;
	float harmonic_backward_f = 0.0;
	double harmonic_forward_d = 0.0;
	double harmonic_backward_d = 0.0;

	for (int i=1;i <= steps; i++)
	{
		harmonic_forward_f += float(1.0)/float(i);
		harmonic_forward_d += double(1.0)/double(i);
		harmonic_backward_f += float(1.0)/float(steps+1-i);
		harmonic_backward_d += double(1.0)/double(steps+1-i);

		if(print_single_steps) {
			std::cout << "Harmonic series forward  until n=" << i << " with Float:  " << harmonic_forward_f << std::endl;
			std::cout << "Harmonic series forward  until n=" << i << " with Double: " << harmonic_forward_d << std::endl;
			std::cout << "Harmonic series backward until n=" << i << " with Float:  " << harmonic_backward_f << std::endl;
			std::cout << "Harmonic series backward until n=" << i << " with Double: " << harmonic_backward_d << std::endl;
		}
	}
	
	std::cout << "Harmonic series forward  until n=" << steps << " with Float:  " << harmonic_forward_f << std::endl;
	std::cout << "Harmonic series forward  until n=" << steps << " with Double: " << harmonic_forward_d << std::endl;;
	std::cout << "Harmonic series backward until n=" << steps << " with Float:  " << harmonic_backward_f << std::endl;
	std::cout << "Harmonic series backward until n=" << steps << " with Double: " << harmonic_backward_d << std::endl;;
}

double calculate_euler(int steps, bool print_single_steps)
{
	double euler = 0.0;
	for (int i=0;i < steps; i++)
	{
		euler += double(1.0)/double(factorial(i));
		if(print_single_steps) {
			cout << "e= " << euler << " for n=" << i << std::endl;
		}
	}
	std::cout << "1. e after n=" << steps << ": " << euler << std::endl;
	return euler;
}

double calculate_pi_1(int steps, bool print_single_steps)
{
	double pi = 0.0;
	for (int i=1;i < steps; i++)
	{
		double numerator = std::pow(-1.0, i-1);
		double denominator = 2*i-1;
		
		pi += numerator/denominator;
		if(print_single_steps) {
			cout << "pi= " << 4*pi << " for n=" << i << std::endl;
		}
	}
	std::cout << "2. pi after n=" << steps << ": " << 4*pi << std::endl;
	return 4*pi;
}

double calculate_pi_2(int steps, bool print_single_steps)
{
	double pi = 0.0;
	double first_sum = 0.0;
	double second_sum = 0.0;
	for (int i=1;i < steps; i++)
	{
		double numerator = std::pow(-1.0, i-1);
		double denominator_first_sum = std::pow(5, 2*i-1) * (2*i-1);
		double denominator_second_sum = std::pow(239, 2*i-1) * (2*i-1);

		first_sum += numerator / denominator_first_sum;
		second_sum += numerator / denominator_second_sum;
		pi = 16*first_sum - 4*second_sum;
		if(print_single_steps) {
			cout << "pi= " << 16*first_sum - 4*second_sum << " for n=" << i << std::endl;
		}
	}
	std::cout << "3. pi after n=" << steps << ": " << pi << std::endl;

	return pi;
}

double calculate_pi_3(int steps, bool print_single_steps)
{
	double pi = 0.0;
	for (int i=0;i < steps; i++)
	{
		double factor = (1.0/std::pow(16, i));
		pi += factor * ( 4.0/(8.0*i+1) - 2.0/(8.0*i+4.0) - 1.0/(8.0*i+5.0) - 1.0/(8.0*i+6.0) );
		if(print_single_steps) {
			std::cout << "pi= " << pi << " for n=" << i << std::endl;
		}
	}
	std::cout << "4. pi after n=" << steps << ": " << pi << std::endl;
	return pi;
}


int main() 
{	static int tensix = std::pow(10, 6);
	static int tenseven = std::pow(10, 7);
	static long double euler_precise = 2.7182818284590452353602874713526624977572470936999595749669676277;
	static long double pi_precise    = 3.1415926535897932384626433832795028841971693993751058209749445923;
	bool print_single_steps = false;

	// Increase the precision of cout for double und float.
	std::cout.precision(12);
	calculate_harmonic(tensix, print_single_steps);
	calculate_harmonic(tenseven, print_single_steps);
	
	double euler = calculate_euler(16, print_single_steps);
	cout << "Deviation of Euler-calculation: " << euler_precise - euler << std::endl;
	/* n=16 enough for 15 digits precision. */
	double pi = calculate_pi_1(42, print_single_steps);
	cout << "Deviation of pi-calculation: " << pi_precise - pi << std::endl;
	/* Doesn't reach 15 digit precision as n=10^9 computes "forever".	*/
	pi = calculate_pi_2(10, print_single_steps);
	cout << "Deviation of pi-calculation: " << pi_precise - pi << std::endl;
	/* n=10 enough for 15 digits precision.*/
	pi = calculate_pi_3(9, print_single_steps);
	cout << "Deviation of pi-calculation: " << pi_precise - pi << std::endl;
	/* n=9 enough for 15 digits precision. */
	// std::cout << "Faculty is: " << factorial(33) << std::endl;;
	
	return 0;
}
