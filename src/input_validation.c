#include "converter.h"

bool	is_valid_input(int volt_in, int bit_res, double volt_low, double volt_high) {

	if(bit_res <= 0) {
		ft_putstr_fd("Error: bit resolution must be positive\n", 2);
		return false;
	}
	if(volt_high <= volt_low) {
		ft_putstr_fd("Error: highest voltage must be greater than lowest voltage\n", 2);
		return false;
	}
	if(volt_in < volt_low || volt_in > volt_high) {
		ft_putstr_fd("Error: analog input value is outside the voltage range. It will be clamped\n", 2);
		return false;
	}
	return true;
}
