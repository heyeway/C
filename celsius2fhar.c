#include <stdio.h>

int main(void)
{
    float fhar, celsius;

    printf("celsius to fhar table:\n");
    for (celsius = 0; celsius <= 30; celsius += 1) {
        fhar = celsius * (9.0 / 5.0) + 32;
        printf("%f\t%f\n", celsius, fhar);
    }
    return 0;
}
