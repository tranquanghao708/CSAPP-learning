#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    float x = 0.1f + 0.2f;

    uint32_t bits;
    memcpy(&bits, &x, sizeof(bits));

    printf("value = %.20f\n", x);
    printf("bits  = 0x%08X\n", bits);
}
