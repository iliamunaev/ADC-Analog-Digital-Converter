#include "converter.h"

/**
 * @brief Converts a decimal number to its binary representation.
 *
 * This function converts a decimal integer into its binary representation.
 * The binary value is stored in an `int32_t`, where the least significant
 * bits store the converted value.
 *
 * @param bits The number of bits to use for the binary representation.
 * @param digit The decimal number to convert.
 * @return int32_t The binary representation of `digit` using `bits` bits.
 */
static int32_t	decimal_to_binary(int bits, int digit)
{
	int32_t	num = 0;
	int		i = 0;

	while (i < bits)
	{
		num |= ((digit >> i) & 1) << i;
		i++;
	}
	return num;
}

/**
 * @brief Converts an input voltage to a binary representation based on ADC resolution.
 *
 * This function takes an input voltage (`volt_in`) and converts it to
 * a digital output value based on the ADC resolution determined by the
 * bit resolution (`bit_res`) and reference voltage range (`volt_low` to `volt_high`).
 * The function ensures that the output remains within the valid range
 * and then converts it to binary.
 *
 * @param volt_in The input voltage to be converted.
 * @param bit_res The bit resolution of the ADC.
 * @param volt_low The lower bound of the reference voltage.
 * @param volt_high The upper bound of the reference voltage.
 * @return int32_t The binary representation of the converted digital value.
 */
int32_t	convert(int volt_in, int bit_res, double volt_low, double volt_high) {
	double voltage_reference = volt_high - volt_low;

	// Calculate ADC resolution (voltage per bit)
	double ADC_resolution = voltage_reference / (pow(2, bit_res) - 1);

	// Calculate the digital output value
	int output_digit = ((volt_in - volt_low) / ADC_resolution);

	// Clamp the output_digit to the valid range [0, 2^bits - 1]
	if(output_digit < 0)
		output_digit = 0;

	int max_digit = (pow(2, bit_res) - 1);
	if(output_digit > max_digit)
		output_digit = max_digit;

	// Convert decimal to binary
	int32_t binary = decimal_to_binary(bit_res, output_digit);
	return binary;
}
