#include "driver_gpio.h"

struct pin_dir_array{
	uint8_t pin;
	uint8_t dir;
};

void pio_config(uint8_t gpio_num, uint8_t dir){
	const struct system_pinmux_config pinmux_config;
	pinmux_config.direction = dir;

	static struct pin_dir_array dir_array;
	dir_array.pin = gpio_num;
	dir_array.dir = dir;

	port_pin_set_config(gpio_num,&pinmux_config);
}

void gpio_write(uint8_t gpio_num, uint8_t val){
	port_pin_set_output_level(gpio_num,(bool)val);
}

void gpio_read(uint8_t gpio_num, uint8_t *val){
	&val = port_pin_get_input_level(gpio_num);
}

void gpio_toggle(uint8_t gpio_num){
	port_pin_toggle_output_level(gpio_num);
}

uint8_t gpio_dir(uint8_t gpio_num){
	if (gpio_num == dir_array.gpio_num){
		return dir_array.dir;
	}
	else{
		return -1;
	}
}