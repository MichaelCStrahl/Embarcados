#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* macros de testes - baseado em minUnit: www.jera.com/techinfo/jtns/jtn002.html */
#define verifica(mensagem, teste) do { if (!(teste)) return mensagem; } while (0)
#define executa_teste(teste) do { char *mensagem = teste(); testes_executados++; \
                                if (mensagem) return mensagem; } while (0)
int testes_executados = 0;

static char * executa_testes(void);
static int firstbiteq1 (uint32_t x);

int main()
{
	 char *resultado = executa_testes();
     if (resultado != 0)
     {
         printf("%s\n", resultado);
     }
     else
     {
         printf("TODOS OS TESTES PASSARAM\n");
     }
     printf("Testes executados: %d\n", testes_executados);

     return resultado != 0;
}

/* Função que calcula a posição do MSB */
/***********************************************/
static int msbPosition(uint32_t x)
{
    //                                 /* 1 -> position */
    //if(x == 1) return 0;            // 01 -> 0
    //                                 /* 2 -> position */
    //if(x == 2 || x == 3) return 1;  // 10 -> 1
    //                                 /* 3 -> position */
    //                                // 11 -> 1
    //                                 /* 4 -> position */
    //if(x == 4) return 2;           // 100 -> 2
    //else return -1;

    uint32_t count = 0;

    while (x)
    {
        count++;
        x >>= 1;
    }

    return count - 1;
    
}

static char * teste_retorna0_caso_1(void)
{
    verifica("erro: deveria retornar 0", msbPosition(1) == 0);
    return 0;
}

static char * teste_retorna1_caso_2(void)
{
    verifica("erro: deveria retornar 1", msbPosition(2) == 1);
    return 0;
}

static char * teste_retorna1_caso_3(void)
{
    verifica("erro: deveria retornar 1", msbPosition(3) == 1);
    return 0;
}

static char * teste_retorna2_caso_4(void)
{
    verifica("erro: deveria retornar 2", msbPosition(4) == 2);
    return 0;
}

static char * teste_retorna2_caso_5(void)
{
    verifica("erro: deveria retornar 2", msbPosition(5) == 2);
    return 0;
}

static char * teste_retorna3_caso_8(void)
{
    verifica("erro: deveria retornar 3", msbPosition(8) == 3);
    return 0;
}

static char * teste_retorna4_caso_16(void)
{
    verifica("erro: deveria retornar 4", msbPosition(16) == 4);
    return 0;
}

/***********************************************/

static char * executa_testes(void)
{
	/* Executa testes */
    executa_teste(teste_retorna0_caso_1);
    executa_teste(teste_retorna1_caso_2);
    executa_teste(teste_retorna1_caso_3);
    executa_teste(teste_retorna2_caso_4);
    executa_teste(teste_retorna2_caso_5);
    executa_teste(teste_retorna3_caso_8);
    executa_teste(teste_retorna4_caso_16);
    return 0;
}