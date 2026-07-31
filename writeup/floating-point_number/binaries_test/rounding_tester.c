#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void){
	float a = 0.1f; //số thực vô hạn
	int o,z;
	uint32_t raw;

	memcpy(&raw, &a, 4);

	printf(" infinity floating point numbers: %.23f\n raw: %08x\n binary: ",a,raw);

	for(int i = 0; i < 35; i++){
		o = (int)a; //ép kiểu để lấy phần nguyên, kết quả đầu tiên là 0
		printf("%d",o);
		a -= o; //lấy phần thập phân ví dụ 1 + 1.23 = 0.23
		a *= 2; //theo quy định encode thì phần thập phân nhân 2
	}
		printf("\n");
	return 0;
}
