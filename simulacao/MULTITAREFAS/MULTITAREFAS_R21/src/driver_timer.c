#include "driver_timer.h"

void timer_config(const struct tc_module *const timer_num, const uint32_t period_ms){
	tc_init(&timer_num);
	tc_set_top_value(&timer_num,period_ms);	
}

void timer_start(const struct tc_module *const timer_num){
	tc_start_counter(&timer_num);
}

void timer_stop(const struct tc_module *const timer_num){
	tc_stop_counter(&timer_num);
}

uint32_t timer_count(const struct tc_module *const timer_num){
	tc_get_count_value(&timer_num);
}

void timer_delay(uint8_t timer_num, uint16_t period_ms){
	
}