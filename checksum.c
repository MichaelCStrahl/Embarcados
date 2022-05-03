#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    char mensagem[4] = {3, 2, 1, 1};
    uint8_t chk = 0;

    for (size_t i = 1; i <= mensagem[0]; i++)
    {
        chk = mensagem[i] ^ chk;
        printf("chk: %d, msg: %d, qtd: %d\n", chk, mensagem[i], mensagem[0]);
    }
    
}