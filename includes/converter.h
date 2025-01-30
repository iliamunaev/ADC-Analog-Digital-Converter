#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "../libft/libft.h"

bool	is_valid_input(int volt_in, int bit_res, double volt_low, double volt_high);
int32_t	convert(int volt_in, int bit_res, double volt_low, double volt_high);
void print_result(int num, int bit_res);

#endif  // CONVERTER_H
