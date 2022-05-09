#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main()
{
    uint32_t cnt = 0;
    uint32_t x = 1;

    if (x >= 0)
    {
        while (x) {
            cnt++;
            x >>= 1;
            printf("%d, ", x);
        }
    }
    

    // return cnt - 1;

    printf("resultado: %d \n", cnt);

    return 0;
}