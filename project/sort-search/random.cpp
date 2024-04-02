#include <limits.h>
const int max_int = INT_MAX;
#include <math.h>
#include <time.h>
#include <cstdlib>

#include "random.h"

Random::Random(bool pseudo)
{
	if (pseudo) { srand(1); }
	else { srand(time(NULL)); }
}
 
double Random::random_real()
{
	double max = max_int + 1.0;
	double temp = (rand() % 1001) / 1000.0;
	if (temp < 0) temp = temp + max;
	return temp / max;
}
 
int Random::random_integer(int low, int high)
{
	if (low > high) { 
		return random_integer(high, low);
	}
	else {
		return (rand() % (high - low) + low);
	}
}
 
int Random::poisson(double mean)
{
	double limit = exp(-mean);
	double product = random_real();
	int count = 0;
	while (product > limit) {
		count++;
		product *= random_real();
	}
	return count;
}
