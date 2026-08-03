#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
    float a = 0.1f;
    uint32_t raw;
    
    // Bê nguyên 32 bit từ vùng nhớ của a sang raw
    memcpy(&raw, &a, sizeof(raw));

    // Tách 3 thành phần IEEE 754 bằng Bitwise operators
    uint32_t sign     = (raw >> 31) & 0x01; // Bit 31 là cái phần sign
    uint32_t exponent = (raw >> 23) & 0xFF; // Bit 23 -> 30 (8 bits) gán vô exponent
    uint32_t fraction = raw & 0x7FFFFF; // Bit 0 -> 22  (23 bits) fraction

    printf("Sign: %u\n", sign);
    printf("Exponent (Biased): %u (Actual: %d)\n", exponent, exponent - 127);
    printf("fraction (Raw Hex): 0x%06X\nFraction binary: ", fraction);

	//phần lấy mã nhị phân của trường fraction
	int o;
	for(int i = 22; i >= 0; i--){ //cố tình dump quá 3bit
		o = (fraction >> i) & 1;
		printf("%d",o);
	}
	printf("\n");

    return 0;
}
