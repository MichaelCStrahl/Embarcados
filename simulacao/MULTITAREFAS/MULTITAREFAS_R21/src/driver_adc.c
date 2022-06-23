#include "driver_adc.h"
#define MODULE_LENGHT 1

struct adc_config adc_vector[MODULE_LENGHT];
struct adc_module adc_instance[MODULE_LENGHT];

void adc_config_driver(uint8_t adc_num, uint8_t adc_chan, uint8_t adc_res, uint16_t adc_freq){
	if (adc_num <= MODULE_LENGHT-1){
		adc_get_config_defaults(&adc_vector[adc_num]);
		adc_vector[adc_num].clock_prescaler = adc_freq;
		adc_vector[adc_num].resolution = adc_res;
		adc_vector[adc_num].positive_input = adc_chan;
		adc_init(&adc_instance[adc_num], ADC, &adc_vector[adc_num]);
		adc_enable(&adc_instance[adc_num]);
	}

}

uint16_t adc_read_in(uint8_t adc_num, uint8_t adc_chan){
	uint16_t result;
	uint8_t status = STATUS_BUSY;
	if (adc_num <= MODULE_LENGHT-1){
		adc_vector[adc_num].positive_input = adc_chan;
		adc_start_conversion(&adc_instance[adc_num]);
		while(status != STATUS_OK){
			status = adc_read(&adc_instance[adc_num],&result);
		}
		return result;	
	}
}
