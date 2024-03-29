/**
 * \file
 *
 * \brief Exemplos diversos de tarefas e funcionalidades de um sistema operacional multitarefas.
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Este arquivo contem exemplos diversos de tarefas e 
 * funcionalidades de um sistema operacional multitarefas.
 *
 *
 * \par Conteudo
 *
 * -# Inclui funcoes do sistema multitarefas (atraves de multitarefas.h)
 * -# Inicizalizao do processador e do sistema multitarefas
 * -# Criacao de tarefas de demonstracao
 *
 */

/*
 * Inclusao de arquivos de cabecalhos
 */
#include <asf.h>
#include <stdio.h>
#include "stdint.h"
#include "multitarefas.h"
#include <unistd.h>
#include "extint.h"
#include "driver_gpio.h"
#include "driver_led.h"
#include "driver_timer.h"
#include "driver_pwm.h"
#include "driver_adc.h"
#include "driver_uart.h"

/*
 * Prototipos das tarefas
 */
void tarefa_1(void);
void tarefa_2(void);
void tarefa_3(void);
void tarefa_4(void);
void tarefa_5(void);
void tarefa_6(void);
void tarefa_7(void);
void tarefa_8(void);
void tarefa_9(void);
void tarefa_10(void);
void periodicCoop1(void);
void periodicCoop2(void);
void periodicPreemp1(void);
void periodicPreemp2(void);
void Produtor(void);
void Consumidor(void);
int produz(void);
void consome(int buf);
void thread1(void);
void thread2(void);
void thread3(void);
void thread4(void);
void thread5(void);
void thread_print(int c1,int c2,int c3,int c4,int c5);
void configure_extint_channel(void);
void configure_extint_callbacks(void);
void extint_detection_callback(void);
void extint_polled(void);
void extint_callback(void);
void adc_reader(void);
void pwm(void);
void print(void);

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_3			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_4			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_5			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_6			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_7			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_8			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_9			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_10		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_3[TAM_PILHA_3];
uint32_t PILHA_TAREFA_4[TAM_PILHA_4];
uint32_t PILHA_TAREFA_5[TAM_PILHA_5];
uint32_t PILHA_TAREFA_6[TAM_PILHA_6];
uint32_t PILHA_TAREFA_7[TAM_PILHA_7];
uint32_t PILHA_TAREFA_8[TAM_PILHA_8];
uint32_t PILHA_TAREFA_9[TAM_PILHA_9];
uint32_t PILHA_TAREFA_10[TAM_PILHA_10];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];

#define TAM_BUFFER 10
uint8_t buffer[TAM_BUFFER]; /* declaracao de um buffer (vetor) ou fila circular */

semaforo_t SemaforoCheio = {0,0}; /* declaracao e inicializacao de um semaforo */
semaforo_t SemaforoVazio = {TAM_BUFFER,0}; /* declaracao e inicializacao de um semaforo */


/* Configura EXTINT */
void configure_extint_channel(void)
{
	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);
	config_extint_chan.gpio_pin = BUTTON_0_EIC_PIN;
	config_extint_chan.gpio_pin_mux = BUTTON_0_EIC_MUX;
	config_extint_chan.gpio_pin_pull = EXTINT_PULL_UP;
	config_extint_chan.detection_criteria = EXTINT_DETECT_BOTH;
	extint_chan_set_config(BUTTON_0_EIC_LINE, &config_extint_chan);
}
void configure_extint_callbacks(void)
{
	extint_register_callback(extint_detection_callback,BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
}
void extint_detection_callback(void)
{
	bool pin_state = port_pin_get_input_level(BUTTON_0_PIN);
	port_pin_set_output_level(LED_0_PIN, pin_state);
}

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	system_init();
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */

	//CriaTarefa(tarefa_1, "Tarefa 1", PILHA_TAREFA_1, TAM_PILHA_1, 1);
	
	//CriaTarefa(tarefa_2, "Tarefa 2", PILHA_TAREFA_2, TAM_PILHA_2, 2);
	
	//CriaTarefa(periodicCoop1, "Tarefa Coop1", PILHA_TAREFA_2, TAM_PILHA_2, 2);

	//CriaTarefa(periodicCoop2,"Tarefa Coop2",PILHA_TAREFA_1,TAM_PILHA_1,1);

	//CriaTarefa(periodicPreemp1, "Tarefa Preemp1", PILHA_TAREFA_2, TAM_PILHA_2, 2);

	//CriaTarefa(periodicPreemp2,"Tarefa Preemp2", PILHA_TAREFA_1,TAM_PILHA_1,1);

	//CriaTarefa(Produtor,"Tarefa Produtor", PILHA_TAREFA_1,TAM_PILHA_1,1);

	//CriaTarefa(Consumidor,"Tarefa Consumidor", PILHA_TAREFA_2,TAM_PILHA_2,2);

	//CriaTarefa(thread1,"Tarefa thread1", PILHA_TAREFA_1, TAM_PILHA_1,4);

	//CriaTarefa(thread2,"Tarefa thread2", PILHA_TAREFA_2, TAM_PILHA_2,3);

	//CriaTarefa(thread3,"Tarefa thread3", PILHA_TAREFA_3, TAM_PILHA_3,2);

	//CriaTarefa(thread4,"Tarefa thread4", PILHA_TAREFA_4, TAM_PILHA_4,1);

	//CriaTarefa(thread5,"Tarefa thread5", PILHA_TAREFA_5, TAM_PILHA_5,0);

	//CriaTarefa(thread_print,"Tarefa thread_print",PILHA_TAREFA_6,TAM_PILHA_6,5);

	//configure_extint_channel();

	//CriaTarefa(extint_polled,"Tarefa Polled",PILHA_TAREFA_1, TAM_PILHA_1,1);

	//configure_extint_channel();
	//configure_extint_callbacks();
	//system_interrupt_enable_global();

	//CriaTarefa(extint_callback,"Tarefa Callback",PILHA_TAREFA_1, TAM_PILHA_1,1);

	//CriaTarefa(adc_reader,"Tarefa adc reader",PILHA_TAREFA_1, TAM_PILHA_1,1);
	
	//CriaTarefa(pwm,"Tarefa pwm",PILHA_TAREFA_1, TAM_PILHA_1,1);
	
	CriaTarefa(print,"Tarefa print",PILHA_TAREFA_1, TAM_PILHA_1,1);

	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}

