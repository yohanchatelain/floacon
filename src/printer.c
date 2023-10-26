#include <mpfr.h>

#include "printer.h"
#include "types.h"

void floacon_print_float(floacon_t x) { mpfr_printf("%Rf\n", x); }
void floacon_print_binary(floacon_t x) { mpfr_printf("%Rb\n", x); }
void floacon_print_hex(floacon_t x) { mpfr_printf("%Ra\n", x); }
void floacon_print_scientific(floacon_t x) { mpfr_printf("%Re\n", x); }
void floacon_print_general(floacon_t x) { mpfr_printf("%Rg\n", x); }

void floacon_print(floacon_output_format_t format, floacon_t x) {
  switch (format) {
  case FLOACON_OUTPUT_BINARY:
    floacon_print_binary(x);
    break;
  case FLOACON_OUTPUT_FLOAT:
    floacon_print_float(x);
    break;
  case FLOACON_OUTPUT_HEX:
    floacon_print_hex(x);
    break;
  case FLOACON_OUTPUT_SCIENTIFIC:
    floacon_print_scientific(x);
    break;
  case FLOACON_OUTPUT_GENERAL:
    floacon_print_general(x);
    break;
  default:
    floacon_print_general(x);
    break;
  }
}