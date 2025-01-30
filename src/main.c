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

	return EXIT_SUCCESS;
}
