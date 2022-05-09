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

/* Teste de exemplo - apenas para demonstração */
/***********************************************/
static int firstbiteq1 (uint32_t x)
{
    
    // if(x == 1) return 0;
    // if(x == 2) return 1;
    // if(x == 2147483648) return 31;

    // uint32_t cnt = 0;

    // while (x) {

    //     cnt++;
    //     x = x >> 1;

    // }

    // return cnt - 1;
    
}

static char * teste_retorna0_caso_1(void)
{
    verifica("erro: deveria retornar 0", firstbiteq1(1) == 0);
    return 0;
}

static char * teste_retorna1_caso_2(void)
{
    verifica("erro: deveria retornar 1", firstbiteq1(2) == 1);
    return 0;
}

static char * teste_retorna1_caso_3(void)
{
    verifica("erro: deveria retornar 1", firstbiteq1(3) == 1);
    return 0;
}
/***********************************************/

static char * executa_testes(void)
{
	/* Colocar os testes aqui */
    /* Exemplo fictício!*/
    executa_teste(teste_retorna0_caso_1);
    executa_teste(teste_retorna1_caso_2);
    executa_teste(teste_retorna1_caso_3);
    return 0;
}