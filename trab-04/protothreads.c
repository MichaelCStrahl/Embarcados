/**
 * This is a very small example that shows how to use
 * protothreads. The program consists of two protothreads that wait
 * for each other to toggle a variable.
 */

/* We must always include pt.h in our protothreads code. */
#include "pt.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_MESSAGE 9 // Tamanho da mensagem

/* Two flags that the two protothread functions use. */
static int sender_flag, receiver_flag;

/* Main functions */
struct Data {
    uint16_t qtd;
    char *data;
    uint8_t chksum;
    uint16_t etx;
    char msg[SIZE_MESSAGE];
} dt;

int readSTX() {
    if (dt.msg[0] == 0x02) return 0;
    else return -1;
}

int readQTD() {
    if(dt.msg[1] <= 0) return -1;
    else{  
      dt.qtd = dt.msg[1];
      dt.data = (char*) malloc(dt.qtd * sizeof(char));
      return 0;
    }
}

void readDATA() {
    dt.chksum = 0;

    for (size_t i = 0; i < dt.qtd; i++)
    {
        dt.data[i] = dt.msg[2 + i];
        dt.chksum ^= dt.msg[2 + i];
    }    
}

int checkSUM() {
    if (dt.chksum == dt.msg[dt.qtd + 2]) return 0;
    else return -1;
}

int readETX() {
    if (dt.msg[dt.qtd + 3] == 0x03) return 0;
    else return -1;
}

void raiseError(int err){
  switch (err)
  {
  case 1:
    printf("Erro no STX \n");
    break;

  case 2:
    printf("Erro na leitura da quantidade de dados \n");
    break;

  case 3:
    printf("Erro no checksum\n");
    break;

  default:
    printf("Erro no ETX\n");
    break;
  }
}


void readMSG() {
    int aux = 0;

    aux = readSTX();
    if (aux == -1) raiseError(1);
    else{
      aux = readQTD();
      if(aux == -1) raiseError(2);
      else{
        readDATA();
        aux = checkSUM();
        if (aux == -1) raiseError(3);
        else{
            if (readETX() == -1) raiseError(4);
            else{
                printf("Dados: %ld\n", dt.qtd);
                for (uint16_t i = 0; i < dt.qtd; i++)
                {
                    printf("%d \n", dt.data[i]);
                }
            }
        }
      }
    }
}

/**
 * The first protothread function. A protothread function must always
 * return an integer, but must never explicitly return - returning is
 * performed inside the protothread statements.
 *
 * The protothread function is driven by the main loop further down in
 * the code.
 */
static int sender(struct pt *pt)
{
  /* A protothread function must begin with PT_BEGIN() which takes a
     pointer to a struct pt. */
  PT_BEGIN(pt);

  /* We loop forever here. */
  while(1) {
    /* Wait until the other protothread has set its flag. */
    PT_WAIT_UNTIL(pt, receiver_flag != 0);
    printf("Protothread 1 running\n");
    //char msg[SIZE_MESSAGE] = {0x01, 0x03, 2, 1, 1, 2, 0x03}; // Erro forçado no STX
    //char msg[SIZE_MESSAGE] = {0x02, 0x00, 2, 1, 1, 2, 0x03}; // Erro forçado na QTD
    //char msg[SIZE_MESSAGE] = {0x02, 0x03, 2, 1, 1, 6, 0x03}; // Erro forçado no CHK
    //char msg[SIZE_MESSAGE] = {0x02, 0x03, 2, 1, 1, 2, 0x01}; // Erro forçado no ETX
    char msg[SIZE_MESSAGE] = {0x02, 0x03, 2, 1, 1, 2, 0x03}; // Mensagem correta

    for (size_t i = 0; i < SIZE_MESSAGE; i++)
    {
        dt.msg[i] = msg[i];
    }
    

    /* We then reset the other protothread's flag, and set our own
       flag so that the other protothread can run. */
    receiver_flag = 0;
    sender_flag = 1;

    /* And we loop. */
  }

  /* All protothread functions must end with PT_END() which takes a
     pointer to a struct pt. */
  PT_END(pt);
  printf("Protothread 1 stopped running\n");
}

/**
 * The second protothread function. This is almost the same as the
 * first one.
 */
static int receiver(struct pt *pt)
{
  PT_BEGIN(pt);

  while(1) {
    /* Let the other protothread run. */
    receiver_flag = 1;

    /* Wait until the other protothread has set its flag. */
    PT_WAIT_UNTIL(pt, sender_flag != 0);
    printf("Protothread 2 running\n");
    
    readMSG();
    
    /* We then reset the other protothread's flag. */
    sender_flag = 0;

    /* And we loop. */
  }
  PT_END(pt);
  printf("Protothread 2 stopped running\n");
}

/**
 * Finally, we have the main loop. Here is where the protothreads are
 * initialized and scheduled. First, however, we define the
 * protothread state variables pt1 and pt2, which hold the state of
 * the two protothreads.
 */
static struct pt pt1, pt2;

int main(void)
{
  /* Initialize the protothread state variables with PT_INIT(). */
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  
  /*
   * Then we schedule the two protothreads by repeatedly calling their
   * protothread functions and passing a pointer to the protothread
   * state variables as arguments.
   */
  while(1) {
    sender(&pt1);
    receiver(&pt2);
  }
}