/* Tarefas de exemplo que usam funcoes para suspender/continuar as tarefas */
void tarefa_1(void)
{
	volatile uint16_t a = 0;
	for(;;)
	{
		a++;
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE); /* Liga LED. */
		TarefaContinua(2);
	
	}
}

void tarefa_2(void)
{
	volatile uint16_t b = 0;
	for(;;)
	{
		b++;
		TarefaSuspende(2);	
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE); 	/* Turn LED off. */
	}
}

/* Tarefas de exemplo que usam funcoes para suspender as tarefas por algum tempo (atraso/delay) */
void tarefa_3(void)
{
	volatile uint16_t a = 0;
	for(;;)
	{
		a++;
		
		/* Liga LED. */
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		TarefaEspera(1000); 	/* tarefa 1 se coloca em espera por 3 marcas de tempo (ticks) */
		
		/* Desliga LED. */
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		TarefaEspera(1000); 	/* tarefa 1 se coloca em espera por 3 marcas de tempo (ticks) */
	}
}

void tarefa_4(void)
{
	volatile uint16_t b = 0;
	for(;;)
	{
		b++;
		TarefaEspera(5);	/* tarefa se coloca em espera por 5 marcas de tempo (ticks) */
	}
}

/* Tarefas de exemplo que usam funcoes de semaforo */

semaforo_t SemaforoTeste = {0,0}; /* declaracao e inicializacao de um semaforo */

void tarefa_5(void)
{

	uint32_t a = 0;			/* inicializações para a tarefa */
	
	for(;;)
	{
		
		a++;				/* código exemplo da tarefa */

		TarefaEspera(3); 	/* tarefa se coloca em espera por 3 marcas de tempo (ticks) */
		
		SemaforoLibera(&SemaforoTeste); /* tarefa libera semaforo para tarefa que esta esperando-o */
		
	}
}

/* Exemplo de tarefa que usa semaforo */
void tarefa_6(void)
{
	
	uint32_t b = 0;	    /* inicializações para a tarefa */
	
	for(;;)
	{
		
		b++; 			/* código exemplo da tarefa */
		
		SemaforoAguarda(&SemaforoTeste); /* tarefa se coloca em espera por semaforo */

	}
}

/* soluçao com buffer compartihado */
/* Tarefas de exemplo que usam funcoes de semaforo */

void tarefa_7(void)
{

	uint8_t a = 1;			/* inicializações para a tarefa */
	uint8_t i = 0;
	
	for(;;)
	{
		SemaforoAguarda(&SemaforoVazio);
		
		buffer[i] = a++;
		i = (i+1)%TAM_BUFFER;
		
		SemaforoLibera(&SemaforoCheio); /* tarefa libera semaforo para tarefa que esta esperando-o */
		
		TarefaEspera(10); 	/* tarefa se coloca em espera por 10 marcas de tempo (ticks), equivale a 10ms */		
	}
}

/* Exemplo de tarefa que usa semaforo */
void tarefa_8(void)
{
	static uint8_t f = 0;
	volatile uint8_t valor;
		
	for(;;)
	{
		volatile uint8_t contador;
		
		do{
			REG_ATOMICA_INICIO();			
				contador = SemaforoCheio.contador;			
			REG_ATOMICA_FIM();
			
			if (contador == 0)
			{
				TarefaEspera(100);
			}
				
		} while (!contador);
		
		SemaforoAguarda(&SemaforoCheio);
		
		valor = buffer[f];
		f = (f+1) % TAM_BUFFER;		
		
		SemaforoLibera(&SemaforoVazio);
	}
}

