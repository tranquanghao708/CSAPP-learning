#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void){
    uint32_t raw = 0x7F800001; // sNaN (theo IEEE754)
    float x;
    memcpy(&x, &raw, sizeof(x));
    printf("%f\n", x);
    return 0;
}