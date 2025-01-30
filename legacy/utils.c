#include "converter.h"

double	get_voltage_ref(Adc *adc) {
	double voltage_reference = adc->highest_voltage - adc->lowest_voltage;

	return (voltage_reference);
}

double	get_resolution(Adc *adc) {
	double resolution = adc->voltage_reference / (pow(2, adc->bits) - 1);

	return (resolution);
}
/*
 * Converts a decimal number to its binary representation as a string using only while loops.
 *
 * bits: Number of bits for the binary representation.
 * digit: The decimal number to convert.
 * binary_value: Pointer to a character array where the binary string will be stored.
 *
 * returns: void (binary_value is modified directly).
 */
void decimal_to_binary(int bits, int digit, char *binary_value)
{
	int i = 0;
	while (i < bits)
	{
		int power = (1 << (bits - 1 - i));
		if (digit & power)
		{
			binary_value[i] = '1';
		} else
		{
			binary_value[i] = '0';
		}
		i++;
	}
	binary_value[bits] = '\0';
}

/*
 * Converts an analog input value to its binary representation based on ADC parameters.
 *
 * bits: Number of bits of the ADC.
 * lowest_voltage: The lowest voltage reference (e.g., 0V).
 * highest_voltage: The highest voltage reference (e.g., 5V).
 * analog_input_value: The raw analog input value from the ADC.
 *
 * returns: A string containing the binary representation of the digital value.
 */
char *convert(int bits, double lowest_voltage, double highest_voltage, int analog_input_value) {
	// Calculate voltage reference
	double voltage_reference = highest_voltage - lowest_voltage;

	// Calculate ADC resolution (voltage per bit)
	double ADC_resolution = voltage_reference / (pow(2, bits) - 1);

	// Calculate the digital output value
	int output_digit = (int)((analog_input_value - lowest_voltage) / ADC_resolution);

	// Clamp the output_digit to the valid range [0, 2^bits - 1]
	if(output_digit < 0)
	{
		output_digit = 0;
	}
	int max_digit = (int)(pow(2, bits) - 1);
	if(output_digit > max_digit)
	{
		output_digit = max_digit;
	}

	// Allocate memory for the binary string
	char *binary_value = (char *)malloc(bits + 1);
	if(binary_value == NULL)
	{
		printf("Memory allocation failed\n");
		free(binary_value);
		return 0;
	}

	// Convert decimal to binary string using while loops
	decimal_to_binary(bits, output_digit, binary_value);

	return binary_value;
}
