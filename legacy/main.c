#include "converter.h"

int main(int argc, char **argv) {

	if(argc != 2) {
		// err msg
		return EXIT_FAILURE;
	}

	const char *pathToData = argv[1];
	Adc *adc = init_ads(pathToData);
	if(!adc) {
		// err msg
		return EXIT_FAILURE;
	}

	int bits = atoi(argv[1]);
	double lowest_voltage = atof(argv[2]);
	double highest_voltage = atof(argv[3]);
	int analog_input_value = atof(argv[4]);

	// Validate input
	if(bits <= 0)
	{
		printf("Error: Number of bits must be positive.\n");
		return 1;
	}
	if(highest_voltage <= lowest_voltage)
	{
		printf("Error: Highest voltage must be greater than lowest voltage.\n");
		return 1;
	}
	if(analog_input_value < lowest_voltage || analog_input_value > highest_voltage)
	{
		printf("Warning: Analog input value is outside the voltage range. It will be clamped.\n");
	}

	// Perform the conversion
	char *binary_result = convert(bits, lowest_voltage, highest_voltage, analog_input_value);

	printf("Binary Representation: %s\n", binary_result);
	free(binary_result);

	return 0;
}
