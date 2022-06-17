#include "driver_led.h"

void led_config(uint8_t led_num, uint8_t pin){
	static const struct port_config config;
	port_pin_set_config(led_num,&config);
}

void led_on(uint8_t led_num){
	port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
}

void led_off(uint8_t led_num){
	port_pin_set_output_level(led_num, !LED_0_ACTIVE);
}

void led_toggle(uint8_t led_num){
	port_pin_toggle_output_level(led_num);
}