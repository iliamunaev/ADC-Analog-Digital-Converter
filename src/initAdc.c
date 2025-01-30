#include "converter.h"

static bool	get_data(Data *data, const char *pathToData) {

	int fd = open(pathToData, O_RDONLY);
	if (fd == -1) {
		perror("ERROR: Failed opening file");
		return false;
	}

	int		i = 0;
	char	*line;
	char	**new_data = NULL;

	while ((line = get_next_line(fd)) != NULL) {

		// Resize the array to store new line
		new_data = realloc(data->data, (i + 1) * sizeof(char *));
		if (!new_data) {
			perror("ERROR: Memory allocation failed");
			free(line);
			return false;
		}
		data->data = new_data;
		data->data[i] = line;
		i++;
	}

	data->count = i;

	close(fd);
	return true;
}

Adc	*init_ads(const char	*pathToData) {

	Data *data = malloc(sizeof(Data));
	if(!data)
		return NULL;
	data->data = NULL;
	data->count = 0;

	Adc *adc = malloc(sizeof(Adc));
	if(!adc)
		return NULL;

	adc->data = data;

	if(!get_data(data, pathToData)) {
		free(data->data);
		free(data);
		free(adc);
		return NULL;
	}
	adc->highest_voltage = atof(data->data[0]);
	adc->lowest_voltage = atof(data->data[1]);
	adc->bits = ft_atoi(data->data[2]);
	adc->voltage_reference = get_voltage_ref(adc);
	adc->resolution = get_resolution(adc);

	return adc;
}

