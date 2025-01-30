#include "converter.h"

double	get_voltage_ref(Adc *adc) {
	double voltage_reference = adc->highest_voltage - adc->lowest_voltage;

	return (voltage_reference);
}

double	get_resolution(Adc *adc) {
	double resolution = adc->voltage_reference / (pow(2, adc->bits) - 1);

	return (resolution);
}
