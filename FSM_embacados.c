/*  FSM =>  S1(pega proto, le STX) -> S2(le Qtd Dados) -> S3(le Dados) ->
S4(le chk) -> S5(le ETX) -> S1(le novo prot) ;; S6(imprime parte que houve erro)*/

/* S0 => S0,S1,S5*/
/* S1 => S1*/
/* S2 => S2,S3*/
/* S3 => S4,S5*/
/* S4 => S0,S5*/
/* S5 => S0*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

char mensagem[9] = {0x02, 0x05, 2, 1, 1, 5, 4, 1024, 0x03};

static int leSTX(uint8_t i);
static int leQTD(uint8_t i, uint8_t *num, char *buffer);
static int leDADOS(uint8_t *i, uint8_t num, char *buffer);
static int checkSUM(uint8_t i, char chk_rec);
static int leETX(uint8_t i);
static void msg(uint8_t n, char *buffer);

int main(){
    enum States {CHECK_STX = 0, QTD_DADOS, LE_DADOS, CHECKSUM, CHECK_ETX,FIM_TRANSMISSAO};
    enum States state = CHECK_STX;
    uint8_t err = 0;
    uint8_t cont_test = 0;
    uint8_t *num = 0;
    uint8_t iterator = 0;
    char *buffer;
    char data;
    char chk_rec = 0;
    char chk_tran;
    bool stx;
    bool qtd;
    bool chk;
    bool etx;

    for (int i = 0; i <= 100; i++)
    {
        switch (state)
        {
        case CHECK_STX:
            // Le inicio da transmissao

            stx = leSTX(iterator);
            cont_test++;
            iterator++;
            if(stx == false){
                state = FIM_TRANSMISSAO;
                err = 1;      
            }
            else state = QTD_DADOS;
            break;

        case QTD_DADOS:
            // Le quantidade de dados
            qtd = leQTD(iterator, &num, buffer);            
            cont_test++;
            iterator++;
            if(qtd == false){
                state = FIM_TRANSMISSAO;
                err = 2;
            }
            else state = LE_DADOS;
            break;

        case LE_DADOS:
            // Le os dados
            chk_rec = leDADOS(&iterator, num, &buffer);
            cont_test++;
            if (chk_rec == NULL){
                state = FIM_TRANSMISSAO;
                err = 3;
            }
            else state = CHECKSUM;
            break;

        case CHECKSUM:
            // Faz checksum
            printf("interador: %d\n", iterator);
            chk_tran = checkSUM(iterator, chk_rec);
            cont_test++;
            iterator++;
            if(chk_tran == false){
                state = FIM_TRANSMISSAO;
                err = 4;
            }
            else state = CHECK_ETX;
            break;

        case CHECK_ETX:
            // Le fim da transmissao
            etx = leETX(iterator);
            cont_test++;
            if(etx == false){
                err = 5;
            }
            state = FIM_TRANSMISSAO;
            break;

        case FIM_TRANSMISSAO:
            // Imprime erro na tela
            if (err != 0){
                printf("Houve erro na função %d, %d testes foram feitos. Reiniciando recebimento de protocolo.\n", err,cont_test);
            }
            else {
                uint8_t n = sizeof(buffer) / sizeof(int*);
                //printf("Transmissao completa. %d testes feitos. Aguardando nova transmissão.\n", cont_test);
                msg(n, &buffer);
                
                state = CHECK_STX;
            }
            break;

        default:
            state = CHECK_STX;
            break;
        }
    }
    
    return 0;
}

static int leSTX(uint8_t i){
    if (mensagem[i] == 0x02){
        printf("STX: %d \n", mensagem[i]);
        return true;
    }
    else return false;
}

static int leQTD(uint8_t i, uint8_t *num, char *buffer){
    if (mensagem[i] > 0){
        buffer = (char*) malloc(mensagem[i] * sizeof(char));
        *num = mensagem[i];
        printf("QTD: %d \n", mensagem[i]);
        return true;
    }
    else return false;
}

static int leDADOS(uint8_t *i, uint8_t num, char *buffer){
    uint8_t qtd_dados = num;
    uint8_t chk;
    printf("i: %d \n", *i);
    // printf("buffer: ");
    while(qtd_dados > 0){
        buffer[qtd_dados - num] = mensagem[*i];
        chk = buffer[qtd_dados - num] ^ chk;
        printf("buffer: %d, i: %d, qtd: %d, index: %d, num: %d \n", mensagem[*i], *i, qtd_dados, qtd_dados - num, num);
        *i = *i + 1;
        qtd_dados--;
    }
    printf("CHK-DADOS: %d \n", chk);
    return chk;
}

static int checkSUM(uint8_t i, char chk_rec){
    if (chk_rec == mensagem[i]){
        return true;
    }
    else return false;
}

static int leETX(uint8_t i){
    if (mensagem[i] == 0x03){
        return true;
    }
    else return false;
}

static void msg(uint8_t n, char *buffer) {
    uint8_t aux = 0;
    printf("buffer: ");

    while(aux <= n){
        printf("%d, ", buffer[n - aux]);
        aux++;
    }
    printf("teste: %d, %d, %d", buffer[-1], buffer[0], buffer[1]);

    printf("\n");
}