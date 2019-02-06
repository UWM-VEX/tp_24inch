#include "main.h"
#include <cmath>



double Utilities::Limit(double value, double max = 127, double min = -127)
{

	if(value > max)
	{
		value = max;
	}
	else if(value < min)
	{
		value = min;
	}

return value;
}
