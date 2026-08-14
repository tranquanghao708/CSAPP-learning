#include <stdio.h>
#include <fenv.h>

#pragma STDC FENV_ACCESS ON

int main(void){
	if (fesetround(FE_UPWARD) != 0){
		printf("changed mode failed\n");
		return -1;
	} //chuyển đỏi sang round toward positive infinity

    volatile float a = 1.0f;
    volatile float b = 0x1.000002p-24f;

    float result = a + b;

    printf("%.20f\n", result);

	return 0;
}