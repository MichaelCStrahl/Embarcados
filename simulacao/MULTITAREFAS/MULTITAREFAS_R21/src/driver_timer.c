#include "driver_timer.h"
#define MODULE_LENGHT 1

struct tc_config config_tc[MODULE_LENGHT];
struct tc_module tc_instance[MODULE_LENGHT];


void timer_config(uint8_t timer_num, uint16_t period_ms){
	if (timer_num <= MODULE_LENGHT-1){
		tc_get_config_defaults(&config_tc[timer_num]);
		config_tc[timer_num].counter_size = TC_COUNTER_SIZE_8BIT;
		config_tc[timer_num].clock_source = GCLK_GENERATOR_1;
		config_tc[timer_num].clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
		config_tc[timer_num].counter_8_bit.period = period_ms;

		tc_init(&tc_instance[timer_num], TC3, &config_tc[timer_num]);
		tc_enable(&tc_instance[timer_num]);
	}
}

void timer_start(uint8_t timer_num){
	tc_start_counter(&tc_instance[timer_num]);
}

void timer_stop(uint8_t timer_num){
	tc_stop_counter(&tc_instance[timer_num]);
}

uint32_t timer_count(uint8_t timer_num){
	uint32_t result;

	result = tc_get_count_value(&tc_instance[timer_num]);
}

void timer_delay(uint8_t timer_num, uint16_t period_ms){
	tc_stop_counter(&tc_instance[timer_num]);
	config_tc[timer_num].counter_8_bit.period = period_ms;
	tc_start_counter(&tc_instance[timer_num]);
}