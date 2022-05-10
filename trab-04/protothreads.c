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

#define SIZE_DATA 3 // Tamanho do vetor que salva dados
#define SIZE_MESSAGE 9 // Tamanho da mensagem

/* Two flags that the two protothread functions use. */
static int sender_flag, receiver_flag;

/* Main functions */
struct Data {
    uint16_t qtd;
    char data[SIZE_DATA];
    uint8_t chksum;
    uint16_t etx;
    char msg[SIZE_MESSAGE];
} dt;

int readSTX() {
    if (dt.msg[0] == 0x02) return 0;
    else return -1;
}

void readQTD() {
    dt.qtd = dt.msg[1];
}

void readDATA() {
    dt.chksum = 0;

    for (size_t i = 0; i < dt.qtd; i++)
    {
        dt.data[i] = dt.msg[dt.qtd + i];
        dt.chksum = dt.msg[dt.qtd + i] ^ dt.chksum;
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

void readMSG() {
    int aux = 0;

    aux = readSTX();
    if (aux == 0) readQTD();

    readDATA();

    aux = checkSUM();
    if (aux == 0) {
        if (readETX() == 0) {
            size_t n = sizeof(dt.data)/sizeof(dt.data[0]);
            printf("Dados: %ld\n", n);
            for (size_t i = 0; i < n; i++)
            {
                printf("%c \n", dt.data[i]);
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
static int
sender(struct pt *pt)
{
  /* A protothread function must begin with PT_BEGIN() which takes a
     pointer to a struct pt. */
  PT_BEGIN(pt);

  /* We loop forever here. */
  while(1) {
    /* Wait until the other protothread has set its flag. */
    PT_WAIT_UNTIL(pt, receiver_flag != 0);
    printf("Protothread 1 running\n");
    char msg[SIZE_MESSAGE] = {0x02, 0x03, 2, 1, 1, 2, 0x03};

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
}

/**
 * The second protothread function. This is almost the same as the
 * first one.
 */
static int
receiver(struct pt *pt)
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
}

/**
 * Finally, we have the main loop. Here is where the protothreads are
 * initialized and scheduled. First, however, we define the
 * protothread state variables pt1 and pt2, which hold the state of
 * the two protothreads.
 */
static struct pt pt1, pt2;
int
main(void)
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