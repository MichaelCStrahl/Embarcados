#include <asf.h>

adc_config(uint8_t adc_num, uint8_t adc_chan, uint8_t adc_res, uint16_t adc_freq);

uint16_t adc_read(uint8_t adc_num, uint8_t adc_chan);