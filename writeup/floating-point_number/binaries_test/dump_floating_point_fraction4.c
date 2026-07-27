#include <stdio.h>

int main(void){
	float x = 0.1;
	float y = 0.2;
	printf("dump fration 23bit : %.23f\n",x + y); //xấp xỉ 0.3 chứ ko phải tuyệt đối do rounting
}