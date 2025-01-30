#include "converter.h"

void print_result(int num, int bit_res)
{
	unsigned int mask = (1U << (bit_res - 1)); // Start from MSB
	char bit;
	int i = 0;

	while (i < bit_res) {
		bit = ((num & mask) != 0) ? '1' : '0';  // Extract correct bit
		write(1, &bit, 1);
		mask >>= 1; // Shift mask right
		i++;
	}
	write(1, "\n", 1);
}
