#include <stdio.h>

int main(void){
	float x = 1.0f / 0.0f; //chia cho +0
	float y = 1.0f / -0.0f; // chi cho -0

	printf("1 / +0: %f\n 1 / -0: %f\n",x,y);
	return 0;
}
