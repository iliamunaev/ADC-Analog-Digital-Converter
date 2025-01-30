#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <fcntl.h>
#include "libft.h"

typedef struct {
	char	**data;
	int		count;
}	Data;

typedef struct {
	Data	*data;
	double	highest_voltage;
	double	lowest_voltage;
	int		bits;
	double	voltage_reference;
	double	resolution;
}	Adc;

Adc		*init_ads(const char *pathToData);
double	get_voltage_ref(Adc *adc);
double	get_resolution(Adc *adc);

#endif  // CONVERTER_H
