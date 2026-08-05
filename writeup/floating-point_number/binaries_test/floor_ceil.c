#include <math.h>
#include <stdio.h>

int main (void){
	printf(" floor 3.8 = %f\n ceil 3.8 = %f\n floor -3.8 = %f\n ceil -3.8 = %f\n",
	floor(3.8), // 3.0
	ceil(3.8), // 4.0

	floor(-3.8), // -4.0
	ceil(-3.8) // -3.0
	);
}