#include "driver_pwm.h"
#define MODULE_LENGHT 1

struct tcc_config config_tcc[MODULE_LENGHT];
struct tcc_module tcc_instance[MODULE_LENGHT];


void pwm_config(uint8_t pwm_num, uint8_t pin){
	if (pwm_num <= MODULE_LENGHT-1){
		tcc_get_config_defaults(&config_tcc[pwm_num], LED_0_PWM4CTRL_MODULE);
		config_tcc[pwm_num].pins.wave_out_pin[LED_0_PWM4CTRL_OUTPUT] = pin;

		tcc_init(&tcc_instance[pwm_num], LED_0_PWM4CTRL_MODULE, &config_tcc[pwm_num]);
	}
}


void pwm_on(uint8_t pwm_num){
	tcc_enable(&tcc_instance[pwm_num]);
}


void pwm_off(uint8_t pwm_num){
	tcc_disable(&tcc_instance[pwm_num]);
}


void pwm_set(uint8_t pwm_num, uint16_t duty){
	uint16_t duty_percent;

	tcc_disable(&tcc_instance[pwm_num]);
	duty_percent = (0xFFFF/1000)*duty;
	config_tcc[pwm_num].compare.match[LED_0_PWM4CTRL_CHANNEL] = duty_percent;
	tcc_enable(&tcc_instance[pwm_num]);
}