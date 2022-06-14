#include "driver_timer.h"

void timer_config(uint8_t timer_num, uint16_t period_ms){
	tc_init();
	tc_set_top_value();	
}

void timer_start(uint8_t timer_num){
	tc_start_counter()
}

void timer_stop(uint8_t timer_num){
	tc_stop_counter(timer_num)
}

uint32_t timer_count(uint8_t timer_num){
	tc_get_count_value(timer_num);
}

void timer_delay(uint8_t timer_num, uint16_t period_ms){
	
}