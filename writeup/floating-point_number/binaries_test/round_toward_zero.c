#include <stdio.h>
#include <fenv.h>

#pragma STDC FENV_ACCESS ON

int main(void){
	if (fesetround(FE_TOWARDZERO) != 0){
		printf("changed mode failed\n");
		return -1;
	} //chuyển đỏi sang round toward zero
	{
	volatile double a = 1.0;
    volatile double b = 10.0;
	double x = a / b;

    printf("%.20f\n", x);
	}
	volatile double a = 2.2;
	volatile double b = 3.4;
	double x = a * b;

	printf("%.20f\n", x);

	return 0;
}