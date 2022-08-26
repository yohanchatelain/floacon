#include <mpfr.h>

void print_float(mpfr_t x) { mpfr_printf("%Rf\n", x); }
void print_binary(mpfr_t x) { mpfr_printf("%Rb\n", x); }
void print_hex(mpfr_t x) { mpfr_printf("%Ra\n", x); }
void print_scientific(mpfr_t x) { mpfr_printf("%Re\n", x); }
void print_general(mpfr_t x) { mpfr_printf("%Rg\n", x); }
