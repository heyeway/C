#include <stdio.h>

int F2C(int F);

int main(void)
{
    int F;
    F = 1;
    printf("fahr to celsius table:\n");
    printf("%3d\t%6d\n", F, F2C(F));

    for (F = 20; F <= 300; F += 20) {
        printf("%3d\t%6d\n", F, F2C(F));
    }
    return 0;
}

int F2C(int F)
{
    return (5.0/9) * (F - 32);  /* int divide int results int, so 5 divide 9 will get 0! */
}
