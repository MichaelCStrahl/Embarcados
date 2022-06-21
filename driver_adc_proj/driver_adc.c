#include "driver_adc.h"

uint8_t result = 0;

adc_config(uint8_t adc_num, uint8_t adc_chan, uint8_t adc_res, uint16_t adc_freq){
	adc_num->clock_prescaler = adc_freq;
	adc_num->resolution = adc_res;
	adc_num->positive_input = adc_chan;
}

uint16_t adc_read(uint8_t adc_num, uint8_t adc_chan){
	const uint8_t temp = ADC_INPUTCTRL_MUXPOS_TEMP_Val;
	const uint8_t bandgap = ADC_INPUTCTRL_MUXPOS_BANDGAP_Val;

	adc_get_status(adc_num)
}
