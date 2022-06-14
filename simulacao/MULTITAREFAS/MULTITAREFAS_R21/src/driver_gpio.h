#include <asf.h>

void pio_config(uint8_t gpio_num, uint8_t pin, uint8_t dir);

void gpio_write(uint8_t gpio_num, uint8_t val);

void gpio_read(uint8_t gpio_num, uint8_t *val);

void gpio_toggle(uint8_t gpio_num);

uint8_t gpio_dir(uint8_t gpio_num)