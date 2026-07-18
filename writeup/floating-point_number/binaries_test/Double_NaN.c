#include <math.h>
#include <stdio.h>

int main(void){
	double x = NAN;
	printf("dounle NaN x == x is : %d\n",x == x); // kết quả là 0
	printf("dounle NaN x != x is : %d\n",x != x); // kết quả là 1
	printf("dounle NaN x < x is : %d\n",x < x); // kết quả là 0
	printf("dounle NaN x > x is : %d\n",x > x); // kết quả là 0
	return 0;
}