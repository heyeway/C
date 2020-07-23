#include <stdio.h>

int main()
{
    float celsius, fhar;

    printf("reverse celsius to fhar table:\n");
    for (fhar = 300; fhar >= 0; fhar -= 20) {
        celsius = (5.0 / 9) * (fhar - 32);
        printf("%f\t%f\n", celsius, fhar);
    }
    return 0;
}
