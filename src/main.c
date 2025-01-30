#include "converter.h"

/**
 * @brief The main function for handling user input and calling the conversion process.
 *
 * This function runs a loop prompting the user for input values and processes them
 * using the `convert` function. The program exits when the user types "exit".
 *
 * @param ac The argument count.
 * @param av The argument vector (list of input arguments).
 * @return EXIT_SUCCESS on successful execution.
 */
int	main(int ac, char **av)
{
	if (ac < 2) {
		ft_putstr_fd("Error: Too few arguments\n", 2);
		ft_putstr_fd("Usage: ./ADC <volt_in> <bit_res> <volt_low> <volt_high>\n", 1);
		return EXIT_FAILURE;
	}

	// Check if the user wants to exit
	if (ft_strcmp(av[1], "exit") == 0) {
		ft_putstr_fd("Program exit success.\n", 1);
		return EXIT_SUCCESS;
	}

	if (ac != 5) {
		ft_putstr_fd("Error: Invalid number of arguments.\n", 2);
		ft_putstr_fd("Usage: ./ADC <volt_in> <bit_res> <volt_low> <volt_high>\n", 1);
		return EXIT_FAILURE;
	}

	// Convert arguments to numerical values
	int		volt_in = ft_atoi(av[1]);     // Convert voltage input to int
	int		bit_res = ft_atoi(av[2]);     // Convert bit resolution to int
	double	volt_low = atof(av[3]);       // Convert low voltage limit to double
	double	volt_high = atof(av[4]);      // Convert high voltage limit to double

	// Validate input values
	if (!is_valid_input(volt_in, bit_res, volt_low, volt_high)) {
		ft_putstr_fd("Error: Invalid input values.\n", 2);
		ft_putstr_fd("Ensure values are within valid ADC range.\n", 1);
		return EXIT_FAILURE;
	}

	// Convert voltage to binary representation
	int32_t binary = convert(volt_in, bit_res, volt_low, volt_high);
	print_result(binary, bit_res);
	return EXIT_SUCCESS;
}
