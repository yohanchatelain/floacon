#include <stdio.h>
#include <stdlib.h>

#include "args.h"
#include "converter.h"
#include "extractor.h"
#include "printer.h"
#include "types.h"

int main(int argc, char *argv[]) {

  floacon_argp_state_t args;
  parse_args(argc, argv, &args);
  print_argp_state(&args);
  floacon_format_t input_fmt = {.exponent = args.input_exponent,
                                .precision = args.input_precision};
  floacon_format_t output_fmt = {.exponent = args.output_exponent,
                                 .precision = args.output_precision};

  floacon_t x;

  floacon_convert(args.input_value, NULL, input_fmt, output_fmt, MPFR_RNDN, x);
  mpfr_printf("%Ra\n", x);

  return 0;
}
