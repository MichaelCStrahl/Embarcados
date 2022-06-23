#include <asf.h>

void adc_config_driver(uint8_t adc_num, uint8_t adc_chan, uint8_t adc_res, uint16_t adc_freq);

uint16_t adc_read_in(uint8_t adc_num, uint8_t adc_chan);