void tarefa_9(void)
{
	volatile uint16_t a = 0;
	volatile uint16_t b = 0;
	for(;;)
	{
		a++;
		b = a/2;

		/* Liga LED. */
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		TarefaEspera(a*100); 	/* tarefa 1 se coloca em espera por 3 marcas de tempo (ticks) */
		
		/* Desliga LED. */
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		TarefaEspera(b*100); 	/* tarefa 1 se coloca em espera por 3 marcas de tempo (ticks) */
	}
}

void periodicCoop1(void){
	/* tarefa periódica no modo cooperativo */
	volatile uint16_t a = 0;
	while (1){
		a++;
		/* Liga LED. */
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		TarefaEspera(1000); 	/* tarefa 1 se coloca em espera por 3 marcas de tempo (ticks) */
		
	}
}

void periodicCoop2(void){
	/* tarefa periódica no modo cooperativo */
	volatile uint16_t a = 0;
	while (1){
		a++;	
		/* Desliga LED. */
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		TarefaEspera(300); 	/* tarefa 1 se coloca em espera por 3 marcas de tempo (ticks) */
	}
}

void periodicPreemp1(void){
	while(1){
		/* tarefa periódica no modo preemptivo */
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		TarefaEspera(1100);
	}
}

void periodicPreemp2(void){
	while(1){
		volatile int b = 0; 
	/* tarefa periódica no modo preemptivo */
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		TarefaEspera(400);
		
	}
}

int produz(void){
	uint8_t a = 0;
	port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
	return 1;
}

void consome(int buf){
	uint8_t a = 0;
	if(buf == 1){
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
	}
}

void Produtor(void){
	uint8_t f = 0;
	while(1){
		SemaforoAguarda(&SemaforoVazio);
		f = (f+1)%TAM_BUFFER;
		buffer[f] = produz();
		SemaforoLibera(&SemaforoCheio);
	}
}

void Consumidor(void){
	uint8_t i = 0;
	while(1){
		SemaforoAguarda(&SemaforoCheio);
		i = (i+1)%TAM_BUFFER;
		consome(buffer[i]);
		SemaforoLibera(&SemaforoVazio);
	}
}

void thread1(void){
	uint8_t count1=0;
	count1++;
	TarefaContinua(2);
}

void thread2(void){
	uint8_t count2=0;
	count2++;
	TarefaContinua(3);
	TarefaSuspende(2);
}

void thread3(void){
	uint8_t count3=0;
	count3++;
	TarefaContinua(4);
	TarefaSuspende(3);
}

void thread4(void){
	uint8_t count4=0;
	count4++;
	TarefaContinua(5);
	TarefaSuspende(4);
}

void thread5(void){
	uint8_t count5=0;
	count5++;
	TarefaSuspende(5);
}

void thread_print(int c1,int c2,int c3,int c4,int c5){
	int cn1 = c1;
	int cn2 = c2;
	int cn3 = c3;
	int cn4 = c4;
	int cn5 = c5;
	TarefaEspera(300);
}

void extint_polled(void){
	while (true) {
		if (extint_chan_is_detected(BUTTON_0_EIC_LINE)) {
			// Do something in response to EXTINT edge detection
			bool button_pin_state = port_pin_get_input_level(BUTTON_0_PIN);
			port_pin_set_output_level(LED_0_PIN, button_pin_state);
			extint_chan_clear_detected(BUTTON_0_EIC_LINE);
		}
	}
}

void extint_callback(void){
	while (true) {
		/* Do nothing - EXTINT will fire callback asynchronously */
	}
}

void adc_reader(){
	const uint8_t temp = 0x18;
	const uint8_t bandgap = 0x19;
	uint16_t result = 0;
	uint16_t bandigap = 0;
	float voltage = 0;
	float temperature = 0;

	while(true){
		adc_config_driver(0,temp,ADC_RESOLUTION_12BIT,ADC_CLOCK_PRESCALER_DIV8);
		result = adc_read_in(0,temp);
		bandigap = adc_read_in(0,bandgap);
		voltage = (result*0.667)/bandigap;

		temperature = 25 + ((voltage-0.667)/0.0024);
	}
}

void pwm(){
	int a = 0;
	while(true){
		pwm_config(0,LED_0_PIN);
		pwm_on(0);
		for(int i=0;i<10000;i++){
			a++;
		}
		a++;
	}
}

void print(){
	uint8_t ch;
	uart_config(0,9600);
	uart_transmite(0);
	while(1){
		//uart_recebe(0,ch);
		
	}
}