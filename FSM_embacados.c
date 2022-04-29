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

char mensagem[6] = {0x02, 0x02, 2, 4, 6, 0x03};

void main(){
    enum States {CHECK_STX = 0, QTD_DADOS, LE_DADOS, CHECKSUM, CHECK_ETX,FIM_TRANSMISSAO};
    enum States state = CHECK_STX;
    uint8_t err;
    uint8_t cont_test;
    uint8_t num;
    uint8_t iterator=0;
    char *buffer;
    char data;
    char chk_sum=0;
    char chk_tran;
    bool stx;
    bool qtd;
    bool chk;
    bool etx;

    for (;;)
    {
        switch (state)
        {
        case CHECK_STX:
            // Le inicio da transmissao
            stx = leSTX();
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
            qtd = leQTD(buffer,num);
            cont_test++;
            iterator;
            if(qtd == false){
                state = FIM_TRANSMISSAO;
                err = 2;
            }
            else state = LE_DADOS;
            break;
        case LE_DADOS:
            // Le os dados
            data = leDADOS(num,buffer,chk_sum,chk_sum);
            cont_test++;
            iterator++;
            if (data == NULL){
                state = FIM_TRANSMISSAO;
                err = 3;
            }
            else state = CHECKSUM;
            break;
        case CHECKSUM:
            // Faz checksum
            chk = checkSUM(data);
            cont_test++;
            iterator++;
            if(chk == false){
                state = FIM_TRANSMISSAO;
                err = 4;      
            }
            else state = CHECK_ETX;  
            break;
        case CHECK_ETX:
            // Le fim da transmissao
            etx = leETX();
            cont_test++;
            iterator++;
            if(etx == false){
                err = 5;
            }
            state = FIM_TRANSMISSAO;
            break;
        case FIM_TRANSMISSAO:
            // Imprime erro na tela
            if (err != 0){
                printf("Houve erro na função %s , %d testes foram feitos. Reiniciando recebimento de protocolo.\n",state,cont_test);
            }
            else printf("Transmissao completa. %d testes feitos. Aguardando nova transmissão.\n",cont_test);
            state = CHECK_STX;
            break;
        default:
            state = CHECK_STX;
            break;
        }
    }
    
    return 0;
}

static int leSTX(){
    if (mensagem[0]==0x02){
        return true;
    }
    else return false;
}

static int leQTD(char * buffer,uint8_t num){
    if (mensagem[1]>0){
        buffer = (char*) malloc(mensagem[1] * sizeof(char));
        num = mensagem[1];
        return true;
    }
    else return false;
}

static int leDADOS(char * buffer,uint8_t num,char chk_sum,uint8_t iterator){
    uint8_t qtd = mensagem[1];
    while(num>0){
        buffer[qtd - num] = mensagem[iterator];
        chk_sum = buffer[qtd - num] ^ chk_sum;
        iterator++;
        num--;
    }
    return chk_sum;
}

static int checkSUM(char data,uint8_t iterator){
    if (data == mensagem[iterator]){
        return true;
    }
    else return false;
}

static int leETX(uint8_t iterator){
    if (mensagem[iterator+1]==0x03){
        return true;
    }
    else return false;
}