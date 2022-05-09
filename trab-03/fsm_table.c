#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

/*
Tabela estados/eventos, func/prox = funcao (pode ser NULL) 
e proximo estado (pode ser o atual)
formato:
			evento 0  - evento 1 - ... - evento N
estado 0 - func/prox - func/prox - ...- func/prox
...
estado N - func/prox - func/prox - ...- func/prox
*/

/*  FSM =>  S1(pega proto, le STX) -> S2(le Qtd Dados) -> S3(le Dados) ->
S4(le chk) -> S5(le ETX) -> S1(le novo prot) ;; S6(imprime parte que houve erro)*/

/* S0 => S0,S1,S5*/
/* S1 => S2,S5*/
/* S2 => S2,S3,S5*/
/* S3 => S4,S5*/
/* S4 => S0,S5*/
/* S5 => S0*/

#define ESTADOS 5
#define EVENTOS 2


typedef struct
{
  void (*ptrFunc) (void);
  uint8_t ProxEstado;
} FSM_TABLE;


typedef enum {
  STX=0, QTD, DATA, CHK, ETX
} States;


typedef enum {
    FALSO = 0, VERDADEIRO
} Evento;


struct FSM {
    Evento evento;
    States state;
    uint8_t data;
    uint8_t *buffer;
    uint8_t chksum;
    uint16_t index;
    uint16_t qtd;
} fsm;


void __init__(void){
    fsm.evento = FALSO;
    fsm.state = STX;
    fsm.chksum = 0;
    fsm.index = 0;
    fsm.qtd = 0;
}


/* ---------------------------------------------------------------------------- */
void printData(uint8_t *buffer, uint16_t qtd){
    uint16_t i;
    printf("Dados coletados: \n");
    for(i = 0; i < qtd; i++)
    {
        printf("Dado %d:  %d\n",i,buffer[i]);
    }
}


void leSTX(void){
    if (fsm.data == STX){
        fsm.index = fsm.qtd = 0;
        fsm.chksum = 0;
        fsm.evento = VERDADEIRO;
    }
}


void leQTD(void){
    fsm.qtd = fsm.data;
    fsm.buffer = (uint8_t*) malloc(fsm.qtd * sizeof(uint8_t));
}


void leDATA(void){
    fsm.buffer[fsm.index++] = fsm.data;
    fsm.chksum ^= fsm.data;

    if (--fsm.qtd > 0) fsm.evento = VERDADEIRO;
    else fsm.evento = FALSO;
}


void chkSUM(void){
    if(fsm.data == fsm.chksum) fsm.evento = VERDADEIRO;
    else fsm.evento = FALSO;
}


void leETX(void){
    if(fsm.data == ETX) printData(fsm.buffer,fsm.index);
    fsm.evento = VERDADEIRO;
}


const FSM_TABLE StateTable [ESTADOS][EVENTOS] =
{
    leSTX, STX, leSTX, QTD,
    leQTD, CHK, leQTD, DATA,
    NULL, CHK, leDATA, DATA,
    chkSUM, STX, chkSUM, ETX,
    leSTX, STX, leETX, STX,
};


void percorreFSM(uint8_t *data, uint16_t qtd){
    uint16_t i;
    for (i = 0; i < qtd; i++)
    {
        fsm.data = data[i];
        if (StateTable[fsm.state][fsm.evento].ptrFunc != NULL)
            StateTable[fsm.state][fsm.evento].ptrFunc();

        fsm.state = StateTable[fsm.state][fsm.evento].ProxEstado;
    }
    
}

void testes_fsm(void){
    uint8_t dados1[] = {STX, 2, 1, 2, 3, STX};
    uint8_t dados2[] = {ETX, 2, 1, 2, 3, STX};
    uint8_t dados3[] = {STX, 2, 1, 2, 9, STX};
    uint8_t dados4[] = {STX, 2, 1, 2, 3, ETX};
    
    __init__();

    percorreFSM(dados1,sizeof(dados1));
    percorreFSM(dados2,sizeof(dados2));
    percorreFSM(dados3,sizeof(dados3));
    percorreFSM(dados4,sizeof(dados4));

}

int main(){
    testes_fsm();
    return 0;
}